#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("CRC Calculator ver " + QString::number(MAJOR_VERSION) + '.' + QString::number(MINOR_VERSION));


    ui->CRC_Res_Bin_groupBox->setLayout(bit_set.layout());
}



MainWindow::~MainWindow()
{
    delete ui;
}
