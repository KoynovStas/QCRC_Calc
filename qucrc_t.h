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
#include <vector>

#include "ucrc_t.h"





struct CRC_Param_Info
{
    QString  name;
    uint8_t  bits;
    uint64_t poly;
    uint64_t init;
    bool     ref_in;
    bool     ref_out;
    uint64_t xor_out;


    CRC_Param_Info( QString  _name,
                    uint8_t  _bits,
                    uint64_t _poly,
                    uint64_t _init,
                    bool     _ref_in,
                    bool     _ref_out,
                    uint64_t _xor_out);
};





class QuCRC_t : public QObject //Qt wrapper for uCRC_t
{
    Q_OBJECT

    public:
        explicit QuCRC_t(QObject *parent = 0);


        static const std::vector<CRC_Param_Info> CRC_List;


    signals:

        void param_changed();
        void index_changed(uint32_t index);


    public slots:
        // get param CRC
        uint8_t  get_bits()    const { return ucrc.get_bits();   }
        uint64_t get_poly()    const { return ucrc.get_poly();   }
        uint64_t get_init()    const { return ucrc.get_init();   }
        uint64_t get_xor_out() const { return ucrc.get_xor_out();}
        bool     get_ref_in()  const { return ucrc.get_ref_in(); }
        bool     get_ref_out() const { return ucrc.get_ref_out();}

        uint64_t get_crc_init()const { return ucrc.get_crc_init();} //crc_init = reflect(init, bits) if RefIn, else = init
        uint64_t get_top_bit() const { return ucrc.get_top_bit(); }
        uint64_t get_crc_mask()const { return ucrc.get_crc_mask();}


        // set param CRC
        int  set_bits(uint8_t new_bits);
        void set_poly(uint64_t new_poly);
        void set_init(uint64_t new_init);
        void set_xor_out(uint64_t new_xor_out);
        void set_ref_in(bool new_ref_in);
        void set_ref_out(bool new_ref_out);


        // Calculate methods
        uint64_t get_crc(const char* buf, size_t len)          const { return ucrc.get_crc(buf, len);      }
        int      get_crc(uint64_t &crc, const char* file_name) const { return ucrc.get_crc(crc, file_name);}
        int      get_crc(uint64_t &crc, FILE* pfile)           const { return ucrc.get_crc(crc, pfile);    }

        int      get_crc(uint64_t &crc, const char* file_name, void* buf, size_t size_buf) const { return ucrc.get_crc(crc, file_name, buf, size_buf);}
        int      get_crc(uint64_t &crc, FILE* pfile, void* buf, size_t size_buf)           const { return ucrc.get_crc(crc, pfile, buf, size_buf);    }


        // Calculate for chunks of data
        uint64_t get_raw_crc(const char* buf, size_t len, uint64_t crc) const { return ucrc.get_raw_crc(buf, len, crc);}  //for first byte crc = crc_init (must be)
        uint64_t get_final_crc(uint64_t raw_crc)                        const { return ucrc.get_final_crc(raw_crc);    }


        uint64_t get_check();


        uint32_t get_index() const { return index; }
        int      set_index(uint32_t new_index);


    private:

        uCRC_t   ucrc;

        uint32_t index;

        uint32_t find_index();
        void     update_index();

        static const std::vector<CRC_Param_Info> get_crc_list();
};





#endif // QUCRC_T_H
