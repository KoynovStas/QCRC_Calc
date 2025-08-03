#include <QQmlEngine>

#include "crc_result.h"




CRC_Result::CRC_Result(QObject *parent) :
    QObject(parent),

    _result(0),
    _base(2)
{
    qmlRegisterType<CRC_Result>("CRC_Calc", 1, 0, "CRC_Result");
}



void CRC_Result::set_result(quint64 value)
{
    if( value != _result )
    {
        _result = value;
        emit resultChanged();
    }
}



int CRC_Result::set_base(int value)
{
    if( value == _base )
        return 0; //no action


    if( (value < 2) || (value > 36))
        return -1; //bad value


    _base = value;

    emit baseChanged();
    emit resultChanged(); //for update result_base property


    return 0; //good job
}
