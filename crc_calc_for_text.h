#ifndef CRC_CALC_FOR_TEXT_H
#define CRC_CALC_FOR_TEXT_H

#include <QObject>
#include <QList>
#include <QByteArray>

#include "qucrc_t.h"
#include "qexecthread.h"





class CRC_Calc_for_Text : public QObject
{
    Q_OBJECT

    public:
        explicit CRC_Calc_for_Text(QObject *parent = 0);
        ~CRC_Calc_for_Text();


        static const QList<QByteArray> Encodings;


        void set_ucrc(const QuCRC_t *crc) { ucrc = crc; }

        size_t get_encoding_index() { return encoding_index; }
        int    set_encoding_index(size_t new_index);


    signals:
        void calculated(uint64_t value);
        void error(const QString & err);

        //signals for inner use
        void run_calculate(const QString & data);



    public slots:
        void calculate(const QString & data);


    protected slots:
        void _calculate(const QString & data);


    private:

        const QuCRC_t  *ucrc;
        QExecThread     thread;
        size_t          encoding_index;

        static const QList<QByteArray> get_Encodings();
};





#endif // CRC_CALC_FOR_TEXT_H
