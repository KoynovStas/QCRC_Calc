#include <QMetaType>
#include <QTextCodec>
#include <QSet>
#include "crc_calc_for_text.h"
#include <QDebug>





const QList<QByteArray> CRC_Calc_for_Text::Encodings = CRC_Calc_for_Text::get_Encodings();





const QHash<qint8, EndLine> EndLine::end_line_map =
{
    { EndLine::EndLine_LF,   EndLine("LF (Unix/Mac)",   "\n")   },
    { EndLine::EndLine_CR,   EndLine("CR (old Mac)",    "\r")   },
    { EndLine::EndLine_RS,   EndLine("RS (QNX)",        "\x1E") },
    { EndLine::EndLine_9B,   EndLine("0x9B (Atari)",    "\x9B") },
    { EndLine::EndLine_CRLF, EndLine("CR+LF (Win)",     "\r\n") },
    { EndLine::EndLine_LFCR, EndLine("LF+CR (RISC OS)", "\n\r") },
};





CRC_Calc_for_Text::CRC_Calc_for_Text(QObject *parent) :
    Abstract_CRC_Calc(parent),

    // private
    encoding_index(0),
    BOM(false),
    end_line_index(EndLine::EndLine_LF),
    num_lines(0)
{

}



QStringList CRC_Calc_for_Text::end_line_names() const
{
    QStringList list;

    for(int i = 0; i < EndLine::end_line_map.size(); ++i)
        list.push_back(EndLine::end_line_map[i].name);

    return list;
}



QStringList CRC_Calc_for_Text::encodings() const
{
    QStringList list;

    for(int i = 0; i < Encodings.size(); ++i)
        list.push_back(Encodings[i]);

    return list;
}



int CRC_Calc_for_Text::set_end_line_index(int new_index)
{
    if( new_index == end_line_index )
        return 0; //good job (index already set - no action)


    if( new_index >= EndLine::end_line_map.size() )
        return -1; // new_index is bad


    stop_worker();
    end_line_index = new_index;
    emit end_line_indexChanged();


    return 0; //good job
}



void CRC_Calc_for_Text::set_BOM(bool new_BOM)
{
    if( new_BOM == BOM )
        return; //no action

    stop_worker();
    BOM = new_BOM;
    emit BOMChanged();
}



int CRC_Calc_for_Text::set_encoding_index(int new_index)
{
    if( encoding_index == new_index )
        return 0; //no action


    if( (new_index < 0) || (new_index >= Encodings.size()) )
        return -1; //error


    stop_worker();
    encoding_index = new_index;
    emit encoding_indexChanged();


    return 0; //good job
}



int CRC_Calc_for_Text::_calculate(const QString &data)
{
    result.set_result(0); //reset old result

    num_lines = data.count('\n') + 1; // +1 last string have no EndLine char

    replace_end_line(data);
    encoding_str();


    if( raw_str.isEmpty() )
    {
        _set_error("String is empty");
        return -1;
    }


    return get_crc(raw_str.data(), raw_str.size());
}



void CRC_Calc_for_Text::replace_end_line(const QString &data)
{
    tmp_str = data;

    EndLine end_line = EndLine::end_line_map.value(end_line_index);


    tmp_str.replace('\n', end_line.value);
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
        QTextCodec::ConverterState state(BOM ? QTextCodec::DefaultConversion : QTextCodec::IgnoreHeader);

        raw_str = text_codec->fromUnicode(tmp_str.constData(), tmp_str.size(), &state);
    }
}



const QList<QByteArray> CRC_Calc_for_Text::get_Encodings()
{
    // list from Set - list have no a duplicate
    QList<QByteArray> list = QList<QByteArray>::fromSet( QTextCodec::availableCodecs().toSet() );

    std::sort(list.begin(), list.end());


    auto it = std::find(list.begin(), list.end(), "ASCII");

    if( it != list.end() )
    {
        list.erase(it);
    }


    list.push_front("ASCII"); // ASCII always have the index 0


   return list;
}
