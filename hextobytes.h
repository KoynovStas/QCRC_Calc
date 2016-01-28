#ifndef HEXTOBYTES_H
#define HEXTOBYTES_H

#include <QObject>
#include <QString>
#include <QRegExp>
#include <QByteArray>





class HexToBytes : public QObject
{
    Q_OBJECT


    public:
        explicit HexToBytes(QObject *parent = 0);


        QByteArray bytes;

        bool revers_chunk;
        bool revers_data;

        int str_to_bytes(const QString& str);


    signals:
        void error(const QString & err);



//    public slots:


    private:

        int token_to_bytes(const QString& token);

        QByteArray token_bytes;
        QRegExp    token_rx;
        QRegExp    hex_rx;

        QString    str_error;
};





#endif // HEXTOBYTES_H
