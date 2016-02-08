#include "mainwindow.h"
#include "ui_mainwindow.h"





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),

    crc_result(0),
    select_index_done(true)
{
    ui->setupUi(this);

    setWindowTitle("CRC Calculator ver " + QString::number(MAJOR_VERSION) + '.' + QString::number(MINOR_VERSION));

    ui->CRC_Res_Bin_groupBox->setLayout(bit_set.layout());


    Prepare_CRC_Param_comboBox();
    Prepare_Text_Encoding_comboBox();
    Prepare_StatusBar();

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

    QObject::connect(&qucrc,  SIGNAL(param_changed()),
                     this, SLOT(CRC_Param_to_GUI()) );


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


    // Signal changed base for Result CRC
    QObject::connect(ui->CRC_Res_Base_spinBox,  SIGNAL(valueChanged(int)),
                     this, SLOT(set_Result_CRC_for_custom_base()) );



    QObject::connect(ui->CRC_Data_tabs, SIGNAL(currentChanged(int)),
                     this, SLOT(calculate_CRC()) );



    Prepare_Hex_calc();
    Prepare_Text_calc();
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
    // if new_index == Custom(0) or index already set - no action
    if( (new_index == 0) || ((uint32_t)new_index == qucrc.get_index()) )
        return;


    if( !select_index_done)
        return;


    set_GUI_mode(false);


    select_index_done = false;

    qucrc.set_index(new_index);

    select_index_done = true;
}



// (User changed CRC Param in GUI. We must find new index for CRC_Param_comboBox)
void MainWindow::set_index_CRC_in_comboBox(uint32_t new_index)
{
    if( !select_index_done )
        return;

    set_GUI_mode(false);


    select_index_done = false;

    ui->CRC_Param_comboBox->setCurrentIndex(new_index);

    select_index_done = true;
}



void MainWindow::CRC_Param_to_GUI()
{
    ui->CRC_Bits_spinBox->setValue(qucrc.get_bits());

    ui->CRC_Poly_lineEdit->setText(  "0x" + QString::number(qucrc.get_poly(),    16).toUpper() );
    ui->CRC_Init_lineEdit->setText(  "0x" + QString::number(qucrc.get_init(),    16).toUpper() );
    ui->CRC_XorOut_lineEdit->setText("0x" + QString::number(qucrc.get_xor_out(), 16).toUpper() );
    ui->CRC_Check_lineEdit->setText( "0x" + QString::number(qucrc.get_check(),   16).toUpper() );
    ui->CRC_Mask_lineEdit->setText(  "0x" + QString::number(qucrc.get_crc_mask(),16).toUpper() );
    ui->CRC_TopBit_lineEdit->setText("0x" + QString::number(qucrc.get_top_bit(), 16).toUpper() );

    ui->CRC_RefIn_checkBox->setChecked(qucrc.get_ref_in());
    ui->CRC_RefOut_checkBox->setChecked(qucrc.get_ref_out());
}



void MainWindow::CRC_Param_from_GUI()
{
    if( !select_index_done )
        return;

    set_GUI_mode(false);


    qucrc.set_bits( ui->CRC_Bits_spinBox->value() );

    qucrc.set_poly( ui->CRC_Poly_lineEdit->text().toULongLong(NULL, 16) );
    qucrc.set_init( ui->CRC_Init_lineEdit->text().toULongLong(NULL, 16) );
    qucrc.set_xor_out( ui->CRC_XorOut_lineEdit->text().toULongLong(NULL, 16) );

    qucrc.set_ref_in( ui->CRC_RefIn_checkBox->isChecked() );
    qucrc.set_ref_out( ui->CRC_RefOut_checkBox->isChecked() );
}



void MainWindow::set_Result_CRC(uint64_t value)
{
    set_GUI_mode(true);  // calculate done


    if( crc_result == value )
        return;

    crc_result = value;


    ui->CRC_Res_Hex_lineEdit->setText( "0x" + QString::number(value, 16).toUpper() );
    ui->CRC_Res_Dec_lineEdit->setText( QString::number(value, 10) );
    ui->CRC_Res_Oct_lineEdit->setText( QString::number(value, 8) );

    set_Result_CRC_for_custom_base();

    bit_set.set_value(value);
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



void MainWindow::Prepare_Text_Encoding_comboBox()
{
    ui->Text_tab_Encoding_comboBox->clear();


    for( int i = 0; i < Text_calc.Encodings.size(); i++)
    {
        ui->Text_tab_Encoding_comboBox->addItem(Text_calc.Encodings[i]);
    }

    ui->Text_tab_Encoding_comboBox->setCurrentIndex(0); //Default ASCII
}



void MainWindow::Prepare_StatusBar()
{
    status_label = new QLabel(this);
    status_label->setFixedWidth(this->width()/2);

    QLabel *URL_label = new QLabel(this);
    URL_label->setText("<a href=\"https://github.com/KoynovStas/QCRC_Calc/\">Repo on GitHub</a>");
    URL_label->setTextFormat(Qt::RichText);
    URL_label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    URL_label->setOpenExternalLinks(true);
    URL_label->setAlignment(Qt::AlignRight);

    ui->statusBar->addWidget(status_label, 1);
    ui->statusBar->addWidget(URL_label, 1);
}



void MainWindow::set_GUI_mode(bool mode)
{
    static QWidget *widget_in_focus = NULL;
    static bool old_mode = true;

    if( old_mode == mode )
        return;


    old_mode = mode;


    if( !mode )
        widget_in_focus = QApplication::focusWidget();


    ui->CRC_Param_groupBox->setEnabled(mode);
    ui->CRC_Data_groupBox->setEnabled(mode);


   if( mode && widget_in_focus )
        widget_in_focus->setFocus();  // restore focus
}



void MainWindow::set_Result_CRC_for_custom_base()
{
    ui->CRC_Res_Base_lineEdit->setText( QString::number(crc_result, ui->CRC_Res_Base_spinBox->value()).toUpper() );
}



void MainWindow::set_Result_CRC_for_Hex(uint64_t value)
{
    set_Result_CRC(value);


    show_stats(" Bytes: " + QString::number(Hex_calc.get_num_bytes(), 10) +
               " Words: " + QString::number(Hex_calc.get_num_words(), 10) );
}



void MainWindow::textChanged_for_Hex()
{
    static QString old_text;


    // Protection, if we disable (deactivate) widget plainTextEdit
    // comes textChanged signal, we do not need.
    if( old_text == ui->Hex_tab_plainTextEdit->toPlainText() )
        return;

    old_text = ui->Hex_tab_plainTextEdit->toPlainText();


    calculate_CRC_for_Hex();
}



void MainWindow::calculate_CRC_for_Hex()
{
    set_GUI_mode(false);

    Hex_calc.calculate(ui->Hex_tab_plainTextEdit->toPlainText());
}



void MainWindow::Hex_revers_chunk_checkBox_stateChanged(int state)
{
    set_GUI_mode(false);


    Hex_calc.set_revers_chunk(state == Qt::Checked);

    Hex_calc.calculate(ui->Hex_tab_plainTextEdit->toPlainText());
}



void MainWindow::Hex_revers_data_checkBox_stateChanged(int state)
{
    set_GUI_mode(false);


    Hex_calc.set_revers_data(state == Qt::Checked);

    Hex_calc.calculate(ui->Hex_tab_plainTextEdit->toPlainText());
}



void MainWindow::set_Result_CRC_for_Text(uint64_t value)
{
    set_Result_CRC(value);


    show_stats(" Bytes: " + QString::number(Text_calc.get_num_bytes(), 10) +
               " Lines: " + QString::number(Text_calc.get_num_lines(), 10) );
}



void MainWindow::textChanged_for_Text()
{
    static QString old_text;


    // Protection, if we disable (deactivate) widget plainTextEdit
    // comes textChanged signal, we do not need.
    if( old_text == ui->Text_tab_plainTextEdit->toPlainText() )
        return;

    old_text = ui->Text_tab_plainTextEdit->toPlainText();


    calculate_CRC_for_Text();
}



void MainWindow::selected_encodings_in_comboBox(int new_index)
{

    if(Text_calc.get_encoding_index() == (size_t)new_index)
        return;

    Text_calc.set_encoding_index(new_index);

    calculate_CRC_for_Text();
}



void MainWindow::selected_endline_in_comboBox(int new_index)
{
    if(Text_calc.end_line_format == new_index)
        return;

    Text_calc.end_line_format = (CRC_Calc_for_Text::EndLineFormat)new_index;

    calculate_CRC_for_Text();
}



void MainWindow::Text_BOM_checkBox_stateChanged(int state)
{
    Text_calc.with_BOM = (state == Qt::Checked);

    calculate_CRC_for_Text();
}



void MainWindow::show_error(const QString &err)
{
    status_label->setStyleSheet("QLabel { color : red; }");
    status_label->setText(err);

    set_Result_CRC(0);
}



void MainWindow::show_stats(const QString &msg)
{
    status_label->setStyleSheet("QLabel { color : black; }");
    status_label->setText(msg);
}



void MainWindow::calculate_CRC_for_Text()
{
    set_GUI_mode(false);

    Text_calc.calculate(ui->Text_tab_plainTextEdit->toPlainText());
}



void MainWindow::calculate_CRC()
{
    // start calculate CRC only for active Tab

    if( ui->CRC_Data_tabs->currentWidget() == ui->Hex_tab )
    {
        calculate_CRC_for_Hex();
        return;
    }


    if( ui->CRC_Data_tabs->currentWidget() == ui->Text_tab )
    {
        calculate_CRC_for_Text();
        return;
    }
}



void MainWindow::Prepare_Hex_calc()
{

    Hex_calc.set_ucrc(&qucrc);


    QObject::connect(&Hex_calc, SIGNAL(calculated(uint64_t)),
                     this, SLOT(set_Result_CRC_for_Hex(uint64_t)) );


    QObject::connect(&Hex_calc, SIGNAL(error(const QString &)),
                     this, SLOT(show_error(const QString &)) );


    QObject::connect(&qucrc, SIGNAL(param_changed()),
                     this, SLOT(calculate_CRC()) );


    QObject::connect(ui->Hex_tab_RevWord_checkBox, SIGNAL(stateChanged(int)),
                     this, SLOT(Hex_revers_chunk_checkBox_stateChanged(int)) );


    QObject::connect(ui->Hex_tab_RevData_checkBox, SIGNAL(stateChanged(int)),
                     this, SLOT(Hex_revers_data_checkBox_stateChanged(int)) );


    QObject::connect(ui->Hex_tab_plainTextEdit, SIGNAL(textChanged()),
                     this, SLOT(textChanged_for_Hex()) );
}



void MainWindow::Prepare_Text_calc()
{
    Text_calc.set_ucrc(&qucrc);


    QObject::connect(&Text_calc, SIGNAL(calculated(uint64_t)),
                     this, SLOT(set_Result_CRC_for_Text(uint64_t)) );


    QObject::connect(&Text_calc, SIGNAL(error(const QString &)),
                     this, SLOT(show_error(const QString &)) );


    QObject::connect(&qucrc, SIGNAL(param_changed()),
                     this, SLOT(calculate_CRC()) );


    QObject::connect(ui->Text_tab_plainTextEdit, SIGNAL(textChanged()),
                     this, SLOT(textChanged_for_Text()) );


    QObject::connect(ui->Text_tab_Encoding_comboBox,  SIGNAL(currentIndexChanged(int)),
                     this, SLOT(selected_encodings_in_comboBox(int)) );


    QObject::connect(ui->Text_tab_EndLine_comboBox,  SIGNAL(currentIndexChanged(int)),
                     this, SLOT(selected_endline_in_comboBox(int)) );


    QObject::connect(ui->Text_tab_BOM_checkBox, SIGNAL(stateChanged(int)),
                     this, SLOT(Text_BOM_checkBox_stateChanged(int)) );
}
