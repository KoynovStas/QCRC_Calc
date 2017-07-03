#include <QFile>

#include "crc_calc_for_file.h"





CRC_Calc_for_File::CRC_Calc_for_File(QObject *parent):
    Abstract_CRC_Calc(parent)
{

}



int CRC_Calc_for_File::_calculate(const QString &file_name)
{
    result.set_result(0); //reset old result


    QFile file(file_name);
    if( !file.open(QIODevice::ReadOnly) )
    {
        _set_error("Can't open file: " + file_name + " - " + file.errorString());
        return -1;
    }


    return 0;
}
