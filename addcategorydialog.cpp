#include "addcategorydialog.h"
#include "ui_addcategorydialog.h"
#include <QMessageBox>

AddCategoryDialog::AddCategoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCategoryDialog)
{
    ui->setupUi(this);
}

AddCategoryDialog::~AddCategoryDialog()
{
    delete ui;
}

void AddCategoryDialog::on_AddCategory_pushButton_clicked()
{
    QString tableName = ui->CategoryTableNAme_lineEdit->text().trimmed();
    QStringList columns = ui->ColName_lineEdit->text().split(",", Qt::SkipEmptyParts);

    if (tableName.isEmpty() || columns.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please provide a valid table name and at least one column.");
        return;
    }

    emit createCategory(tableName, columns);
    accept();
}

