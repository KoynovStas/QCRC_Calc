#ifndef CRC_CALC_FOR_HEX_H
#define CRC_CALC_FOR_HEX_H


#include <QObject>

#include "hextobytes.h"
#include "qucrc_t.h"
#include "crc_result.h"





class CRC_Calc_for_Hex : public QObject
{
    Q_OBJECT

    public:
        explicit CRC_Calc_for_Hex();


        size_t size() { return hex_to_bytes.bytes.size(); }
        void set_ucrc(const QuCRC_t *crc) { ucrc = crc; }


        // for QML bindings
        Q_PROPERTY(bool revers_chunk READ get_revers_chunk WRITE set_revers_chunk NOTIFY revers_chunkChanged)
        Q_PROPERTY(bool revers_data READ get_revers_data WRITE set_revers_data NOTIFY revers_dataChanged)
        Q_PROPERTY(CRC_Result* result READ get_result CONSTANT)


        CRC_Result* get_result() { return &result; }
        CRC_Result result;

        QString get_str_error() { return str_error; }


    signals:
        void calculated(quint64 value);
        void error(const QString & err);
        void revers_chunkChanged();
        void revers_dataChanged();


    public slots:
        int  calculate(const QString & data) { return _calculate(data); }
        void set_revers_chunk(bool value);
        void set_revers_data(bool value);

        quint32 get_num_words() { return hex_to_bytes.get_num_words(); }
        quint32 get_num_bytes() { return hex_to_bytes.bytes.size(); }

        bool get_revers_chunk() { return hex_to_bytes.revers_chunk; }
        bool get_revers_data()  { return hex_to_bytes.revers_data;  }



    protected slots:
        int  _calculate(const QString & data);
        void _set_error(const QString & err);



    private:
        HexToBytes      hex_to_bytes;
        const QuCRC_t  *ucrc;
        QString         str_error;
};





#endif // CRC_CALC_FOR_HEX_H
