#include <QString>
#include <QtTest>

#include "crc_calc_for_text.h"
#include "qucrc_t.h"





class Test_CRC_Calc_Text : public QObject
{
    Q_OBJECT

    public:

        Test_CRC_Calc_Text();


    private slots:
        void test_calculate();


    private:
        CRC_Calc_for_Text text_calc;
        QuCRC_t           qucrc;
};



Test_CRC_Calc_Text::Test_CRC_Calc_Text():
    QObject(0)
{
    text_calc.set_ucrc(&qucrc);
}




void Test_CRC_Calc_Text::test_calculate()
{
    //i = 1 //without custom CRC (custom CRC have index 0)
    for(size_t i = 1; i < QuCRC_t::CRC_List.size(); ++i)
    {
        CRC_Param_Info info = QuCRC_t::CRC_List[i];

        qucrc.set_bits(info.bits);
        qucrc.set_poly(info.poly);
        qucrc.set_init(info.init);
        qucrc.set_xor_out(info.xor_out);
        qucrc.set_ref_in(info.ref_in);
        qucrc.set_ref_out(info.ref_out);



        text_calc.calculate("123456789");

        if(text_calc.result.get_result() != info.check)
        {
            QString msg = "For CRC: " + info.name;

            msg += "  std check: 0x"     + QString::number(info.check, 16);
            msg += "  but get_check: 0x" + QString::number(text_calc.result.get_result(), 16);


            QFAIL(msg.toStdString().c_str());
        }
    }
}





QTEST_APPLESS_MAIN(Test_CRC_Calc_Text)

#include "test_crc_calc_for_text.moc"
