#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QGraphicsDropShadowEffect"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // List of Cards Frames
    QList<QFrame*> cards = {
                              ui->DashBoardLogoframe};

    // Apply drop down shadow
    for(QFrame* card : cards){
        QGraphicsDropShadowEffect* shadow= new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(40);
        shadow->setOffset(12, 12);
        shadow->setColor(QColor(0, 0, 0, 150));
        card->setGraphicsEffect(shadow);

    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
