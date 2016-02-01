#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "bitset64.h"
#include "qucrc_t.h"
#include "crc_calc_for_hex.h"
#include "crc_calc_for_text.h"




namespace Ui
{
    class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();


    public slots:

        void Hex_tab_WrapWord_checkBox_stateChanged(int state);
        void Text_tab_WrapWord_checkBox_stateChanged(int state);

        void selected_index_CRC_in_comboBox(int new_index);
        void set_index_CRC_in_comboBox(uint32_t new_index);
        void CRC_Param_to_GUI();
        void CRC_Param_from_GUI();

        void set_Result_CRC(uint64_t value);
        void set_Result_CRC_for_custom_base();

        void textChanged_for_Hex();
        void calculate_CRC_for_Hex();
        void Hex_revers_chunk_checkBox_stateChanged(int state);
        void Hex_revers_data_checkBox_stateChanged(int state);


        void textChanged_for_Text();
        void selected_encodings_in_comboBox(int new_index);
        void calculate_CRC_for_Text();


    private:

        Ui::MainWindow *ui;

        BitSet64 bit_set;

        QuCRC_t  qucrc;

        uint64_t crc_result;
        bool     select_index_done;  // to protect against recursion (user select/program select in CRC_Param_comboBox)


        CRC_Calc_for_Hex  Hex_calc;
        CRC_Calc_for_Text Text_calc;

        void Prepare_Hex_calc();
        void Prepare_CRC_Param_comboBox();

        void Prepare_Text_calc();
        void Prepare_Text_Encoding_comboBox();


        void set_GUI_mode(bool mode);
};





#endif // MAINWINDOW_H
