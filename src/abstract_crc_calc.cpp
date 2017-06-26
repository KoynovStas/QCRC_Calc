#include "abstract_crc_calc.h"





Abstract_CRC_Calc::Abstract_CRC_Calc(QObject *parent) : QObject(parent)
{

}



void Abstract_CRC_Calc::_set_error(const QString &err)
{
    str_error = err;
    emit error(err);
}
