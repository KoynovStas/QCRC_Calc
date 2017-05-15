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

        quint32 get_num_words() { return num_words; }


    signals:
        void error(const QString & err);


    private:

        int token_to_bytes(const QString& token);

        QByteArray token_bytes;
        QRegExp    token_rx;
        QRegExp    hex_rx;

        quint32    num_words;
};





#endif // HEXTOBYTES_H
