#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QtSql>

class DbWorker : public QObject
{
    Q_OBJECT
public:
    explicit DbWorker(QObject *parent = nullptr);
    ~DbWorker();

    bool initializeDatabase();
    bool doesDatabaseExist();

    
    
    // void createCategoriesTable();
    bool addCategory(const QString &categoryName);
    bool createCategorySpecificTable(const QString &categoryName);
    void addColumnToCategoryTable(const QString &tableName, const QString &columnName, const QString &dataType);
    
    bool connectToDatabase(const QString &host, const QString &user,
        const QString &password, const QString &dbName);


public slots:
    void setupDatabase(const QString &host, const QString &user,
                       const QString &password, const QString &dbName, bool createIfNotExist);

signals:
    void databaseSetupFinished(bool success, const QString &message);

private:
    QSqlDatabase db;
    QSettings settings;

};

#endif // DBWORKER_H
