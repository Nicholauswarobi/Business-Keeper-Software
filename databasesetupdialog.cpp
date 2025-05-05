#include "databasesetupdialog.h"
#include "ui_databasesetupdialog.h"

DatabaseSetupDialog::DatabaseSetupDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DatabaseSetupDialog)
{
    ui->setupUi(this);
}

DatabaseSetupDialog::~DatabaseSetupDialog()
{
    delete ui;
}

void DatabaseSetupDialog::on_Configure_pushButton_clicked()
{

}

