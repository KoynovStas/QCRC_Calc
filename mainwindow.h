#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "bitset64.h"
#include "qucrc_t.h"




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


    private:

        Ui::MainWindow *ui;

        BitSet64 bit_set;

        QuCRC_t  qucrc;

        uint64_t crc_result;
        bool     select_index_done;  // to protect against recursion (user select/program select in CRC_Param_comboBox)


        void Prepare_CRC_Param_comboBox();
};





#endif // MAINWINDOW_H
