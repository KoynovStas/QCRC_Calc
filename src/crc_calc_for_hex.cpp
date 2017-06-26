#include <QMetaType>
#include "crc_calc_for_hex.h"
#include <QDebug>




CRC_Calc_for_Hex::CRC_Calc_for_Hex() :
    Abstract_CRC_Calc(Q_NULLPTR)
{

    QObject::connect(&hex_to_bytes, SIGNAL(error(const QString &)),
                     this, SLOT(_set_error(const QString &)) );
}



void CRC_Calc_for_Hex::set_revers_chunk(bool value)
{
    if( hex_to_bytes.revers_chunk != value )
    {
        hex_to_bytes.revers_chunk = value;
        emit revers_chunkChanged();
    }
}



void CRC_Calc_for_Hex::set_revers_data(bool value)
{
    if( hex_to_bytes.revers_data != value )
    {
        hex_to_bytes.revers_data  = value;
        emit revers_dataChanged();
    }
}



int CRC_Calc_for_Hex::_calculate(const QString &data)
{
    result.set_result(0); //reset old result


    if( hex_to_bytes.str_to_bytes(data) != 0 )
    {
        return -1; // bad string
    }


    if( hex_to_bytes.bytes.size() == 0 )
    {
        _set_error("No Data");
        return -1;
    }


    if( ucrc )
    {
        quint64 res = ucrc->get_crc(hex_to_bytes.bytes.data(), hex_to_bytes.bytes.size() );
        emit calculated(res);
        result.set_result(res);
        return 0; //good job
    }


    _set_error("Dont set uCRC");
    return -1;
}
