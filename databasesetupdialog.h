#ifndef DATABASESETUPDIALOG_H
#define DATABASESETUPDIALOG_H

#include <QDialog>

namespace Ui {
class DatabaseSetupDialog;
}

class DatabaseSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DatabaseSetupDialog(QWidget *parent = nullptr);
    ~DatabaseSetupDialog();

private slots:
    void on_Configure_pushButton_Accepted();

private:
    Ui::DatabaseSetupDialog *ui;
    bool testConnecttion(const QString &host, const QString &user, const QString &pass, const QString &db, int port);
};

#endif // DATABASESETUPDIALOG_H
