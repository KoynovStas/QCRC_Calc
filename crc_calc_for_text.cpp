#include <QMetaType>
#include <QTextCodec>
#include <QSet>
#include "crc_calc_for_text.h"





const QList<QByteArray> CRC_Calc_for_Text::Encodings = CRC_Calc_for_Text::get_Encodings();





CRC_Calc_for_Text::CRC_Calc_for_Text() :
    QObject(NULL),

    // public
    with_BOM(false),
    end_line_format(EndLine_LF),

    // private
    encoding_index(0),
    num_lines(0)
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

    if( data.isEmpty() )
    {
        emit error("String is empty");
        return;
    }


    num_lines = data.count('\n');

    replace_end_line(data);
    encoding_str();


    if( ucrc )
        emit calculated( ucrc->get_crc(raw_str.data(), raw_str.size() ) );
}



void CRC_Calc_for_Text::replace_end_line(const QString &data)
{
    tmp_str = data;


    switch( end_line_format )
    {
        case EndLine_LF:
                tmp_str.replace('\n', QLatin1String("\n"));
                break;


        case EndLine_CR:
                tmp_str.replace('\n', QLatin1String("\r"));
                break;


        case EndLine_RS:
                tmp_str.replace('\n', QLatin1String("\x1E"));
                break;


        case EndLine_9B:
                tmp_str.replace('\n', QLatin1String("\x9B"));
                break;


        case EndLine_CRLF:
                tmp_str.replace('\n', QLatin1String("\r\n"));
                break;


        case EndLine_LFCR:
                tmp_str.replace('\n', QLatin1String("\n\r"));
                break;

        default:
                break;
    }

}



void CRC_Calc_for_Text::encoding_str()
{

    if( encoding_index == 0 ) //ASCII
    {
        raw_str = tmp_str.toLatin1();
    }
    else
    {
        QTextCodec *text_codec = QTextCodec::codecForName(Encodings[encoding_index]);
        QTextCodec::ConverterState state(with_BOM ? QTextCodec::DefaultConversion : QTextCodec::IgnoreHeader);

        raw_str = text_codec->fromUnicode(tmp_str.constData(), tmp_str.size(), &state);
    }
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
