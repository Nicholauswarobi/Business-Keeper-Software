#ifndef DATABASESETUPDIALOG_H
#define DATABASESETUPDIALOG_H

#include <QDialog>
#include <QThread>
#include "dbworker.h"

namespace Ui {
class DatabaseSetupDialog;
}

class DatabaseSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseSetupDialog(QWidget *parent = nullptr);
    ~DatabaseSetupDialog();

    QString getHost() const;
    QString getUser() const;
    QString getPassword() const;
    QString getDbName() const;
    QString getOrganizationName() const;

signals:
    void setupDatabase(const QString &host, const QString &user,
                       const QString &password, const QString &dbName, bool createIfNotExist);

private slots:
    void on_Configure_pushButton_clicked();
    void onDatabaseSetupFinished(bool success, const QString &message);


private:
    Ui::DatabaseSetupDialog *ui;
    QThread *workerThread;
    DbWorker *worker;
};

#endif // DATABASESETUPDIALOG_H
