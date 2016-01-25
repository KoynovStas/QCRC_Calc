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





QuCRC_t::QuCRC_t(QObject *parent) :
    QObject(parent)
{
}



int QuCRC_t::set_bits(uint8_t new_bits)
{
    if( new_bits == ucrc.get_bits() )
        return 0;


    int ret = ucrc.set_bits(new_bits);
    if( ret == 0 )
        emit param_changed();

    return ret;
}



void QuCRC_t::set_poly(uint64_t new_poly)
{
    if( new_poly == ucrc.get_poly() )
        return;


    ucrc.set_poly(new_poly);
    emit param_changed();
}



void QuCRC_t::set_init(uint64_t new_init)
{
    if( new_init == ucrc.get_init() )
        return;


    ucrc.set_init(new_init);
    emit param_changed();
}



void QuCRC_t::set_xor_out(uint64_t new_xor_out)
{
    if( new_xor_out == ucrc.get_xor_out() )
        return;


    ucrc.set_xor_out(new_xor_out);
    emit param_changed();
}



void QuCRC_t::set_ref_in(bool new_ref_in)
{
    if( new_ref_in == ucrc.get_ref_in() )
        return;


    ucrc.set_ref_in(new_ref_in);
    emit param_changed();
}



void QuCRC_t::set_ref_out(bool new_ref_out)
{
    if( new_ref_out == ucrc.get_ref_out() )
        return;


    ucrc.set_ref_out(new_ref_out);
    emit param_changed();
}
