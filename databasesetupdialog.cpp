#include "databasesetupdialog.h"
#include "ui_databasesetupdialog.h"
#include <QSettings>
#include <QMessageBox>
#include <QSqlDatabase>

DatabaseSetupDialog::DatabaseSetupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DatabaseSetupDialog)
{
    ui->setupUi(this);

    // Set default values
    ui->OrganizationName_lineEdit->setText("BusinessKeeper");
    ui->AppName_lineEdit->setText("MyCompay");
    ui->Port_lineEdit->setText("3309");
}

DatabaseSetupDialog::~DatabaseSetupDialog()
{
    delete ui;
}

QString DatabaseSetupDialog::organizationName() const {
    return ui->OrganizationName_lineEdit->text().trimmed();
}

QString DatabaseSetupDialog::applicationName() const {
    return ui->AppName_lineEdit->text().trimmed();
}


void DatabaseSetupDialog::on_Configure_pushButton_Accepted()
{
    QString orgName = organizationName();
    QString appName = applicationName();

}

