#ifndef ADDCATEGORYDIALOG_H
#define ADDCATEGORYDIALOG_H

#include <QDialog>

namespace Ui {
class AddCategoryDialog;
}

class AddCategoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddCategoryDialog(QWidget *parent = nullptr);
    ~AddCategoryDialog();

    QString getCategoryName() const;


private slots:
    void on_AddCategory_pushButton_clicked();

private:
    Ui::AddCategoryDialog *ui;
};

#endif // ADDCATEGORYDIALOG_H
