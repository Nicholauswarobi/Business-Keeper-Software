#include "mainwindow.h"
#include "databasesetupdialog.h"
#include <QSettings>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Check if settings already exists
    QString defaultOrg = "MyCompany";
    QString defaultApp = "BusinessKeeper";

    QSettings settings(defaultOrg, defaultApp);
    if(!settings.contains("db/host")){
        DatabaseSetupDialog setupDialog;
        if(setupDialog.exec() != QDialog::Accepted)
            return 0;
    }




    MainWindow w;
    w.show();
    return a.exec();
}
