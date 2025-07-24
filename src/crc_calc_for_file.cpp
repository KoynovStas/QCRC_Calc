#include <QFile>

#include "crc_calc_for_file.h"





CRC_Calc_for_File::CRC_Calc_for_File(const QuCRC_t &crc, QObject *parent):
    Abstract_CRC_Calc(crc, parent)
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


    quint64 res = ucrc.get_crc_init();
    qint64 i = 0;
    qint64 chunk_size = qMin(file.size(), (qint64)CHUNK_SIZE);


    char buf[CHUNK_SIZE];


    while( !stoped  && chunk_size )
    {
        file.read(buf, chunk_size);

        res = ucrc.get_raw_crc(buf, chunk_size, res);  //crc for chunk

        i += chunk_size;
        chunk_size = qMin(file.size()-i, (qint64)CHUNK_SIZE);
    }


    res = ucrc.get_final_crc(res);

    emit calculated(res);
    result.set_result(res);
    return 0;               //good job
}
