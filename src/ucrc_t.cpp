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
 */

#include <cstdio>
#include <cerrno>
#include <utility>
#include "ucrc_t.h"





uCRC_t::uCRC_t(std::string Name,
               uint8_t     Bits,
               uint64_t    Poly,
               uint64_t    Init,
               bool        RefIn,
               bool        RefOut,
               uint64_t    XorOut) noexcept:
    name   (std::move(Name)),
    poly   (Poly),
    init   (Init),
    xor_out(XorOut),
    bits   (Bits),
    ref_in (RefIn),
    ref_out(RefOut)
{
    init_class();
}



uCRC_t::uCRC_t(uint8_t  Bits,
               uint64_t Poly,
               uint64_t Init,
               bool     RefIn,
               bool     RefOut,
               uint64_t XorOut) noexcept:
    poly   (Poly),
    init   (Init),
    xor_out(XorOut),
    bits   (Bits),
    ref_in (RefIn),
    ref_out(RefOut)
{
    init_class();
}



int uCRC_t::get_crc(uint64_t &crc, const char *file_name, void *buf, size_t size_buf) const noexcept
{
    std::ifstream ifs(file_name, std::ios_base::binary);

    if( !ifs || !buf || !size_buf)
    {
        errno = EINVAL;
        return -1;
    }

    return get_crc(crc, ifs, buf, size_buf);
}



int uCRC_t::get_crc(uint64_t &crc, std::ifstream &ifs, void *buf, size_t size_buf) const noexcept
{
    crc = crc_init;

    while( ifs )
    {
        ifs.read(static_cast<char *>(buf), size_buf);
        crc = get_raw_crc(buf, ifs.gcount(), crc);
    }

    crc = get_end_crc(crc);

    return (ifs.rdstate() & std::ios_base::badbit); //return 0 if all good
}



uint64_t uCRC_t::get_raw_crc(const void* data, size_t len, uint64_t raw_crc) const noexcept
{
    auto buf = static_cast< const uint8_t* >(data);


    if(bits > 8)
    {
        if(ref_in)
            while (len--)
                raw_crc = (raw_crc >> 8) ^ crc_table[ (raw_crc ^ *buf++) & 0xff ];
        else
            while (len--)
                raw_crc = (raw_crc << 8) ^ crc_table[ ((raw_crc >> shift) ^ *buf++) & 0xff ];
    }
    else
    {
        if (ref_in)
            while (len--)
                raw_crc = crc_table[ (raw_crc ^ *buf++) & 0xff ];
        else
            while (len--)
                raw_crc = crc_table[ ((raw_crc << shift) ^ *buf++) & 0xff ];
    }


    return raw_crc;
}



uint64_t uCRC_t::reflect(uint64_t data, uint8_t num_bits) noexcept
{
    uint64_t reflection = 0;

    while( num_bits-- )
    {
        reflection = (reflection << 1) | (data & 1);
        data >>= 1;
    }

    return reflection;
}



void uCRC_t::init_crc_table() noexcept
{
    //Calculation of the standard CRC table for byte.
    for(int i = 0; i < 256; i++)
    {
        uint64_t crc = 0;

        for(uint8_t mask = 0x80; mask; mask >>= 1)
        {

            if ( i & mask )
                crc ^= top_bit;


            if (crc & top_bit)
            {
                crc <<= 1;
                crc ^= poly;
            }
            else
                crc <<= 1;
        }

        crc &= crc_mask; //for CRC not power 2

        if(ref_in)
            crc_table[reflect(i, 8)] = reflect(crc, bits);
        else
            crc_table[i] = crc;
    }
}



void uCRC_t::init_class() noexcept
{
    top_bit  = (uint64_t)1 << (bits - 1);
    crc_mask = ( (top_bit - 1) << 1) | 1;


    if(bits > 8)
        shift = (bits - 8);
    else
        shift = (8 - bits);


    if(ref_in)
        crc_init = reflect(init, bits);
    else
        crc_init = init;


    init_crc_table();
}
