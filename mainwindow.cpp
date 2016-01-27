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


    // Signal/Slots for Wrap word checkBox
    QObject::connect(ui->Hex_tab_WrapWord_checkBox,  SIGNAL(stateChanged(int)),
                     this, SLOT(Hex_tab_WrapWord_checkBox_stateChanged(int)) );

    QObject::connect(ui->Text_tab_WrapWord_checkBox,  SIGNAL(stateChanged(int)),
                     this, SLOT(Text_tab_WrapWord_checkBox_stateChanged(int)) );


    // Signal/Slots for CRC_Param_comboBox (User select new index)
    QObject::connect(ui->CRC_Param_comboBox,  SIGNAL(currentIndexChanged(int)),
                     this, SLOT(selected_index_CRC_in_comboBox(int)) );

    QObject::connect(&qucrc,  SIGNAL(index_changed(uint32_t)),
                     this, SLOT(set_index_CRC_in_comboBox(uint32_t)) );


    // Signal/Slots User changed CRC Param in GUI
    QObject::connect(ui->CRC_Bits_spinBox,  SIGNAL(valueChanged(int)),
                     this, SLOT(CRC_Param_from_GUI()) );

    QObject::connect(ui->CRC_RefIn_checkBox,  SIGNAL(stateChanged(int)),
                     this, SLOT(CRC_Param_from_GUI()) );

    QObject::connect(ui->CRC_RefOut_checkBox,  SIGNAL(stateChanged(int)),
                     this, SLOT(CRC_Param_from_GUI()) );

    QObject::connect(ui->CRC_Poly_lineEdit,  SIGNAL(textChanged(const QString &)),
                     this, SLOT(CRC_Param_from_GUI()) );

    QObject::connect(ui->CRC_Init_lineEdit,  SIGNAL(textChanged(const QString &)),
                     this, SLOT(CRC_Param_from_GUI()) );

    QObject::connect(ui->CRC_XorOut_lineEdit,  SIGNAL(textChanged(const QString &)),
                     this, SLOT(CRC_Param_from_GUI()) );
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



// (User changed CRC Param in GUI. We must find new index for CRC_Param_comboBox)
void MainWindow::set_index_CRC_in_comboBox(uint32_t new_index)
{
    ui->CRC_Param_comboBox->setCurrentIndex(new_index);
}



void MainWindow::CRC_Param_to_GUI()
{
    ui->CRC_Bits_spinBox->setValue(qucrc.get_bits());

    ui->CRC_Poly_lineEdit->setText(  "0x" + QString::number(qucrc.get_poly(),    16).toUpper() );
    ui->CRC_Init_lineEdit->setText(  "0x" + QString::number(qucrc.get_init(),    16).toUpper() );
    ui->CRC_XorOut_lineEdit->setText("0x" + QString::number(qucrc.get_xor_out(), 16).toUpper() );
    ui->CRC_Check_lineEdit->setText( "0x" + QString::number(qucrc.get_check(),   16).toUpper() );

    ui->CRC_RefIn_checkBox->setChecked(qucrc.get_ref_in());
    ui->CRC_RefOut_checkBox->setChecked(qucrc.get_ref_out());
}



void MainWindow::CRC_Param_from_GUI()
{
    qucrc.set_bits( ui->CRC_Bits_spinBox->value() );


    qucrc.set_poly( ui->CRC_Poly_lineEdit->text().toULongLong(NULL, 16) );
    qucrc.set_init( ui->CRC_Init_lineEdit->text().toULongLong(NULL, 16) );
    qucrc.set_xor_out( ui->CRC_XorOut_lineEdit->text().toULongLong(NULL, 16) );


    qucrc.set_ref_in( ui->CRC_RefIn_checkBox->isChecked() );
    qucrc.set_ref_out( ui->CRC_RefOut_checkBox->isChecked() );
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
