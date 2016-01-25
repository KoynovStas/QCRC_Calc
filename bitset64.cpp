/*
 * bitset64.cpp
 *
 * version 1.0
 *
 *
 * Copyright (c) 2016, Koynov Stas - skojnov@yandex.ru
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

#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "bitset64.h"
#include "bitwidget.h"






BitSet64::BitSet64(QWidget *parent) :
    QWidget(parent),
    value_(0)
{

	// main layout
	QGridLayout *layout = new QGridLayout(this);
    layout->setMargin(10);
    layout->setHorizontalSpacing(20);
    layout->setVerticalSpacing(5);


    bit_widgets_.reserve(64);

    // create bits
    int bitCounter = 63;
    for (int rows = 0; rows < 2; rows++)
    {
        for (int cols = 0; cols < 4; cols++)
        {
            // two rows of four words
            QHBoxLayout *wordlayout = new QHBoxLayout();
            wordlayout->setMargin(2);
            wordlayout->setSpacing(2);
            layout->addLayout(wordlayout, rows, cols);

            for (int bit = 0; bit < 8; bit++)
            {
                // layout for bit
                QVBoxLayout *bitlayout = new QVBoxLayout();
                bitlayout->setMargin(2);
                bitlayout->setSpacing(2);

                // BitWidget for bit
                BitWidget *tmp_bit_widget = new BitWidget(this);
                bit_widgets_[bitCounter] = tmp_bit_widget;
                bitlayout->addWidget(tmp_bit_widget);

                // label for bit
                QLabel *label = new QLabel(this);
                label->setText(QString::number(bitCounter));
                label->setAlignment(Qt::AlignCenter);
                bitlayout->addWidget(label);
                bitlayout->addStretch(1);

                wordlayout->addLayout(bitlayout);
                wordlayout->addStretch(1);

                bitCounter--;
            }
        }
    }
}



void BitSet64::set_value(quint64 value)
{

    if( value_ == value )
        return;

    value_ = value;

    // set each bit_widget
    for(int i = 0; i < 64; i++)
    {
        bit_widgets_[i]->set_on(value & 1);

        value >>= 1;
    }
}
