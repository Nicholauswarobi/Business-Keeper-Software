#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QGraphicsDropShadowEffect"
#include "QIcon"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set Window Icon
    this->setWindowIcon(QIcon(":/Icons/Image/BKSLogo.ico"));

    // Set Window Title
    this->setWindowTitle("Business Keeper Software");

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
        shadow->setOffset(8, 8);
        shadow->setColor(QColor(0, 120, 255, 150));
        card->setGraphicsEffect(shadow);

    }

    // Apply this outside
    QList<QWidget*> frameCard = {ui->Header_widget, ui->SystemTitle_frame};

    for(QWidget* fcard: frameCard){
        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
        shadow->setBlurRadius(20);
        shadow->setColor(QColor(14, 210, 179, 150));
        shadow->setOffset(8, 8);

        fcard->setGraphicsEffect(shadow);
    }



}



MainWindow::~MainWindow()
{
    delete ui;
}


