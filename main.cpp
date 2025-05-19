#include "mainwindow.h"
#include "databasesetupdialog.h"
#include "dbworker.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    // load saved configuration
    // QSettings settings("BusinessKeeper", "AppConfig");
    // QString host = settings.value("Database/Host", "").toString();
    // QString user = settings.value("Database/User", "").toString();
    // QString password = settings.value("Database/Password", "").toString();
    // QString dbName = settings.value("Database/Name", "").toString();
    // QString organizationName = settings.value("Organization/Name", "").toString();

    DbWorker dbWorker;

    if (dbWorker.initializeDatabase() && dbWorker.doesDatabaseExist()){
    QSettings settings("BusinessKeeper", "AppConfig");
    QString organizationName = settings.value("Organization/Name", "").toString();

    MainWindow w(organizationName);
    w.show();

    return app.exec();


    }

    // Check if configuration exists

 /*   if (!host.isEmpty() && !user.isEmpty() && !dbName.isEmpty() &&
        !organizationName.isEmpty() && dbWorker.doesDatabaseExist(host, user, password, dbName)){
        // If configuration exists and the database is accessible, open the main window
        MainWindow w(organizationName);
        w.show();

        return app.exec();

    }*/

    else{
        // If configuration does not exist or the database is inaccessible, show the configuration dialog
        DatabaseSetupDialog dbDialog;
        if (dbDialog.exec() == QDialog::Accepted){
            // Save the configuration after successfull setup
            QSettings settings("BusinessKeeper", "AppConfig");
            settings.setValue("Database/Host", dbDialog.getHost());
            settings.setValue("Database/User", dbDialog.getUser());
            settings.setValue("Database/Password", dbDialog.getPassword());
            settings.setValue("Database/Name", dbDialog.getDbName());
            settings.setValue("Organization/Name", dbDialog.getOrganizationName());


            MainWindow w(dbDialog.getOrganizationName());
            w.show();
            return app.exec();
        }
    }


    return 0;
}
