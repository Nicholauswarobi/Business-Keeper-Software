#include "mainwindow.h"
#include "databasesetupdialog.h"
#include <QSettings>
#include <QScopedPointer>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // Scoped pointer for automatic cleanup
    QScopedPointer<QSettings> settings;

    if(QSettings("BusinessKeeper", "App").contains("db/host")){
        settings.reset(new QSettings("BusinessKeeper", "App"));
    }else{
        DatabaseSetupDialog setupDialog;
        if(setupDialog.exec() == QDialog::Accepted){
            settings.reset(new QSettings(
                setupDialog.organizationName(),
                setupDialog.applicationName()
            ));
        }else{
            return 0;
        }
    }


    MainWindow w;
    w.show();
    return a.exec();
}
