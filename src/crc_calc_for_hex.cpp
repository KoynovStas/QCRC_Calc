#include <QMetaType>
#include "crc_calc_for_hex.h"
#include <QDebug>




CRC_Calc_for_Hex::CRC_Calc_for_Hex() :
    QObject(NULL)
{

    QObject::connect(&hex_to_bytes, SIGNAL(error(QString)),
                     this, SIGNAL(error(QString)) );


    QObject::connect(this, SIGNAL(run_calculate(const QString &)),
                     this, SLOT(_calculate(const QString &))  );
}



void CRC_Calc_for_Hex::calculate(const QString & data)
{
    emit run_calculate(data);
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



void CRC_Calc_for_Hex::_calculate(const QString &data)
{
    if( hex_to_bytes.str_to_bytes(data) != 0 )
    {
        return; // bad string
    }


    if(hex_to_bytes.bytes.size() == 0)
    {
        emit error("No Data");
        return;
    }


    if( ucrc )
    {
        quint64 res = ucrc->get_crc(hex_to_bytes.bytes.data(), hex_to_bytes.bytes.size() );
        emit calculated(res);
        result.set_result(res);
    }
}
