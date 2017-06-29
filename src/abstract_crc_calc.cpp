#include "abstract_crc_calc.h"





Abstract_CRC_Calc::Abstract_CRC_Calc(QObject *parent) :
    QObject(parent),

    worker(*this)
{
}



Abstract_CRC_Calc::~Abstract_CRC_Calc()
{
    stoped = true;
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
