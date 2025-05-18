#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dbworker.h"
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &organizationName, QWidget *parent = nullptr);
    ~MainWindow();

    void setOrganizationName(const QString &organizationName);
private:
    Ui::MainWindow *ui;
    DbWorker *worker;
    QThread *workerThread;
};
#endif // MAINWINDOW_H
