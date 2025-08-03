#ifndef CRC_CALC_FOR_FILE_H
#define CRC_CALC_FOR_FILE_H

#include "abstract_crc_calc.h"




class CRC_Calc_for_File : public Abstract_CRC_Calc
{
    Q_OBJECT

    public:
        explicit CRC_Calc_for_File(const QuCRC_t &crc, QObject *parent = Q_NULLPTR);


    protected slots:
        virtual int _calculate(const QString & file_name);
};




#endif // CRC_CALC_FOR_FILE_H
