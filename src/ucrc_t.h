/*
 * uCRC_t - is C++ class for calculation CRC any sizes 1-64 bits
 *
 *
 * version 2.0
 *
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * more details see https://github.com/KoynovStas/uCRC_t
 *
 */

#ifndef UCRC_T_H
#define UCRC_T_H

#include <cstdint>
#include <string>
#include <fstream>    // for std::ifstream
#include <ios>        // for std::ios_base, etc.





class uCRC_t
{
    public:
        explicit uCRC_t(std::string Name   = "CRC-32",
                        uint8_t     Bits   = 32,
                        uint64_t    Poly   = 0x04c11db7,
                        uint64_t    Init   = 0xffffffff,
                        bool        RefIn  = true,
                        bool        RefOut = true,
                        uint64_t    XorOut = 0xffffffff) noexcept;


        explicit uCRC_t(uint8_t  Bits,
                        uint64_t Poly,
                        uint64_t Init,
                        bool     RefIn,
                        bool     RefOut,
                        uint64_t XorOut) noexcept;


        std::string name;


        // get param CRC
        uint8_t  get_bits()    const noexcept { return bits;   }
        uint64_t get_poly()    const noexcept { return poly;   }
        uint64_t get_init()    const noexcept { return init;   }
        uint64_t get_xor_out() const noexcept { return xor_out;}
        bool     get_ref_in()  const noexcept { return ref_in; }
        bool     get_ref_out() const noexcept { return ref_out;}

        uint64_t get_top_bit() const noexcept { return top_bit; }
        uint64_t get_crc_mask()const noexcept { return crc_mask;}
        uint64_t get_crc_init()const noexcept { return crc_init;} //crc_init = reflect(init, bits) if RefIn, else = init
        uint64_t get_check()   const noexcept;                    //crc for ASCII string "123456789" (i.e. 313233... (hexadecimal)).


        // set param CRC
        int  set_bits(uint8_t new_value)     noexcept;
        void set_poly(uint64_t new_value)    noexcept { poly    = new_value; init_class();}
        void set_init(uint64_t new_value)    noexcept { init    = new_value; init_class();}
        void set_xor_out(uint64_t new_value) noexcept { xor_out = new_value;}
        void set_ref_in(bool new_value)      noexcept { ref_in  = new_value; init_class();}
        void set_ref_out(bool new_value)     noexcept { ref_out = new_value;}


        // Calculate methods
        uint64_t get_crc(const void* data, size_t len) const noexcept;
        int      get_crc(uint64_t &crc, const char* file_name) const noexcept;
        int      get_crc(uint64_t &crc, const char* file_name, void* buf, size_t size_buf) const noexcept;


        // Calculate for chunks of data
        uint64_t get_raw_crc(const void* data, size_t len) const noexcept;                   //get raw_crc for first chunk of data
        uint64_t get_raw_crc(const void* data, size_t len, uint64_t raw_crc) const noexcept; //get raw_crc for chunk of data
        uint64_t get_end_crc(uint64_t raw_crc) const noexcept;


    private:
        uint64_t poly;
        uint64_t init;
        uint64_t xor_out;
        uint64_t crc_init;  //crc_init = reflect(init, bits) if RefIn, else = init
        uint64_t top_bit;
        uint64_t crc_mask;
        uint64_t crc_table[256];

        uint8_t  bits;
        uint8_t  shift;
        bool     ref_in;
        bool     ref_out;


        static uint64_t reflect(uint64_t data, uint8_t num_bits) noexcept;
        void init_crc_table() noexcept;
        void init_class() noexcept;

        int  get_crc(uint64_t &crc, std::ifstream& ifs, void* buf, size_t size_buf) const noexcept;
};





inline uint64_t uCRC_t::get_check() const noexcept
{
    const uint8_t data[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

    return get_crc(data, sizeof(data));
}



inline int uCRC_t::set_bits(uint8_t new_value) noexcept
{
    if( (new_value < 1) || (new_value > 64) )
        return -1; //error

    bits = new_value;
    init_class();

    return 0; //good job
}



inline uint64_t uCRC_t::get_crc(const void* data, size_t len) const noexcept
{
    uint64_t crc = get_raw_crc(data, len, crc_init);

    return get_end_crc(crc);
}



inline int uCRC_t::get_crc(uint64_t& crc, const char* file_name) const noexcept
{
    char buf[4096];

    return get_crc(crc, file_name, buf, sizeof(buf));
}



inline uint64_t uCRC_t::get_raw_crc(const void* data, size_t len) const noexcept
{
    return get_raw_crc(data, len, crc_init);
}



inline uint64_t uCRC_t::get_end_crc(uint64_t raw_crc) const noexcept
{
    if(ref_out^ref_in) raw_crc = reflect(raw_crc, bits);

    raw_crc ^= xor_out;
    raw_crc &= crc_mask; //for CRC not power 2

    return raw_crc;
}





#endif // UCRC_T_H
