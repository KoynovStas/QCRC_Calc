/*
 * qucrc_t.cpp
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

#include "qucrc_t.h"





const std::vector<CRC_Param_Info> QuCRC_t::CRC_List = QuCRC_t::get_crc_list();







CRC_Param_Info::CRC_Param_Info(QString _name, uint8_t _bits, uint64_t _poly, uint64_t _init, bool _ref_in, bool _ref_out, uint64_t _xor_out) :
    name(_name),
    bits(_bits),
    poly(_poly),
    init(_init),
    ref_in(_ref_in),
    ref_out(_ref_out),
    xor_out(_xor_out)
{
}





QuCRC_t::QuCRC_t(QObject *parent) :
    QObject(parent)
{
    index = find_index();
}



int QuCRC_t::set_bits(uint8_t new_bits)
{
    if( new_bits == ucrc.get_bits() )
        return 0;


    int ret = ucrc.set_bits(new_bits);
    if( ret == 0 )
    {
        update_index();
        emit param_changed();
    }

    return ret;
}



void QuCRC_t::set_poly(uint64_t new_poly)
{
    if( new_poly == ucrc.get_poly() )
        return;


    ucrc.set_poly(new_poly);


    update_index();
    emit param_changed();
}



void QuCRC_t::set_init(uint64_t new_init)
{
    if( new_init == ucrc.get_init() )
        return;


    ucrc.set_init(new_init);


    update_index();
    emit param_changed();
}



void QuCRC_t::set_xor_out(uint64_t new_xor_out)
{
    if( new_xor_out == ucrc.get_xor_out() )
        return;


    ucrc.set_xor_out(new_xor_out);


    update_index();
    emit param_changed();
}



void QuCRC_t::set_ref_in(bool new_ref_in)
{
    if( new_ref_in == ucrc.get_ref_in() )
        return;


    ucrc.set_ref_in(new_ref_in);


    update_index();
    emit param_changed();
}



void QuCRC_t::set_ref_out(bool new_ref_out)
{
    if( new_ref_out == ucrc.get_ref_out() )
        return;


    ucrc.set_ref_out(new_ref_out);


    update_index();
    emit param_changed();
}



uint64_t QuCRC_t::get_check()
{
    const char std_check_data[] = "123456789";

    return ucrc.get_crc(std_check_data, sizeof(std_check_data) - 1 ); //-1 without '\0'
}



int QuCRC_t::set_index(uint32_t new_index)
{
    if( new_index == index)
        return 0; //good job


    if( new_index >= CRC_List.size() )
        return -1; // new_index is bad


    index = new_index;


    //set crc param for new_index
    CRC_Param_Info tmp = CRC_List[new_index];

    ucrc.set_bits(tmp.bits);
    ucrc.set_poly(tmp.poly);
    ucrc.set_init(tmp.init);
    ucrc.set_xor_out(tmp.xor_out);
    ucrc.set_ref_in(tmp.ref_in);
    ucrc.set_ref_out(tmp.ref_out);


    emit index_changed(index);
    emit param_changed();


    return 0; //good job
}



uint32_t QuCRC_t::find_index()
{

    for(size_t i = 0; i < CRC_List.size(); ++i)
    {
        CRC_Param_Info tmp = CRC_List[i];

        if(
            tmp.bits    == ucrc.get_bits()    &&
            tmp.poly    == ucrc.get_poly()    &&
            tmp.init    == ucrc.get_init()    &&
            tmp.xor_out == ucrc.get_xor_out() &&
            tmp.ref_in  == ucrc.get_ref_in()  &&
            tmp.ref_out == ucrc.get_ref_out()
          )
            return i; //found
    }


    return 0; //not found
}



void QuCRC_t::update_index()
{
    uint32_t new_index = find_index();

    if( index == new_index )
        return;


    index = new_index;
    emit index_changed(index);
}



const std::vector<CRC_Param_Info> QuCRC_t::get_crc_list()
{
    std::vector<CRC_Param_Info> crc_list;


    crc_list.push_back(CRC_Param_Info("Custom", 0, 0, 0, false, false, 0) );


    // CRC-3
    crc_list.push_back(CRC_Param_Info("CRC-3/ROHC", 3, 0x3, 0x7, true, true, 0x0) );

    // CRC-4
    crc_list.push_back(CRC_Param_Info("CRC-4/ITU", 4, 0x3, 0x0, true, true, 0x0) );

    // CRC-5
    crc_list.push_back(CRC_Param_Info("CRC-5/EPC", 5, 0x09, 0x09, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-5/ITU", 5, 0x15, 0x00, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-5/USB", 5, 0x05, 0x1f, true,  true,  0x1f) );

    // CRC-6
    crc_list.push_back(CRC_Param_Info("CRC-6/CDMA2000-A", 6, 0x27, 0x3f, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-6/CDMA2000-B", 6, 0x07, 0x3f, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-6/DARC",       6, 0x19, 0x00, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-6/ITU",        6, 0x03, 0x00, true,  true,  0x0) );

    // CRC-7
    crc_list.push_back(CRC_Param_Info("CRC-7",      7, 0x09, 0x0,  false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-7/ROHC", 7, 0x4f, 0x7f, true,  true,  0x0) );

    // CRC-8
    crc_list.push_back(CRC_Param_Info("CRC-8",          8, 0x07, 0x00, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-8/CDMA2000", 8, 0x9b, 0xff, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-8/DARC",     8, 0x39, 0x00, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-8/DVB-S2",   8, 0xd5, 0x00, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-8/EBU",      8, 0x1d, 0xff, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-8/I-CODE",   8, 0x1d, 0xfd, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-8/ITU",      8, 0x07, 0x00, false, false, 0x55) );
    crc_list.push_back(CRC_Param_Info("CRC-8/MAXIM",    8, 0x31, 0x00, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-8/ROHC",     8, 0x07, 0xff, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-8/WCDMA",    8, 0x9b, 0x00, true,  true,  0x0) );

    // CRC-10
    crc_list.push_back(CRC_Param_Info("CRC-10",          10, 0x233, 0x000, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-10/CDMA2000", 10, 0x3d9, 0x3ff, false, false, 0x0) );

    // CRC-11
    crc_list.push_back(CRC_Param_Info("CRC-11", 11, 0x385, 0x01a, false, false, 0x0) );

    // CRC-12
    crc_list.push_back(CRC_Param_Info("CRC-12/3GPP",     12, 0x80f, 0x000, false, true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-12/CDMA2000", 12, 0xf13, 0xfff, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-12/DECT",     12, 0x80f, 0x000, false, false, 0x0) );

    // CRC-13
    crc_list.push_back(CRC_Param_Info("CRC-13/BBC", 13, 0x1cf5, 0x0, false, false, 0x0) );

    // CRC-14
    crc_list.push_back(CRC_Param_Info("CRC-14/DARC", 14, 0x0805, 0x0, true, true, 0x0) );

    // CRC-15
    crc_list.push_back(CRC_Param_Info("CRC-15",         15, 0x4599, 0x0, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-15/MPT1327", 15, 0x6815, 0x0, false, false, 0x1) );

    // CRC-16
    crc_list.push_back(CRC_Param_Info("CRC-16/ARC",         16, 0x8005, 0x0000, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/AUG-CCITT",   16, 0x1021, 0x1d0f, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/BUYPASS",     16, 0x8005, 0x0000, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/CCITT-FALSE", 16, 0x1021, 0xffff, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/CDMA2000",    16, 0xc867, 0xffff, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/DDS-110",     16, 0x8005, 0x800d, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/DECT-R",      16, 0x0589, 0x0000, false, false, 0x1) );
    crc_list.push_back(CRC_Param_Info("CRC-16/DECT-X",      16, 0x0589, 0x0000, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/DNP",         16, 0x3d65, 0x0000, true,  true,  0xffff) );
    crc_list.push_back(CRC_Param_Info("CRC-16/EN-13757",    16, 0x3d65, 0x0000, false, false, 0xffff) );
    crc_list.push_back(CRC_Param_Info("CRC-16/GENIBUS",     16, 0x1021, 0xffff, false, false, 0xffff) );
    crc_list.push_back(CRC_Param_Info("CRC-16/MAXIM",       16, 0x8005, 0x0000, true,  true,  0xffff) );
    crc_list.push_back(CRC_Param_Info("CRC-16/MCRF4XX",     16, 0x1021, 0xffff, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/RIELLO",      16, 0x1021, 0xb2aa, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/T10-DIF",     16, 0x8bb7, 0x0000, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/TELEDISK",    16, 0xa097, 0x0000, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/TMS37157",    16, 0x1021, 0x89ec, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/USB",         16, 0x8005, 0xffff, true,  true,  0xffff) );
    crc_list.push_back(CRC_Param_Info("CRC-A",              16, 0x1021, 0xc6c6, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/KERMIT",      16, 0x1021, 0x0000, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/MODBUS",      16, 0x8005, 0xffff, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-16/X-25",        16, 0x1021, 0xffff, true,  true,  0xffff) );
    crc_list.push_back(CRC_Param_Info("CRC-16/XMODEM",      16, 0x1021, 0x0000, false, false, 0x0) );

    // CRC-24
    crc_list.push_back(CRC_Param_Info("CRC-24",           24, 0x864cfb, 0xb704ce, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-24/FLEXRAY-A", 24, 0x5d6dcb, 0xfedcba, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-24/FLEXRAY-B", 24, 0x5d6dcb, 0xabcdef, false, false, 0x0) );

    // CRC-31
    crc_list.push_back(CRC_Param_Info("CRC-31/PHILIPS", 31, 0x04c11db7, 0x7fffffff, false, false, 0x7fffffff) );

    // CRC-32
    crc_list.push_back(CRC_Param_Info("CRC-32",       32, 0x04c11db7, 0xffffffff, true,  true,  0xffffffff) );
    crc_list.push_back(CRC_Param_Info("CRC-32/BZIP2", 32, 0x04c11db7, 0xffffffff, false, false, 0xffffffff) );
    crc_list.push_back(CRC_Param_Info("CRC-32C",      32, 0x1edc6f41, 0xffffffff, true,  true,  0xffffffff) );
    crc_list.push_back(CRC_Param_Info("CRC-32D",      32, 0xa833982b, 0xffffffff, true,  true,  0xffffffff) );
    crc_list.push_back(CRC_Param_Info("CRC-32/MPEG-2",32, 0x04c11db7, 0xffffffff, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-32/POSIX", 32, 0x04c11db7, 0x00000000, false, false, 0xffffffff) );
    crc_list.push_back(CRC_Param_Info("CRC-32Q",      32, 0x814141ab, 0x00000000, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-32/JAMCRC",32, 0x04c11db7, 0xffffffff, true,  true,  0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-32/XFER",  32, 0x000000af, 0x00000000, false, false, 0x0) );

    // CRC-40
    crc_list.push_back(CRC_Param_Info("CRC-40/GSM", 40, 0x0004820009, 0x0, false, false, 0xffffffffff) );

    // CRC-64
    crc_list.push_back(CRC_Param_Info("CRC-64",    64, 0x42f0e1eba9ea3693, 0x0000000000000000, false, false, 0x0) );
    crc_list.push_back(CRC_Param_Info("CRC-64/WE", 64, 0x42f0e1eba9ea3693, 0xffffffffffffffff, false, false, 0xffffffffffffffff) );
    crc_list.push_back(CRC_Param_Info("CRC-64/XZ", 64, 0x42f0e1eba9ea3693, 0xffffffffffffffff, true,  true,  0xffffffffffffffff) );


    return crc_list;
}
