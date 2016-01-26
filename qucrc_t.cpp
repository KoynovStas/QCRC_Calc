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

    crc_list.push_back(CRC_Param_Info("CRC-32", 32, 0x04c11db7, 0xffffffff, true, true, 0xffffffff) );


    return crc_list;
}
