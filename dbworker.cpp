#include "dbworker.h"
#include <QDebug>
#include <stdexcept>

DbWorker::DbWorker(QObject *parent) : QObject(parent) {}

void DbWorker::setupDatabase(const QString &host, const QString &user,
                             const QString &password, const QString &dbName, bool createIfNotExist) {
    try {
        qDebug() << "Starting database setup...";
        qDebug() << "Available drivers:" << QSqlDatabase::drivers();

        // Create a unique connection name for this thread
        QString connectionName = QString("db_connection_%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
        db.setHostName(host);
        db.setUserName(user);
        db.setPassword(password);

        if (createIfNotExist) {
            db.setDatabaseName("");
            if (!db.open()) {
                throw std::runtime_error(QString("Failed to connect to MySQL server: %1").arg(db.lastError().text()).toStdString());
            }

            qDebug() << "Connected to MySQL server.";
            QSqlQuery query(db);
            if (!query.exec(QString("CREATE DATABASE IF NOT EXISTS %1").arg(dbName))) {
                throw std::runtime_error(QString("Failed to create database: %1").arg(query.lastError().text()).toStdString());
            }
            qDebug() << "Database created successfully.";
        }

        db.setDatabaseName(dbName);
        if (!db.open()) {
            throw std::runtime_error(QString("Failed to connect to database: %1").arg(db.lastError().text()).toStdString());
        }

        qDebug() << "Connected to database successfully.";

        // Create the categories table
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

        // Remove the database connection
        QSqlDatabase::removeDatabase(connectionName);
    } catch (const std::exception &e) {
        qDebug() << "Exception caught in setupDatabase:" << e.what();
        emit databaseSetupFinished(false, QString("Exception: %1").arg(e.what()));
    } catch (...) {
        qDebug() << "Unknown exception caught in setupDatabase.";
        emit databaseSetupFinished(false, "Unknown error occurred during database setup.");
    }
}

bool DbWorker::connectToDatabase(const QString &host, const QString &user,
                                 const QString &password, const QString &dbName) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(password);
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
        return false;
    }

    qDebug() << "Database connection established.";
    return true;
}

void DbWorker::createCategoriesTable() {
    QSqlQuery query;
    QString createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS categories (
            id INT AUTO_INCREMENT PRIMARY KEY,
            name VARCHAR(255) UNIQUE NOT NULL
        )
    )";

    if (!query.exec(createTableQuery)) {
        emit databaseSetupFinished(false, query.lastError().text());
    } else {
        emit databaseSetupFinished(true, "Categories table created successfully.");
    }
}

void DbWorker::createCategorySpecificTable(const QString &tableName) {
    QSqlQuery query;
    QString createTableQuery = QString("CREATE TABLE IF NOT EXISTS %1 (id INT AUTO_INCREMENT PRIMARY KEY)").arg(tableName);

    if (!query.exec(createTableQuery)) {
        emit databaseSetupFinished(false, query.lastError().text());
    } else {
        emit databaseSetupFinished(true, QString("Table '%1' created successfully.").arg(tableName));
    }
}

void DbWorker::addColumnToCategoryTable(const QString &tableName, const QString &columnName, const QString &dataType) {
    QSqlQuery query;
    QString alterTableQuery = QString("ALTER TABLE %1 ADD COLUMN %2 %3").arg(tableName, columnName, dataType);

    if (!query.exec(alterTableQuery)) {
        emit databaseSetupFinished(false, query.lastError().text());
    } else {
        emit databaseSetupFinished(true, QString("Column '%1' added to table '%2'.").arg(columnName, tableName));
    }
}

bool DbWorker::doesDatabaseExist(const QString &host, const QString &user,
                        const QString &password, const QString &dbName){
    QString connectionName = QString("check_db_connection_%1").arg(reinterpret_cast<quintptr>(QThread::currentThreadId()));
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL", connectionName);
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(password);
    db.setDatabaseName(dbName);

    if (db.open()){
        qDebug()<< "Database exists and connection successfully.";
        QSqlDatabase::removeDatabase(connectionName);
        return true;
    }else{
        qDebug()<< "Database does not exist and connection failed." << db.lastError().text();
        QSqlDatabase::removeDatabase(connectionName);
        return false;
    }
                            
}
