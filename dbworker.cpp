#include "dbworker.h"
#include <QDebug>
#include <stdexcept>

DbWorker::DbWorker(QObject *parent) : QObject(parent), settings("BusinessKeeper", "AppConfig") {}


// Destructor
// Closes the database connection if it is open
DbWorker::~DbWorker()
{
    if(db.isOpen()){
        db.close();
    }
}



// Function to set up the database
// This function creates a new database and a table for categories
void DbWorker::setupDatabase(const QString &host, const QString &user,
                             const QString &password, const QString &dbName, bool createIfNotExist) {

    qDebug() << "Available drivers:" << QSqlDatabase::drivers();
    try {
        qDebug() << "Starting database setup...";
        QString connectionName = QString("db_connection_%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));

        if (!QSqlDatabase::contains(connectionName)) {
            db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
            db.setHostName(host);
            db.setUserName(user);
            db.setPassword(password);
        } else {
            db = QSqlDatabase::database(connectionName);
        }

        if (createIfNotExist) {
            db.setDatabaseName("");
            if (!db.open()) {
                throw std::runtime_error(QString("Failed to connect to MySQL server: %1").arg(db.lastError().text()).toStdString());
            }

            QSqlQuery query(db);
            if (!query.exec(QString("CREATE DATABASE IF NOT EXISTS %1").arg(dbName))) {
                throw std::runtime_error(QString("Failed to create database: %1").arg(query.lastError().text()).toStdString());
            }
        }

        db.setDatabaseName(dbName);
        if (!db.open()) {
            throw std::runtime_error(QString("Failed to connect to database: %1").arg(db.lastError().text()).toStdString());
        }

        QSqlQuery query(db);
        QString createTableQuery = R"(
            CREATE TABLE IF NOT EXISTS categories (
                id INT AUTO_INCREMENT PRIMARY KEY,
                name VARCHAR(255) UNIQUE NOT NULL,
                created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
            )
        )";

        if (!query.exec(createTableQuery)) {
            throw std::runtime_error(QString("Failed to create categories table: %1").arg(query.lastError().text()).toStdString());
        }

        qDebug() << "Categories table created successfully.";
        emit databaseSetupFinished(true, "Database setup successfully.");
    } catch (const std::exception &e) {
        qDebug() << "Exception caught in setupDatabase:" << e.what();
        emit databaseSetupFinished(false, QString("Exception: %1").arg(e.what()));
    } catch (...) {
        qDebug() << "Unknown exception caught in setupDatabase.";
        emit databaseSetupFinished(false, "Unknown error occurred during database setup.");
    }
}




// Function to initialize the database connection
// This function reads the database configuration from settings and establishes a connection
bool DbWorker::initializeDatabase(){
    
    QString host = settings.value("Database/Host", "").toString();
    QString user = settings.value("Database/User", "").toString();
    QString password = settings.value("Database/Password", "").toString();
    QString dbName = settings.value("Database/Name", "").toString();
    
    if (QSqlDatabase::contains("persistent_connection")){
        db = QSqlDatabase::database("persistent_connection");
    }else{
        db = QSqlDatabase::addDatabase("QMYSQL", "persistent_connection");
        db.setHostName(host);
        db.setUserName(user);
        db.setPassword(password);
        db.setDatabaseName(dbName);
    }
    
    if (!db.isOpen()){
        qDebug() << "Failed to open database: " << db.lastError().text();
        return false;
    }
    
    qDebug() << "Database connection initialized successfully.";
    return true;
}



// Function to check if the database exists
// This function checks if the database can be accessed with the given credentials
bool DbWorker::doesDatabaseExist(){
    
    QString host = settings.value("Database/Host", "").toString();
    QString user = settings.value("Database/User", "").toString();
    QString password = settings.value("Database/Password", "").toString();
    QString dbName = settings.value("Database/Name", "").toString();
    
    QString connectionName = QString("check_db_connection_%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));
    QSqlDatabase tempDb = QSqlDatabase::addDatabase("QMYSQL", connectionName);
    tempDb.setHostName(host);
    tempDb.setUserName(user);
    tempDb.setPassword(password);
    tempDb.setDatabaseName(dbName);

    if (tempDb.open()){
        qDebug()<< "Database exists and connection successfully.";
        tempDb.close();
        QSqlDatabase::removeDatabase(connectionName);
        return true;
    }else{
        qDebug()<< "Database does not exist and connection failed." << tempDb.lastError().text();
        QSqlDatabase::removeDatabase(connectionName);
        return false;
    }
    
}


// Function to connect to the database
// This function establishes a connection to the database using the provided credentials
bool DbWorker::connectToDatabase(const QString &host, const QString &user, const QString &password, const QString &dbName) {
    // Use the class member `db`
    if (QSqlDatabase::contains("persistent_connection")) {
        db = QSqlDatabase::database("persistent_connection");
    } else {
        db = QSqlDatabase::addDatabase("QMYSQL", "persistent_connection");
        db.setHostName(host);
        db.setUserName(user);
        db.setPassword(password);
        db.setDatabaseName(dbName);
    }

    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
        return false;
    }

    qDebug() << "Database connection established.";
    return true;
}




// Function to add a new category to the database
// This function inserts a new category into the categories table
bool DbWorker::addCategory(const QString &categoryName) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open. Attempting to reinitialize...";
        if (!initializeDatabase()) {
            qDebug() << "Failed to reinitialize database.";
            return false;
        }
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO categories (name) VALUES (:name)");
    query.bindValue(":name", categoryName);

    if (!query.exec()) {
        qDebug() << "Failed to add category: " << query.lastError().text();
        return false;
    }

    qDebug() << "Category added successfully: " << categoryName;
    return true;
}




// Function to create a category-specific table
// This function creates a new table for the specified category
bool DbWorker::createCategorySpecificTable(const QString &categoryName) {

   if (!db.isOpen()) {
        qDebug() << "Database is not open. Attempting to reinitialize...";
        if (!initializeDatabase()) {
            qDebug() << "Failed to reinitialize database.";
            return false;
        }
    }

    QSqlQuery query(db);
    QString tableName = categoryName.toLower().replace(" ", "_");
    QString createTableQuery = QString("CREATE TABLE IF NOT EXISTS %1 (id INT AUTO_INCREMENT PRIMARY KEY)").arg(tableName);

    if (!query.exec(createTableQuery)){
        qDebug() << "Failed to create table for category: " << query.lastError().text();
        return false;
    }

    qDebug() << "Table created successfully for category: " << tableName;
    return true;

}


// Function to add a new column to a category-specific table
void DbWorker::addColumnToCategoryTable(const QString &tableName, const QString &columnName, const QString &dataType) {
    QSqlQuery query;
    QString alterTableQuery = QString("ALTER TABLE %1 ADD COLUMN %2 %3").arg(tableName, columnName, dataType);

    if (!query.exec(alterTableQuery)) {
        emit databaseSetupFinished(false, query.lastError().text());
    } else {
        emit databaseSetupFinished(true, QString("Column '%1' added to table '%2'.").arg(columnName, tableName));
    }
}





