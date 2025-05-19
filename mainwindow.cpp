#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QGraphicsDropShadowEffect"
#include "QIcon"
#include "addcategorydialog.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

MainWindow::MainWindow(const QString &organizationName, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setOrganizationName(organizationName);

    // Set Window Icon
    this->setWindowIcon(QIcon(":/Icons/Image/BKSLogo.ico"));

    // Set Window Title
    this->setWindowTitle("Business Keeper Software");

    // BUTTON connections
    connect(ui->New_Product_Category_pushButton, &QPushButton::clicked, this, &MainWindow::on_New_Product_Category_pushButton_clicked);

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
        shadow->setBlurRadius(100);
        shadow->setColor(QColor(14, 210, 179, 150));
        shadow->setOffset(0, 8);

        fcard->setGraphicsEffect(shadow);
    }

    workerThread = new QThread(this);
    worker = new DbWorker();
    worker->moveToThread(workerThread);

    connect(workerThread, &QThread::finished, worker, &QObject::deleteLater);
    workerThread->start();
}

void MainWindow::setOrganizationName(const QString &organizationName){
    if (ui->OrgName_Label){
        ui->OrgName_Label->setText(organizationName);
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_New_Product_Category_pushButton_clicked()
{
    AddCategoryDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted){
        QString categoryName = dialog.getCategoryName();

        if (categoryName.isEmpty()){
            QMessageBox::warning(this, "Invalid Input", "Category name can not be empty.");
            return;
        }

        // add the category to the database
        DbWorker dbWorker;
        if (!dbWorker.addCategory(categoryName)){
            QMessageBox::critical(this, "Error", "Failed to add category to the database.");
            return;
        }

        // Create table for the category
        if (!dbWorker.createCategorySpecificTable(categoryName)){
            QMessageBox::critical(this, "Error", "Failed to create table for category.");
            return;
        }

        QMessageBox::information(this, "Success", "Category added and table created successfully.");
    }
}

