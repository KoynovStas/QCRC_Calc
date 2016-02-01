#include <QMetaType>
#include <QTextCodec>
#include <QSet>
#include "crc_calc_for_text.h"

#include <QDebug>




const QList<QByteArray> CRC_Calc_for_Text::Encodings = CRC_Calc_for_Text::get_Encodings();





CRC_Calc_for_Text::CRC_Calc_for_Text(QObject *parent) :
    QObject(NULL),

    encoding_index(0)
{
    qRegisterMetaType<uint64_t>("uint64_t");


    this->moveToThread(&thread);

    thread.start();


    QObject::connect(this, SIGNAL(run_calculate(const QString &)),
                     this, SLOT(_calculate(const QString &))  );
}



CRC_Calc_for_Text::~CRC_Calc_for_Text()
{
    thread.quit();
    thread.wait();
}



int CRC_Calc_for_Text::set_encoding_index(size_t new_index)
{
    if( new_index >= (size_t)Encodings.size() )
        return -1; //error


    encoding_index = new_index;


    return 0; //good job
}



void CRC_Calc_for_Text::calculate(const QString &data)
{
    emit run_calculate(data);
}



void CRC_Calc_for_Text::_calculate(const QString &data)
{

    if(data == "")
    {
        emit error("String is empty");
        emit calculated(0);
        return;
    }

    QByteArray tmp_str;

    if( encoding_index == 0 ) //ASCII
    {
        tmp_str = data.toLatin1();
    }
    else
    {
        QTextCodec *text_codec = QTextCodec::codecForName(Encodings[encoding_index]);
        tmp_str = text_codec->fromUnicode(data);
    }


    if( ucrc )
        emit calculated( ucrc->get_crc(tmp_str.data(), tmp_str.size() ) );
}



const QList<QByteArray> CRC_Calc_for_Text::get_Encodings()
{
    // list from Set - list have no a duplicate
    QList<QByteArray> list = QList<QByteArray>::fromSet( QTextCodec::availableCodecs().toSet() );

    std::sort(list.begin(), list.end());


    QList<QByteArray>::iterator it = std::find(list.begin(), list.end(), "ASCII");

    if( it != list.end() )
    {
        list.erase(it);
    }


    list.push_front("ASCII"); // ASCII always have the index 0


   return list;
}
