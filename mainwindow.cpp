#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("CRC Calculator ver " + QString::number(MAJOR_VERSION) + '.' + QString::number(MINOR_VERSION));


    ui->CRC_Res_Bin_groupBox->setLayout(bit_set.layout());


    //Signal/Slots for Wrap word checkBox
    QObject::connect(ui->Hex_tab_WrapWord_checkBox,  SIGNAL(stateChanged(int)),
                     this, SLOT(Hex_tab_WrapWord_checkBox_stateChanged(int)) );

    QObject::connect(ui->Text_tab_WrapWord_checkBox,  SIGNAL(stateChanged(int)),
                     this, SLOT(Text_tab_WrapWord_checkBox_stateChanged(int)) );
}



MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::Hex_tab_WrapWord_checkBox_stateChanged(int state)
{
    if( state )
        ui->Hex_tab_plainTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    else
        ui->Hex_tab_plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
}



void MainWindow::Text_tab_WrapWord_checkBox_stateChanged(int state)
{
    if( state )
        ui->Text_tab_plainTextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
    else
        ui->Text_tab_plainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
}
