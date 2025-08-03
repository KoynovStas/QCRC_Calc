#include <QFile>
#include <QTextStream>

#include "abstract_crc_calc.h"





const int Abstract_CRC_Calc::CHUNK_SIZE = 4096;




Abstract_CRC_Calc::Abstract_CRC_Calc(const QuCRC_t &crc, QObject *parent) :
    QObject(parent),

    ucrc(crc),
    worker(*this)
{
}



Abstract_CRC_Calc::~Abstract_CRC_Calc()
{
    stoped = true;
}



int Abstract_CRC_Calc::get_crc_data_from_file(const QString &file_name)
{
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        _set_error("Can't open file: " + file_name + " - " + file.errorString());
        return -1;
    }


    QTextStream in(&file);

    return _calculate(in.readAll());      //start calculation in current thread.
}



void Abstract_CRC_Calc::_set_error(const QString &err)
{
    str_error = err;
    emit error(err);
}



void Abstract_CRC_Calc::stop_worker()
{
    while(worker.active)
    {
        stoped = true;
        QThread::yieldCurrentThread();
    }


    stoped = false;
}



int Abstract_CRC_Calc::get_crc(const char *data, int size)
{
    quint64 res = ucrc.get_crc_init();
    int i = 0;
    int chunk_size = std::min(size, CHUNK_SIZE);


    while( !stoped  && chunk_size )
    {
        res = ucrc.get_raw_crc(&data[i], chunk_size, res);  //crc for chunk

        i += chunk_size;
        chunk_size = std::min(size-i, CHUNK_SIZE);
    }


    res = ucrc.get_end_crc(res);


    emit calculated(res);
    result.set_result(res);
    return 0;               //good job
}



int Abstract_CRC_Calc::calculate(const QString &data, bool synchro_mode)
{
    stop_worker();


    if(synchro_mode)
        return _calculate(data);      //start calculation in current thread.


    m_data = data;                    //in async mode work with a copy of data
    worker.active = true;
    worker.calculate(m_data);         //start calculation in another thread.

    return 0;                         //always 0(good job) in asynchonous mode
}



CRC_Calc_Worker::CRC_Calc_Worker(Abstract_CRC_Calc & calculator):
    QObject(Q_NULLPTR),

    //public
    active(false),

    //private
    calc(calculator)
{
    this->moveToThread(&worker_thread);

    connect(this, &CRC_Calc_Worker::calculate, this, &CRC_Calc_Worker::do_work);

    worker_thread.start();
}



CRC_Calc_Worker::~CRC_Calc_Worker()
{
    worker_thread.quit();
    worker_thread.wait();
}



void CRC_Calc_Worker::do_work(const QString &data)
{
    calc._calculate(data);
    active = false;
}
