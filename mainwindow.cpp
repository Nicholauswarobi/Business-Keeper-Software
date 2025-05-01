#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QGraphicsDropShadowEffect"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // List of Cards Frames
    QList<QWidget*> cards = {
                              ui->DashBoardLogoframe, ui->Revenue_Card_frame,
        ui->Expenses_Card_frame, ui->Profit_Card_frame, ui->StockIN_Card_frame,
        ui->StockOUT_frame, ui->StockRemain_frame};

    // Apply drop down shadow
    for(QWidget* card : cards){
        QGraphicsDropShadowEffect* shadow= new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(40);
        shadow->setOffset(0, 6);
        shadow->setColor(QColor(0, 120, 255, 150));
        card->setGraphicsEffect(shadow);

    }
}



MainWindow::~MainWindow()
{
    delete ui;
}
