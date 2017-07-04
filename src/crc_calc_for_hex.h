#ifndef CRC_CALC_FOR_HEX_H
#define CRC_CALC_FOR_HEX_H


#include "abstract_crc_calc.h"
#include "hextobytes.h"





class CRC_Calc_for_Hex : public Abstract_CRC_Calc
{
    Q_OBJECT

    public:
        explicit CRC_Calc_for_Hex(const QuCRC_t &crc, QObject *parent = Q_NULLPTR);


        size_t size() { return hex_to_bytes.bytes.size(); }


        // for QML bindings
        Q_PROPERTY(bool revers_chunk READ get_revers_chunk WRITE set_revers_chunk NOTIFY revers_chunkChanged)
        Q_PROPERTY(bool revers_data READ get_revers_data WRITE set_revers_data NOTIFY revers_dataChanged)



    signals:
        void revers_chunkChanged();
        void revers_dataChanged();



    public slots:
        void set_revers_chunk(bool value);
        void set_revers_data(bool value);

        quint32 get_num_words() { return hex_to_bytes.get_num_words(); }
        quint32 get_num_bytes() { return hex_to_bytes.bytes.size(); }

        bool get_revers_chunk() { return hex_to_bytes.revers_chunk; }
        bool get_revers_data()  { return hex_to_bytes.revers_data;  }



    protected slots:
       virtual  int _calculate(const QString & data);



    private:
        HexToBytes      hex_to_bytes;
};





#endif // CRC_CALC_FOR_HEX_H
