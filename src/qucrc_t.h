/*
 * qucrc_t.h
 *
 *
 * version 1.0
 *
 *
 * Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1 Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  2 Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  3 Neither the name of the <organization> nor the
 *    names of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef QUCRC_T_H
#define QUCRC_T_H

#include <QObject>
#include <QString>
#include <QQmlListProperty>

#include <vector>

#include "ucrc_t.h"





struct CRC_Param_Info
{
    QString name;
    quint8  bits;
    quint64 poly;
    quint64 init;
    bool    ref_in;
    bool    ref_out;
    quint64 xor_out;
};





class QuCRC_t : public QObject //Qt wrapper for uCRC_t
{
    Q_OBJECT

    public:
        explicit QuCRC_t(QObject *parent = 0);


        static const std::vector<CRC_Param_Info> CRC_List;

        // for QML bindings
        Q_PROPERTY(QStringList crc_names READ crc_names CONSTANT)
        Q_PROPERTY(int index READ get_index WRITE set_index NOTIFY indexChanged)
        Q_PROPERTY(quint8 bits READ get_bits WRITE set_bits NOTIFY bitsChanged)
        Q_PROPERTY(QString poly_str READ get_poly_str  WRITE set_poly_str NOTIFY polyChanged)
        Q_PROPERTY(QString init_str READ get_init_str  WRITE set_init_str NOTIFY initChanged)
        Q_PROPERTY(QString xor_out_str READ get_xor_out_str  WRITE set_xor_out_str NOTIFY xor_outChanged)
        Q_PROPERTY(bool ref_in READ get_ref_in WRITE set_ref_in NOTIFY ref_inChanged)
        Q_PROPERTY(bool ref_out READ get_ref_out WRITE set_ref_out NOTIFY ref_outChanged)

        //extended param (info) CRC
        Q_PROPERTY(QString check_str READ get_check_str NOTIFY paramChanged)
        Q_PROPERTY(QString crc_mask_str READ get_crc_mask_str NOTIFY paramChanged)
        Q_PROPERTY(QString top_bit_str READ get_top_bit_str NOTIFY paramChanged)


        QStringList crc_names() const;


    signals:

        void paramChanged();
        void indexChanged(int index);
        void bitsChanged(quint8 bits);
        void polyChanged();
        void initChanged();
        void xor_outChanged();
        void ref_inChanged(bool ref_in);
        void ref_outChanged(bool ref_out);


    public slots:
        // get param CRC
        quint8  get_bits()    const { return ucrc.get_bits();   }
        quint64 get_poly()    const { return ucrc.get_poly();   }
        quint64 get_init()    const { return ucrc.get_init();   }
        quint64 get_xor_out() const { return ucrc.get_xor_out();}
        bool    get_ref_in()  const { return ucrc.get_ref_in(); }
        bool    get_ref_out() const { return ucrc.get_ref_out();}

        quint64 get_crc_init()const { return ucrc.get_crc_init();} //crc_init = reflect(init, bits) if RefIn, else = init
        quint64 get_top_bit() const { return ucrc.get_top_bit(); }
        quint64 get_crc_mask()const { return ucrc.get_crc_mask();}
        quint64 get_check()   const { return ucrc.get_check();   } //crc for ASCII string "123456789" (i.e. 313233... (hexadecimal)).


        QString get_poly_str()    { return "0x" + QString::number(get_poly(),    16).toUpper(); }
        QString get_init_str()    { return "0x" + QString::number(get_init(),    16).toUpper(); }
        QString get_xor_out_str() { return "0x" + QString::number(get_xor_out(), 16).toUpper(); }

        //extended param (info) CRC
        QString get_check_str()    { return "0x" + QString::number(get_check(),    16).toUpper(); }
        QString get_crc_mask_str() { return "0x" + QString::number(get_crc_mask(), 16).toUpper(); }
        QString get_top_bit_str()  { return "0x" + QString::number(get_top_bit(),  16).toUpper(); }


        void set_poly_str(QString &new_poly);
        void set_init_str(QString &new_init);
        void set_xor_out_str(QString &new_xor_out);


        // set param CRC
        int  set_bits(quint8 new_bits)        { return set_bits(new_bits, true); }
        void set_poly(quint64 new_poly)       { set_poly(new_poly, true);        }
        void set_init(quint64 new_init)       { set_init(new_init, true);        }
        void set_xor_out(quint64 new_xor_out) { set_xor_out(new_xor_out, true);  }
        void set_ref_in(bool new_ref_in)      { set_ref_in(new_ref_in, true);    }
        void set_ref_out(bool new_ref_out)    { set_ref_out(new_ref_out, true);  }


        // Calculate methods
        quint64 get_crc(const char* buf, size_t len)         const { return ucrc.get_crc(buf, len);                  }
        int     get_crc(quint64 &crc, const char* file_name) const { return ucrc.get_crc((uint64_t &)crc, file_name);}
        int     get_crc(quint64 &crc, FILE* pfile)           const { return ucrc.get_crc((uint64_t &)crc, pfile);    }

        int     get_crc(quint64 &crc, const char* file_name, void* buf, size_t size_buf) const { return ucrc.get_crc((uint64_t &)crc, file_name, buf, size_buf);}
        int     get_crc(quint64 &crc, FILE* pfile, void* buf, size_t size_buf)           const { return ucrc.get_crc((uint64_t &)crc, pfile, buf, size_buf);    }


        // Calculate for chunks of data
        quint64 get_raw_crc(const char* buf, size_t len, quint64 crc) const { return ucrc.get_raw_crc(buf, len, crc);}  //for first byte crc = crc_init (must be)
        quint64 get_final_crc(quint64 raw_crc)                        const { return ucrc.get_final_crc(raw_crc);    }





        int get_index() const { return index; }
        int set_index(int new_index);


    private:

        uCRC_t   ucrc;

        int index;

        int  set_bits(quint8 new_bits, bool single_action);
        void set_poly(quint64 new_poly, bool single_action);
        void set_init(quint64 new_init, bool single_action);
        void set_xor_out(quint64 new_xor_out, bool single_action);
        void set_ref_in(bool new_ref_in, bool single_action);
        void set_ref_out(bool new_ref_out, bool single_action);


        int  find_index();
        void update_index();
        void update_param(int new_index);
};





#endif // QUCRC_T_H
