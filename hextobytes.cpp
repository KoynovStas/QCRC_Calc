#include "hextobytes.h"





HexToBytes::HexToBytes(QObject *parent) :
    QObject(parent),

    revers_chunk(false),
    revers_data(false),

    //private
    token_rx("(\\w+)"),
    hex_rx("^(0x)?([0-9a-f]+)$")
{
}



int HexToBytes::str_to_bytes(const QString& str)
{

    bytes.clear();

    int pos = 0;

    while( (pos = token_rx.indexIn(str, pos)) != -1 )
    {
        pos += token_rx.matchedLength();
        if( token_to_bytes(token_rx.cap(1)) == -1 )
            return -1;
    }


    if( revers_data )
        std::reverse(bytes.begin(), bytes.end());


    return 0;  //good job
}



int HexToBytes::token_to_bytes(const QString& token)
{

    if( hex_rx.indexIn(token.toLower()) == -1 )
    {
        emit error("bad format: " + token);
        return -1;
    }


    token_bytes = QByteArray::fromHex(hex_rx.cap(2).toLatin1());


    if( revers_chunk )
        std::reverse(token_bytes.begin(), token_bytes.end());


    bytes += token_bytes;

    return 0;  //good job
}
