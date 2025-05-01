#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QGraphicsDropShadowEffect"
#include "QPropertyAnimation"
#include "QParallelAnimationGroup"
#include "QStackedWidget"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Navigate to Page when pushButton is clicked
    connect(ui->Dashboard_pushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->Dashboard_page);
    });

    connect(ui->Sales_pushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->Sales_page);
    });


    connect(ui->Reports_pushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->Reports_page);
    });


    connect(ui->Stock_pushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->Stock_page);
    });


    connect(ui->Purchases_pushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->Purchases_page);
    });

    connect(ui->Suppliers_pushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->Suppliers_page);
    });

    connect(ui->Settings_pushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->Settings_page);
    });

    connect(ui->About_pushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->About_page);
    });

    connect(ui->Expenses_pushButton, &QPushButton::clicked, this, [=](){
        ui->stackedWidget->setCurrentWidget(ui->Expenses_page);
    });


    // List of Cards Frames
    QList<QWidget*> cards = {
                              ui->DashBoardLogoframe, ui->Revenue_Card_frame,
        ui->Expenses_Card_frame, ui->Profit_Card_frame, ui->StockIN_Card_frame,
        ui->StockOUT_frame, ui->StockRemain_frame};

    // Apply drop down shadow
    for(QWidget* card : cards){
        QGraphicsDropShadowEffect* shadow= new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(40);
        shadow->setOffset(6, 6);
        shadow->setColor(QColor(0, 120, 255, 150));
        card->setGraphicsEffect(shadow);

    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::animatePageSwitch(QWidget* from, QWidget* to, int direction){
    int width = ui->stackedWidget->width();

    // Position the target page
    to->move(direction * width, 0);
    to->show();

    // Animate the movement
    QPropertyAnimation* animFrom = new QPropertyAnimation(from, "pos");
    animFrom->setDuration(300);
    animFrom->setStartValue(from->pos());
    animFrom->setEndValue(QPoint(-direction * width, 0));

    QPropertyAnimation* animTo = new QPropertyAnimation(to, "pos");
    animTo->setDuration(300);
    animTo->setStartValue(to->pos());
    animTo->setEndValue(QPoint(0, 0));


















}
