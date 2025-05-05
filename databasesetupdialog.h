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

private:
    Ui::DatabaseSetupDialog *ui;
};

#endif // DATABASESETUPDIALOG_H
