/*
 * qucrc_t.cpp
 *
 *
 * version 1.3
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

#include "qucrc_t.h"








#ifdef TEST
    #define  CRC_PARAM_INFO(name, bits, poly, init, ref_in, ref_out, xor_out, check) \
                           {name, bits, poly, init, ref_in, ref_out, xor_out, check}
#else
    #define  CRC_PARAM_INFO(name, bits, poly, init, ref_in, ref_out, xor_out, check) \
                           {name, bits, poly, init, ref_in, ref_out, xor_out}
#endif



/*
 * Catalogue of parametrised CRC algorithms
 * more see http://reveng.sourceforge.net/crc-catalogue/
*/
const std::vector<CRC_Param_Info> QuCRC_t::CRC_List =
{
    CRC_PARAM_INFO("Custom", 0, 0, 0, false, false, 0, 0),


    // CRC-3
    CRC_PARAM_INFO("CRC-3/GSM",  3, 0x3, 0,   false, false, 0x7, 0x4),
    CRC_PARAM_INFO("CRC-3/ROHC", 3, 0x3, 0x7, true,  true,  0x0, 0x6),

    // CRC-4
    CRC_PARAM_INFO("CRC-4/ITU",        4, 0x3, 0x0, true,  true,  0x0, 0x7),
    CRC_PARAM_INFO("CRC-4/INTERLAKEN", 4, 0x3, 0xF, false, false, 0xF, 0xB),

    // CRC-5
    CRC_PARAM_INFO("CRC-5/EPC", 5, 0x09, 0x09, false, false, 0x0,  0x0 ),
    CRC_PARAM_INFO("CRC-5/ITU", 5, 0x15, 0x00, true,  true,  0x0,  0x7 ),
    CRC_PARAM_INFO("CRC-5/USB", 5, 0x05, 0x1F, true,  true,  0x1F, 0x19),

    // CRC-6
    CRC_PARAM_INFO("CRC-6/CDMA2000-A", 6, 0x27, 0x3F, false, false, 0x0,  0x0D),
    CRC_PARAM_INFO("CRC-6/CDMA2000-B", 6, 0x07, 0x3F, false, false, 0x0,  0x3B),
    CRC_PARAM_INFO("CRC-6/DARC",       6, 0x19, 0x00, true,  true,  0x0,  0x26),
    CRC_PARAM_INFO("CRC-6/ITU",        6, 0x03, 0x00, true,  true,  0x0,  0x06),
    CRC_PARAM_INFO("CRC-6/GSM",        6, 0x2F, 0x00, false, false, 0x3F, 0x13),

    // CRC-7
    CRC_PARAM_INFO("CRC-7",      7, 0x9,  0x0,  false, false, 0x0, 0x75),
    CRC_PARAM_INFO("CRC-7/ROHC", 7, 0x4F, 0x7F, true,  true,  0x0, 0x53),
    CRC_PARAM_INFO("CRC-7/UMTS", 7, 0x45, 0x0,  false, false, 0x0, 0x61),

    // CRC-8
    CRC_PARAM_INFO("CRC-8",            8, 0x7,  0x0,  false, false, 0x0,  0xF4),
    CRC_PARAM_INFO("CRC-8/AUTOSAR",    8, 0x2F, 0xFF, false, false, 0xFF, 0xDF),
    CRC_PARAM_INFO("CRC-8/CDMA2000",   8, 0x9B, 0xFF, false, false, 0x0,  0xDA),
    CRC_PARAM_INFO("CRC-8/DARC",       8, 0x39, 0x0,  true,  true,  0x0,  0x15),
    CRC_PARAM_INFO("CRC-8/DVB-S2",     8, 0xD5, 0x0,  false, false, 0x0,  0xBC),
    CRC_PARAM_INFO("CRC-8/EBU",        8, 0x1D, 0xFF, true,  true,  0x0,  0x97),
    CRC_PARAM_INFO("CRC-8/GSM-A",      8, 0x1D, 0x0,  false, false, 0x0,  0x37),
    CRC_PARAM_INFO("CRC-8/GSM-B",      8, 0x49, 0x0,  false, false, 0xFF, 0x94),
    CRC_PARAM_INFO("CRC-8/I-CODE",     8, 0x1D, 0xFD, false, false, 0x0,  0x7E),
    CRC_PARAM_INFO("CRC-8/ITU",        8, 0x7,  0x0,  false, false, 0x55, 0xA1),
    CRC_PARAM_INFO("CRC-8/LTE",        8, 0x9B, 0x0,  false, false, 0x0,  0xEA),
    CRC_PARAM_INFO("CRC-8/MAXIM",      8, 0x31, 0x0,  true,  true,  0x0,  0xA1),
    CRC_PARAM_INFO("CRC-8/OPENSAFETY", 8, 0x2F, 0x0,  false, false, 0x0,  0x3E),
    CRC_PARAM_INFO("CRC-8/ROHC",       8, 0x7,  0xFF, true,  true,  0x0,  0xD0),
    CRC_PARAM_INFO("CRC-8/SAE-J1850",  8, 0x1D, 0xFF, false, false, 0xFF, 0x4B),
    CRC_PARAM_INFO("CRC-8/WCDMA",      8, 0x9B, 0x0,  true,  true,  0x0,  0x25),

    // CRC-10
    CRC_PARAM_INFO("CRC-10",          10, 0x233, 0x0,   false, false, 0x0,   0x199),
    CRC_PARAM_INFO("CRC-10/CDMA2000", 10, 0x3D9, 0x3FF, false, false, 0x0,   0x233),
    CRC_PARAM_INFO("CRC-10/GSM",      10, 0x175, 0x0,   false, false, 0x3FF, 0x12A),

    // CRC-11
    CRC_PARAM_INFO("CRC-11",      11, 0x385, 0x1A, false, false, 0x0, 0x5A3),
    CRC_PARAM_INFO("CRC-11/UMTS", 11, 0x307, 0x0,  false, false, 0x0, 0x061),

    // CRC-12
    CRC_PARAM_INFO("CRC-12/3GPP",     12, 0x80F, 0x0,   false, true,  0x0,   0xDAF),
    CRC_PARAM_INFO("CRC-12/CDMA2000", 12, 0xF13, 0xFFF, false, false, 0x0,   0xD4D),
    CRC_PARAM_INFO("CRC-12/DECT",     12, 0x80F, 0x0,   false, false, 0x0,   0xF5B),
    CRC_PARAM_INFO("CRC-12/GSM",      12, 0xD31, 0x0,   false, false, 0xFFF, 0xB34),

    // CRC-13
    CRC_PARAM_INFO("CRC-13/BBC", 13, 0x1CF5, 0x0, false, false, 0x0, 0x4FA),

    // CRC-14
    CRC_PARAM_INFO("CRC-14/DARC", 14, 0x805,  0x0, true,  true,  0x0,    0x82D ),
    CRC_PARAM_INFO("CRC-14/GSM",  14, 0x202D, 0x0, false, false, 0x3FFF, 0x30AE),

    // CRC-15
    CRC_PARAM_INFO("CRC-15",         15, 0x4599, 0x0, false, false, 0x0, 0x59E ),
    CRC_PARAM_INFO("CRC-15/MPT1327", 15, 0x6815, 0x0, false, false, 0x1, 0x2566),

    // CRC-16
    CRC_PARAM_INFO("CRC-16/ARC",         16, 0x8005, 0x0,    true,  true,  0x0,    0xBB3D),
    CRC_PARAM_INFO("CRC-16/AUG-CCITT",   16, 0x1021, 0x1D0F, false, false, 0x0,    0xE5CC),
    CRC_PARAM_INFO("CRC-16/BUYPASS",     16, 0x8005, 0x0,    false, false, 0x0,    0xFEE8),
    CRC_PARAM_INFO("CRC-16/CCITT-FALSE", 16, 0x1021, 0xFFFF, false, false, 0x0,    0x29B1),
    CRC_PARAM_INFO("CRC-16/CDMA2000",    16, 0xC867, 0xFFFF, false, false, 0x0,    0x4C06),
    CRC_PARAM_INFO("CRC-16/CMS",         16, 0x8005, 0xFFFF, false, false, 0x0,    0xAEE7),
    CRC_PARAM_INFO("CRC-16/DDS-110",     16, 0x8005, 0x800D, false, false, 0x0,    0x9ECF),
    CRC_PARAM_INFO("CRC-16/DECT-R",      16, 0x589,  0x0,    false, false, 0x1,    0x7E  ),
    CRC_PARAM_INFO("CRC-16/DECT-X",      16, 0x589,  0x0,    false, false, 0x0,    0x7F  ),
    CRC_PARAM_INFO("CRC-16/DNP",         16, 0x3D65, 0x0,    true,  true,  0xFFFF, 0xEA82),
    CRC_PARAM_INFO("CRC-16/EN-13757",    16, 0x3D65, 0x0,    false, false, 0xFFFF, 0xC2B7),
    CRC_PARAM_INFO("CRC-16/GENIBUS",     16, 0x1021, 0xFFFF, false, false, 0xFFFF, 0xD64E),
    CRC_PARAM_INFO("CRC-16/GSM",         16, 0x1021, 0x0,    false, false, 0xFFFF, 0xCE3C),
    CRC_PARAM_INFO("CRC-16/LJ1200",      16, 0x6F63, 0x0,    false, false, 0x0,    0xBDF4),
    CRC_PARAM_INFO("CRC-16/MAXIM",       16, 0x8005, 0x0,    true,  true,  0xFFFF, 0x44C2),
    CRC_PARAM_INFO("CRC-16/MCRF4XX",     16, 0x1021, 0xFFFF, true,  true,  0x0,    0x6F91),
    CRC_PARAM_INFO("CRC-16/OPENSAFETY-A",16, 0x5935, 0x0,    false, false, 0x0,    0x5D38),
    CRC_PARAM_INFO("CRC-16/OPENSAFETY-B",16, 0x755B, 0x0,    false, false, 0x0,    0x20FE),
    CRC_PARAM_INFO("CRC-16/PROFIBUS",    16, 0x1DCF, 0xFFFF, false, false, 0xFFFF, 0xA819),
    CRC_PARAM_INFO("CRC-16/RIELLO",      16, 0x1021, 0xB2AA, true,  true,  0x0,    0x63D0),
    CRC_PARAM_INFO("CRC-16/T10-DIF",     16, 0x8BB7, 0x0,    false, false, 0x0,    0xD0DB),
    CRC_PARAM_INFO("CRC-16/TELEDISK",    16, 0xA097, 0x0,    false, false, 0x0,    0xFB3 ),
    CRC_PARAM_INFO("CRC-16/TMS37157",    16, 0x1021, 0x89EC, true,  true,  0x0,    0x26B1),
    CRC_PARAM_INFO("CRC-16/USB",         16, 0x8005, 0xFFFF, true,  true,  0xFFFF, 0xB4C8),
    CRC_PARAM_INFO("CRC-16/CRC-A",       16, 0x1021, 0xC6C6, true,  true,  0x0,    0xBF05),
    CRC_PARAM_INFO("CRC-16/KERMIT",      16, 0x1021, 0x0,    true,  true,  0x0,    0x2189),
    CRC_PARAM_INFO("CRC-16/MODBUS",      16, 0x8005, 0xFFFF, true,  true,  0x0,    0x4B37),
    CRC_PARAM_INFO("CRC-16/X-25",        16, 0x1021, 0xFFFF, true,  true,  0xFFFF, 0x906E),
    CRC_PARAM_INFO("CRC-16/XMODEM",      16, 0x1021, 0x0,    false, false, 0x0,    0x31C3),

    // CRC-24
    CRC_PARAM_INFO("CRC-24",            24, 0x864CFB, 0xB704CE, false, false, 0x0,      0x21CF02),
    CRC_PARAM_INFO("CRC-24/BLE",        24, 0x65B,    0x555555, true,  true,  0x0,      0xC25A56),
    CRC_PARAM_INFO("CRC-24/FLEXRAY-A",  24, 0x5D6DCB, 0xFEDCBA, false, false, 0x0,      0x7979BD),
    CRC_PARAM_INFO("CRC-24/FLEXRAY-B",  24, 0x5D6DCB, 0xABCDEF, false, false, 0x0,      0x1F23B8),
    CRC_PARAM_INFO("CRC-24/INTERLAKEN", 24, 0x328B63, 0xFFFFFF, false, false, 0xFFFFFF, 0xB4F3E6),
    CRC_PARAM_INFO("CRC-24/LTE-A",      24, 0x864CFB, 0x0,      false, false, 0x0,      0xCDE703),
    CRC_PARAM_INFO("CRC-24/LTE-B",      24, 0x800063, 0x0,      false, false, 0x0,      0x23EF52),

    // CRC-30
    CRC_PARAM_INFO("CRC-30/CDMA", 30, 0x2030B9C7, 0x3FFFFFFF, false, false, 0x3FFFFFFF, 0x4C34ABF),

    // CRC-31
    CRC_PARAM_INFO("CRC-31/PHILIPS", 31, 0x4C11DB7, 0x7FFFFFFF, false, false, 0x7FFFFFFF, 0xCE9E46C),

    // CRC-32
    CRC_PARAM_INFO("CRC-32",        32, 0x4C11DB7,  0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0xCBF43926),
    CRC_PARAM_INFO("CRC-32/AUTOSAR",32, 0xF4ACFB13, 0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0x1697D06A),
    CRC_PARAM_INFO("CRC-32/BZIP2",  32, 0x4C11DB7,  0xFFFFFFFF, false, false, 0xFFFFFFFF, 0xFC891918),
    CRC_PARAM_INFO("CRC-32C",       32, 0x1EDC6F41, 0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0xE3069283),
    CRC_PARAM_INFO("CRC-32D",       32, 0xA833982B, 0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0x87315576),
    CRC_PARAM_INFO("CRC-32/MPEG-2", 32, 0x4C11DB7,  0xFFFFFFFF, false, false, 0x0,        0x376E6E7 ),
    CRC_PARAM_INFO("CRC-32/POSIX",  32, 0x4C11DB7,  0x0,        false, false, 0xFFFFFFFF, 0x765E7680),
    CRC_PARAM_INFO("CRC-32Q",       32, 0x814141AB, 0x0,        false, false, 0x0,        0x3010BF7F),
    CRC_PARAM_INFO("CRC-32/JAMCRC", 32, 0x4C11DB7,  0xFFFFFFFF, true,  true,  0x0,        0x340BC6D9),
    CRC_PARAM_INFO("CRC-32/XFER",   32, 0xAF,       0x0,        false, false, 0x0,        0xBD0BE338),

    // CRC-40
    CRC_PARAM_INFO("CRC-40/GSM", 40, 0x4820009, 0x0, false, false, 0xFFFFFFFFFF, 0xD4164FC646),

    // CRC-64
    CRC_PARAM_INFO("CRC-64",       64, 0x42F0E1EBA9EA3693, 0x0,                false, false, 0x0,                0x6C40DF5F0B497347),
    CRC_PARAM_INFO("CRC-64/GO-ISO",64, 0x1B,               0xFFFFFFFFFFFFFFFF, true,  true,  0xFFFFFFFFFFFFFFFF, 0xB90956C775A41001),
    CRC_PARAM_INFO("CRC-64/WE",    64, 0x42F0E1EBA9EA3693, 0xFFFFFFFFFFFFFFFF, false, false, 0xFFFFFFFFFFFFFFFF, 0x62EC59E3F1A4F00A),
    CRC_PARAM_INFO("CRC-64/XZ",    64, 0x42F0E1EBA9EA3693, 0xFFFFFFFFFFFFFFFF, true,  true,  0xFFFFFFFFFFFFFFFF, 0x995DC9BBDF1939FA)
};





QuCRC_t::QuCRC_t(QObject *parent) :
    QObject(parent)
{
    index = find_index();
}



QStringList QuCRC_t::crc_names() const
{
    QStringList list;

    for(size_t i = 0; i < CRC_List.size(); ++i)
        list.push_back(CRC_List[i].name);

    return list;
}



bool QuCRC_t::operator==(const CRC_Param_Info &r) const
{
    return (
        r.bits    == get_bits()    &&
        r.poly    == get_poly()    &&
        r.init    == get_init()    &&
        r.xor_out == get_xor_out() &&
        r.ref_in  == get_ref_in()  &&
        r.ref_out == get_ref_out()
    );
}



QuCRC_t &QuCRC_t::operator=(const CRC_Param_Info &r)
{
    if( !(*this == r) )
    {
        set_bits   (r.bits,    false);
        set_poly   (r.poly,    false);
        set_init   (r.init,    false);
        set_xor_out(r.xor_out, false);
        set_ref_in (r.ref_in,  false);
        set_ref_out(r.ref_out, false);


        emit paramChanged();
        update_index();
    }


    return *this;
}



int QuCRC_t::set_index(int new_index)
{
    if( new_index == index )
        return 0; //good job (index already set - no action)


    if( (size_t)new_index >= CRC_List.size() )
        return -1; // new_index is bad


    index = new_index;
    emit indexChanged();


    if( new_index != 0 )                 //no action for Custom CRC
        *this = CRC_List[new_index];


    return 0; //good job
}



int QuCRC_t::set_bits(quint8 new_bits, bool single_action)
{
    if( new_bits == ucrc.get_bits() )
        return 0; //no action


    int ret = ucrc.set_bits(new_bits);
    if( ret != 0 )
        return ret; //error set bits


    emit bitsChanged();

    if( single_action )
    {
        emit paramChanged();
        update_index();
    }


    return 0; //good job
}



void QuCRC_t::set_poly(quint64 new_poly, bool single_action)
{
    if( new_poly == ucrc.get_poly() )
        return;


    ucrc.set_poly(new_poly);
    emit polyChanged();


    if( single_action )
    {
        emit paramChanged();
        update_index();
    }
}



void QuCRC_t::set_init(quint64 new_init, bool single_action)
{
    if( new_init == ucrc.get_init() )
        return;


    ucrc.set_init(new_init);
    emit initChanged();


    if( single_action )
    {
        emit paramChanged();
        update_index();
    }
}



void QuCRC_t::set_xor_out(quint64 new_xor_out, bool single_action)
{
    if( new_xor_out == ucrc.get_xor_out() )
        return;


    ucrc.set_xor_out(new_xor_out);
    emit xor_outChanged();


    if( single_action )
    {
        emit paramChanged();
        update_index();
    }
}



void QuCRC_t::set_ref_in(bool new_ref_in, bool single_action)
{
    if( new_ref_in == ucrc.get_ref_in() )
        return;


    ucrc.set_ref_in(new_ref_in);
    emit ref_inChanged();


    if( single_action )
    {
        emit paramChanged();
        update_index();
    }
}



void QuCRC_t::set_ref_out(bool new_ref_out, bool single_action)
{
    if( new_ref_out == ucrc.get_ref_out() )
        return;


    ucrc.set_ref_out(new_ref_out);
    emit ref_outChanged();


    if( single_action )
    {
        emit paramChanged();
        update_index();
    }
}



int QuCRC_t::find_index()
{

    for(size_t i = 0; i < CRC_List.size(); ++i)
    {
        if( *this == CRC_List[i] )
            return i; //found
    }


    return 0; //not found (return 0 - custom)
}



void QuCRC_t::update_index()
{
    int new_index = find_index();

    if( index == new_index )
        return;


    index = new_index;
    emit indexChanged();
}
