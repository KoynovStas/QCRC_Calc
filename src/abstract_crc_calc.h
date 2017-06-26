#ifndef ABSTRACT_CRC_CALC_H
#define ABSTRACT_CRC_CALC_H

#include <QObject>





class Abstract_CRC_Calc : public QObject
{
    Q_OBJECT
    public:
        explicit Abstract_CRC_Calc(QObject *parent = nullptr);

    signals:

    public slots:
};





#endif // ABSTRACT_CRC_CALC_H
