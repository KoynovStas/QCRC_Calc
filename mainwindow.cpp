#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("CRC Calculator ver " + QString::number(MAJOR_VERSION) + '.' + QString::number(MINOR_VERSION));


    ui->CRC_Res_Bin_groupBox->setLayout(bit_set.layout());


    Prepare_CRC_Param_comboBox();


    CRC_Param_to_GUI();


    //Signal/Slots for Wrap word checkBox
    QObject::connect(ui->Hex_tab_WrapWord_checkBox,  SIGNAL(stateChanged(int)),
                     this, SLOT(Hex_tab_WrapWord_checkBox_stateChanged(int)) );

    QObject::connect(ui->Text_tab_WrapWord_checkBox,  SIGNAL(stateChanged(int)),
                     this, SLOT(Text_tab_WrapWord_checkBox_stateChanged(int)) );



    QObject::connect(ui->CRC_Param_comboBox,  SIGNAL(currentIndexChanged(int)),
                     this, SLOT(selected_index_CRC_in_comboBox(int)) );


    QObject::connect(&qucrc,  SIGNAL(index_changed(uint32_t)),
                     this, SLOT(set_index_CRC_in_comboBox(uint32_t)) );
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



void MainWindow::selected_index_CRC_in_comboBox(int new_index)
{
    if( new_index == 0 )
        return;  // for Custom no action


    qucrc.set_index(new_index);
    CRC_Param_to_GUI();
}



void MainWindow::set_index_CRC_in_comboBox(uint32_t new_index)
{
    ui->CRC_Param_comboBox->setCurrentIndex(new_index);
}



void MainWindow::CRC_Param_to_GUI()
{
    ui->CRC_Bits_spinBox->setValue(qucrc.get_bits());

    ui->CRC_Poly_lineEdit->setText(   QString::number(qucrc.get_poly(),    16) );
    ui->CRC_Init_lineEdit->setText(   QString::number(qucrc.get_init(),    16) );
    ui->CRC_XorOut_lineEdit->setText( QString::number(qucrc.get_xor_out(), 16) );
    ui->CRC_Check_lineEdit->setText(  QString::number(qucrc.get_check(),   16) );

    ui->CRC_RefIn_checkBox->setChecked(qucrc.get_ref_in());
    ui->CRC_RefOut_checkBox->setChecked(qucrc.get_ref_out());
}



void MainWindow::Prepare_CRC_Param_comboBox()
{
    ui->CRC_Param_comboBox->clear();

    for( size_t i = 0; i < QuCRC_t::CRC_List.size(); i++)
    {
        QString item;
        CRC_Param_Info crc_info = QuCRC_t::CRC_List[i];

        item = crc_info.name;

//        item += "  Bits: "     + QString::number(crc_info.bits);
//        item += "  Poly: 0x"   + QString::number(crc_info.poly, 16);
//        item += "  Init: 0x"   + QString::number(crc_info.init, 16);
//        item += "  RefIn: "    + QString::number(crc_info.ref_in);
//        item += "  RefOut: "   + QString::number(crc_info.ref_out);
//        item += "  XorOut: 0x" + QString::number(crc_info.xor_out, 16);

        ui->CRC_Param_comboBox->addItem(item);
    }


    ui->CRC_Param_comboBox->setCurrentIndex( qucrc.get_index() );
}
