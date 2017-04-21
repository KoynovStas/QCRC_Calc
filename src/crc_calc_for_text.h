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


        explicit CRC_Calc_for_Text();
        ~CRC_Calc_for_Text();


        static const QList<QByteArray> Encodings;

        bool           with_BOM;
        EndLineFormat  end_line_format;


        void set_ucrc(const QuCRC_t *crc) { ucrc = crc; }

        size_t get_encoding_index() { return encoding_index; }
        int    set_encoding_index(size_t new_index);

        size_t get_num_lines() { return num_lines; }
        size_t get_num_bytes() { return raw_str.size(); }



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

        QString         tmp_str;
        QByteArray      raw_str;

        size_t          num_lines;


        void replace_end_line(const QString &data);
        void encoding_str();

        static const QList<QByteArray> get_Encodings();
};





#endif // CRC_CALC_FOR_TEXT_H
