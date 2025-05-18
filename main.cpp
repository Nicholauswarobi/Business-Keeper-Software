#include "mainwindow.h"
#include "databasesetupdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DatabaseSetupDialog dbDialog;
    if (dbDialog.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return app.exec();
    }

    return 0;
}
