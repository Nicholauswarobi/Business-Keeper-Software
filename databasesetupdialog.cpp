#include "databasesetupdialog.h"
#include "ui_databasesetupdialog.h"
#include <QMessageBox>
#include <QDebug>

DatabaseSetupDialog::DatabaseSetupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseSetupDialog),
    workerThread(new QThread(this)),
    worker(new DbWorker())
{
    ui->setupUi(this);

    // Move worker to a separate thread
    worker->moveToThread(workerThread);

    // Connect signals and slots
    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &DatabaseSetupDialog::setupDatabase, worker, &DbWorker::setupDatabase);
    connect(worker, &DbWorker::databaseSetupFinished, this, &DatabaseSetupDialog::onDatabaseSetupFinished);
    connect(ui->Configure_pushButton, &QPushButton::clicked, this, &DatabaseSetupDialog::on_Configure_pushButton_clicked);

    // Start the worker thread
    workerThread->start();
}

DatabaseSetupDialog::~DatabaseSetupDialog()
{
    workerThread->quit();
    workerThread->wait();
    delete ui;
}

QString DatabaseSetupDialog::getHost() const {
    return ui->HostName_lineEdit->text().trimmed();
}

QString DatabaseSetupDialog::getUser() const {
    return ui->Username_lineEdit->text().trimmed();
}

QString DatabaseSetupDialog::getPassword() const {
    return ui->Password_lineEdit->text().trimmed();
}

QString DatabaseSetupDialog::getDbName() const {
    return ui->DatabaseName_lineEdit->text().trimmed();
}

QString DatabaseSetupDialog::getOrganizationName() const {
    return ui->OrganizationName_lineEdit->text().trimmed();
}

void DatabaseSetupDialog::on_Configure_pushButton_clicked()
{
    qDebug() << "Configure button clicked.";

    QString host = ui->HostName_lineEdit->text();
    QString user = ui->Username_lineEdit->text();
    QString password = ui->Password_lineEdit->text();
    QString dbName = ui->DatabaseName_lineEdit->text();
    bool createIfNotExist = ui->NewDB_Checkbox->isChecked();

    qDebug() << "Host:" << host << "User:" << user << "DB Name:" << dbName << "Create DB:" << createIfNotExist;

    emit setupDatabase(host, user, password, dbName, createIfNotExist);
}

void DatabaseSetupDialog::onDatabaseSetupFinished(bool success, const QString &message)
{
    if (success) {
        accept(); // Close the dialog and proceed to the main window
    } else {
        QMessageBox::critical(this, "Database Setup Failed", message);
        qDebug() << "Database setup failed with message:" << message;
    }
}



