/*
 * ucrc_t.h
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
 *
 * more details see https://github.com/KoynovStas/CRC_CPP_Class
 *
 */

#ifndef UCRC_T_H
#define UCRC_T_H

#include <stdint.h>
#include <string>
#include <cstdio>





class uCRC_t
{

    public:

        explicit uCRC_t(const std::string Name = "CRC-32",
                        uint8_t  Bits   = 32,
                        uint64_t Poly   = 0x04c11db7,
                        uint64_t Init   = 0xffffffff,
                        bool     RefIn  = true,
                        bool     RefOut = true,
                        uint64_t XorOut = 0xffffffff);


        explicit uCRC_t(uint8_t  Bits,
                        uint64_t Poly,
                        uint64_t Init,
                        bool     RefIn,
                        bool     RefOut,
                        uint64_t XorOut);


        std::string name;


        // get param CRC
        uint8_t  get_bits()    const { return bits;   }
        uint64_t get_poly()    const { return poly;   }
        uint64_t get_init()    const { return init;   }
        uint64_t get_xor_out() const { return xor_out;}
        bool     get_ref_in()  const { return ref_in; }
        bool     get_ref_out() const { return ref_out;}

        uint64_t get_crc_init()const { return crc_init;} //crc_init = reflect(init, bits) if RefIn, else = init
        uint64_t get_top_bit() const { return top_bit; }
        uint64_t get_crc_mask()const { return crc_mask;}


        // set param CRC
        int  set_bits(uint8_t new_bits);
        void set_poly(uint64_t new_poly)       { poly    = new_poly; init_class();}
        void set_init(uint64_t new_init)       { init    = new_init; init_class();}
        void set_xor_out(uint64_t new_xor_out) { xor_out = new_xor_out;}
        void set_ref_in(bool new_ref_in)       { ref_in  = new_ref_in; init_class();}
        void set_ref_out(bool new_ref_out)     { ref_out = new_ref_out;}


        // Calculate methods
        uint64_t get_crc(const char* buf, size_t len) const;
        int      get_crc(uint64_t &crc, const char* file_name) const;
        int      get_crc(uint64_t &crc, FILE* pfile) const;
        int      get_crc(uint64_t &crc, const char* file_name, void* buf, size_t size_buf) const;
        int      get_crc(uint64_t &crc, FILE* pfile, void* buf, size_t size_buf) const;


        // Calculate for chunks of data
        uint64_t get_raw_crc(const char* buf, size_t len, uint64_t crc) const; //for first byte crc = crc_init (must be)
        uint64_t get_final_crc(uint64_t raw_crc) const;



    private:

        uint8_t  bits;
        uint64_t poly;
        uint64_t init;
        bool     ref_in;
        bool     ref_out;
        uint64_t xor_out;

        uint8_t  shift;
        uint64_t crc_init;
        uint64_t top_bit;
        uint64_t crc_mask;
        uint64_t crc_table[256];


        uint64_t reflect(uint64_t data, uint8_t num_bits) const;
        void     init_crc_table();
        void     init_class();
};





#endif // UCRC_T_H
