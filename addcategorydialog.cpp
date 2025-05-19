#include "addcategorydialog.h"
#include "ui_addcategorydialog.h"
#include <QMessageBox>

AddCategoryDialog::AddCategoryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCategoryDialog)
{
    ui->setupUi(this);
    connect(ui->AddCategory_pushButton, &QPushButton::clicked, this, &AddCategoryDialog::accept);
}

AddCategoryDialog::~AddCategoryDialog()
{
    delete ui;
}

void AddCategoryDialog::on_AddCategory_pushButton_clicked(){
    accept();
}


QString AddCategoryDialog::getCategoryName() const{
    return ui->CategoryTableNAme_lineEdit->text().trimmed();
}
