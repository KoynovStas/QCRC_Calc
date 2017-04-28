#ifndef CRC_RESULT_H
#define CRC_RESULT_H

#include <QObject>
#include <QString>





class CRC_Result : public QObject
{
    Q_OBJECT

    public:
        explicit CRC_Result(QObject *parent = 0);


        // for QML bindings
        Q_PROPERTY(QString result_hex READ get_result_hex NOTIFY resultChanged)
        Q_PROPERTY(QString result_dec READ get_result_dec NOTIFY resultChanged)
        Q_PROPERTY(QString result_oct READ get_result_oct NOTIFY resultChanged)
        Q_PROPERTY(QString result_bin READ get_result_bin NOTIFY resultChanged)
        Q_PROPERTY(QString result_base READ get_result_base NOTIFY resultChanged)

        Q_PROPERTY(int base READ get_base WRITE set_base NOTIFY baseChanged)



    signals:
        resultChanged();
        baseChanged();


    public slots:
        QString get_result_hex() { return get_result(16);    }
        QString get_result_dec() { return get_result(10);    }
        QString get_result_oct() { return get_result(8);     }
        QString get_result_bin() { return get_result(2);     }
        QString get_result_base(){ return get_result(_base); }

        QString get_result(int base) { return QString::number(_result, base).toUpper(); }

        bool get_result_bit(int num_bit){ return (bool)(_result & ((quint64)1 << num_bit)); }


        void set_result(quint64 value);
        quint64 get_result() { return _result; }

        int set_base(int value);
        int get_base() { return _base; }


    private:
        quint64 _result;
        int     _base;
};





#endif // CRC_RESULT_H
