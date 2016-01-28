#include "crc_calc_for_hex.h"





CRC_Calc_for_Hex::CRC_Calc_for_Hex(QObject *parent) :
    QObject(parent)
{

    QObject::connect(&hex_to_bytes, SIGNAL(error(QString)),
                     this, SIGNAL(error(QString)) );
}



void CRC_Calc_for_Hex::calculate(const QString & data)
{

    if( hex_to_bytes.str_to_bytes(data) != 0 )
    {
        emit calculated(0);
        return;
    }


    if(hex_to_bytes.bytes.size() == 0)
    {
        emit error("No Data");
        emit calculated(0);
        return;
    }


    if( ucrc )
        emit calculated( ucrc->get_crc(hex_to_bytes.bytes.data(), hex_to_bytes.bytes.size() ) );
}
