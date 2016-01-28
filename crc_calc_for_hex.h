#ifndef CRC_CALC_FOR_HEX_H
#define CRC_CALC_FOR_HEX_H

#include <QObject>
#include "hextobytes.h"
#include "qucrc_t.h"





class CRC_Calc_for_Hex : public QObject
{
    Q_OBJECT

    public:
        explicit CRC_Calc_for_Hex(QObject *parent = 0);


        size_t size() { return hex_to_bytes.bytes.size(); }
        void set_ucrc(const QuCRC_t *crc) { ucrc = crc; }


    signals:
        void calculated(uint64_t value);
        void error(const QString & err);


    public slots:
        void calculate(const QString & data);
        void set_revers_chunk(bool value) { hex_to_bytes.revers_chunk = value; }
        void set_revers_data(bool value)  { hex_to_bytes.revers_data  = value; }


    private:

        HexToBytes      hex_to_bytes;
        const QuCRC_t  *ucrc;
};





#endif // CRC_CALC_FOR_HEX_H
