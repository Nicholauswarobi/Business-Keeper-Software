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

    // Default local database
    ui->Local_radioButton->setChecked(true);
    ui->Cloud_radioButton->setVisible(false);

    connect(ui->Local_radioButton, &QRadioButton::toggled, this, [this](bool checked){
        ui->
    })

    // Set default values
    ui->OrganizationName_lineEdit->setText("MyCompany");
    ui->AppName_lineEdit->setText("BusinessKeeper");
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
    QString host = ui->HostName_lineEdit->text();
    QString user = ui->Username_lineEdit->text();
    QString passW = ui->Password_lineEdit->text();
    QString db = ui->DatabaseName_lineEdit->text();
    int port = ui->Port_lineEdit->text().toInt();

    if (orgName.isEmpty() || appName.isEmpty()){
        QMessageBox::warning(this, "Invalid Input", "Organization and Application names can not be empty!");
        return;
    }

    if (testConnecttion(host, user, passW, db, port)){
        QSettings settings(orgName, appName);
        settings.setValue("db/host", host);
        settings.setValue("db/user", user);
        settings.setValue("db/passW", passW);
        settings.setValue("db/name", db);
        settings.setValue("db/port", port);
        accept();
    }

    else{
        QMessageBox::critical(this, "Connection Failed", "Could not connect to the database!");
    }
}

bool DatabaseSetupDialog::testConnecttion(const QString &host, const QString &user, const QString &pass, const QString &db, int port){
    QSqlDatabase testDb = QSqlDatabase::addDatabase("QMYSQL", "TestConnection");
    testDb.setHostName(host);
    testDb.setUserName(user);
    testDb.setPassword(pass);
    testDb.setDatabaseName(db);
    testDb.setPort(port);

    bool success = testDb.open();
    testDb.close();
    QSqlDatabase::removeDatabase("TestConnection");
    return success;
}

