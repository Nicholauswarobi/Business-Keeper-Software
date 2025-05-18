#ifndef DBWORKER_H
#define DBWORKER_H

#include <QObject>
#include <QtSql>

class DbWorker : public QObject
{
    Q_OBJECT
public:
    explicit DbWorker(QObject *parent = nullptr);

public slots:
    void setupDatabase(const QString &host, const QString &user,
                       const QString &password, const QString &dbName, bool createIfNotExist);
    void createCategoriesTable();
    void createCategorySpecificTable(const QString &tableName);
    void addColumnToCategoryTable(const QString &tableName, const QString &columnName, const QString &dataType);

signals:
    void databaseSetupFinished(bool success, const QString &message);

private:
    bool connectToDatabase(const QString &host, const QString &user,
                           const QString &password, const QString &dbName);
};

#endif // DBWORKER_H
