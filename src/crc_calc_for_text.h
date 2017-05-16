#ifndef CRC_CALC_FOR_TEXT_H
#define CRC_CALC_FOR_TEXT_H


#include <QObject>
#include <QList>
#include <QHash>
#include <QByteArray>

#include "qucrc_t.h"
#include "crc_result.h"





class EndLine
{
    public:

        enum EndLineFormat
        {
            EndLine_LF = 0,  // LF:    Multics, Unix and Unix-like systems (Linux, OS X, FreeBSD, AIX, Xenix, etc.), BeOS, Amiga, RISC OS,
            EndLine_CR,      // CR:    Commodore 8-bit machines, Acorn BBC, ZX Spectrum, TRS-80, Apple II family, Mac OS up to version 9, and OS-9
            EndLine_RS,      // RS:    QNX pre-POSIX implementation
            EndLine_9B,      // 0x9B:  Atari 8-bit machines using ATASCII variant of ASCII (155 in decimal)
            EndLine_CRLF,    // CR+LF: Microsoft Windows, DOS (MS-DOS, PC DOS, etc.), DEC TOPS-10, RT-11, CP/M, MP/M, Atari TOS, OS/2
            EndLine_LFCR,    // LF+CR: Acorn BBC and RISC OS spooled text output
                             // more see https://en.wikipedia.org/wiki/Newline
        };


        static const QHash<qint8, EndLine> end_line_map;



        EndLine(): name("LF (Unix/Mac)"), value("\n") {}
        EndLine(const char * _name, const char * _value): name(_name), value(_value) {}

        QString       name;
        QLatin1String value;
};





class CRC_Calc_for_Text : public QObject
{
    Q_OBJECT


    public:

        explicit CRC_Calc_for_Text();


        // for QML bindings
        Q_PROPERTY(QStringList end_line_names READ end_line_names CONSTANT)
        Q_PROPERTY(int end_line_index READ get_end_line_index WRITE set_end_line_index NOTIFY end_line_indexChanged)

        Q_PROPERTY(QStringList encodings READ encodings CONSTANT)
        Q_PROPERTY(int encoding_index READ get_encoding_index WRITE set_encoding_index NOTIFY encoding_indexChanged)

        Q_PROPERTY(bool BOM READ get_BOM WRITE set_BOM NOTIFY BOMChanged)
        Q_PROPERTY(CRC_Result* result READ get_result CONSTANT)


        CRC_Result* get_result() { return &result; }
        CRC_Result result;

        QStringList end_line_names() const;
        QStringList encodings() const;


        int get_end_line_index() const { return end_line_index; }
        int set_end_line_index(int new_index);

        bool get_BOM() const { return BOM; }
        void set_BOM(bool new_BOM);


        static const QList<QByteArray> Encodings;


        void set_ucrc(const QuCRC_t *crc) { ucrc = crc; }

        int get_encoding_index() { return encoding_index; }
        int set_encoding_index(int new_index);


        QString get_str_error() { return str_error; }



    signals:

        void end_line_indexChanged();
        void encoding_indexChanged();
        void BOMChanged();
        void calculated(quint64 value);
        void error(const QString & err);



    public slots:
        int  calculate(const QString & data) { return _calculate(data); }

        quint32 get_num_lines() { return num_lines; }
        quint32 get_num_bytes() { return raw_str.size(); }



    protected slots:
        int  _calculate(const QString & data);
        void _set_error(const QString & err);



    private:
        const QuCRC_t  *ucrc;
        int             encoding_index;

        bool            BOM;
        int             end_line_index;

        QString         tmp_str;
        QByteArray      raw_str;

        size_t          num_lines;

        QString         str_error;


        void replace_end_line(const QString &data);
        void encoding_str();

        static const QList<QByteArray> get_Encodings();
};





#endif // CRC_CALC_FOR_TEXT_H
