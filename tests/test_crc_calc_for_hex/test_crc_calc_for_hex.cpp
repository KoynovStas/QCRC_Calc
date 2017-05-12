#include <QString>
#include <QtTest>

#include "crc_calc_for_hex.h"
#include "qucrc_t.h"





class Test_CRC_Calc_Hex : public QObject
{
    Q_OBJECT

    public:

        Test_CRC_Calc_Hex();


    private slots:
        void test_calculate();


    private:
        CRC_Calc_for_Hex hex_calc;
        QuCRC_t          qucrc;
};



Test_CRC_Calc_Hex::Test_CRC_Calc_Hex():
    QObject(0)
{
    hex_calc.set_ucrc(&qucrc);
}



void Test_CRC_Calc_Hex::test_calculate()
{
    //i = 1 //without custom CRC (custom CRC have index 0)
    for(size_t i = 1; i < QuCRC_t::CRC_List.size(); ++i)
    {
        CRC_Param_Info info = QuCRC_t::CRC_List[i];

        qucrc = info;

        hex_calc.calculate("31 32 33 34 35 36 37 38 39");

        if(hex_calc.result.get_result() != info.check)
        {
            QString msg = "For CRC: " + info.name;

            msg += "  std check: 0x"     + QString::number(info.check, 16);
            msg += "  but get_check: 0x" + QString::number(hex_calc.result.get_result(), 16);


            QFAIL(msg.toStdString().c_str());
        }
    }
}





QTEST_APPLESS_MAIN(Test_CRC_Calc_Hex)

#include "test_crc_calc_for_hex.moc"
