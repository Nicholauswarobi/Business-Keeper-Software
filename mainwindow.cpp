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
        QWidget* from = ui->stackedWidget->currentWidget();
        QWidget* to = ui->Dashboard_page;
        animatePageSwitch(from, to, -1);    // -1 = slide left
    });


    connect(ui->Sales_pushButton, &QPushButton::clicked, this, [=](){
        QWidget* from = ui->stackedWidget->currentWidget();
        QWidget* to = ui->Sales_page;
        animatePageSwitch(from, to, 1);    // -1 = slide right
    });


    connect(ui->Reports_pushButton, &QPushButton::clicked, this, [=](){
        QWidget* from = ui->stackedWidget->currentWidget();
        QWidget* to = ui->Reports_page;
        animatePageSwitch(from, to, -1);    // -1 = slide right
    });



    connect(ui->Expenses_pushButton, &QPushButton::clicked, this, [=](){
        QWidget* from = ui->stackedWidget->currentWidget();
        QWidget* to = ui->Expenses_page;
        animatePageSwitch(from, to, 1);    // -1 = slide right
    });



    connect(ui->About_pushButton, &QPushButton::clicked, this, [=](){
        QWidget* from = ui->stackedWidget->currentWidget();
        QWidget* to = ui->About_page;
        animatePageSwitch(from, to, -1);    // -1 = slide right
    });



    connect(ui->Stock_pushButton, &QPushButton::clicked, this, [=](){
        QWidget* from = ui->stackedWidget->currentWidget();
        QWidget* to = ui->Stock_page;
        animatePageSwitch(from, to, 1);    // -1 = slide right
    });



    connect(ui->Purchases_pushButton, &QPushButton::clicked, this, [=](){
        QWidget* from = ui->stackedWidget->currentWidget();
        QWidget* to = ui->Purchases_page;
        animatePageSwitch(from, to, -1);    // -1 = slide right
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

    QParallelAnimationGroup* group = new QParallelAnimationGroup;
    group->addAnimation(animFrom);
    group->addAnimation(animTo);

    connect(group, &QParallelAnimationGroup::finished, this, [=](){
        ui->stackedWidget->setCurrentWidget(to);
    });

    group->start(QAbstractAnimation::DeleteWhenStopped);


}











