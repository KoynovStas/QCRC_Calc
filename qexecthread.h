#ifndef QEXECTHREAD_H
#define QEXECTHREAD_H


#include <QObject>
#include <QThread>





class QExecThread : public QThread
{
    Q_OBJECT

    public:

        explicit QExecThread(QObject *parent = 0, bool autostart = false):
                             QThread(parent){
                                                if(autostart)
                                                    start();
                                            }


    protected:

        virtual void run() { exec(); }

};





#endif // QEXECTHREAD_H
