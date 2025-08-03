#ifndef ABSTRACT_CRC_CALC_H
#define ABSTRACT_CRC_CALC_H

#include <QObject>
#include <QThread>

#include "qucrc_t.h"
#include "crc_result.h"




class Abstract_CRC_Calc;


class CRC_Calc_Worker : public QObject
{
    Q_OBJECT

    public:
        CRC_Calc_Worker(Abstract_CRC_Calc & calculator);
        ~CRC_Calc_Worker();

        volatile bool active;


    public slots:
        void do_work(const QString & data);


    signals:
        void calculate(const QString & data);


    private:
        QThread            worker_thread;
        Abstract_CRC_Calc &calc;
};




class Abstract_CRC_Calc : public QObject
{
    Q_OBJECT

    friend class CRC_Calc_Worker;

    public:
        explicit Abstract_CRC_Calc(const QuCRC_t &crc, QObject *parent = Q_NULLPTR);
        virtual ~Abstract_CRC_Calc();


        static const int CHUNK_SIZE;


        CRC_Result result;


        QString get_str_error() { return str_error; }


        int get_crc_data_from_file(const QString & file_name); //for cmd --xxx_file (synchonous mode)


        // for QML bindings
        Q_PROPERTY(CRC_Result* result READ get_result CONSTANT)


    signals:
        void calculated(quint64 value);
        void error(const QString & err);


    public slots:
        int calculate(const QString & data, bool synchro_mode = false);


    protected slots:
        void _set_error(const QString & err);
        virtual int _calculate(const QString & data) = 0;


    protected:
        const QuCRC_t  &ucrc;
        QString         str_error;


        volatile bool   stoped;
        CRC_Calc_Worker worker;
        QString         m_data;


        void stop_worker();
        int  get_crc(const char *data, int size);


    private:
        CRC_Result* get_result() { return &result; } //for QML bindings
};




#endif // ABSTRACT_CRC_CALC_H
