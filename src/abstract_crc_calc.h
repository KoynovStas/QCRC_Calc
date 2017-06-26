#ifndef ABSTRACT_CRC_CALC_H
#define ABSTRACT_CRC_CALC_H

#include <QObject>

#include "qucrc_t.h"
#include "crc_result.h"





class Abstract_CRC_Calc : public QObject
{
    Q_OBJECT

    public:
        explicit Abstract_CRC_Calc(QObject *parent = NULL);


        CRC_Result* get_result() { return &result; }
        CRC_Result result;

        void set_ucrc(const QuCRC_t *crc) { ucrc = crc; }

        QString get_str_error() { return str_error; }



        // for QML bindings
        Q_PROPERTY(CRC_Result* result READ get_result CONSTANT)



    signals:
        void calculated(quint64 value);
        void error(const QString & err);



    public slots:
        virtual int calculate(const QString & data) = 0;



    protected slots:
        void _set_error(const QString & err);



    protected:
        const QuCRC_t  *ucrc;
        QString         str_error;
};





#endif // ABSTRACT_CRC_CALC_H
