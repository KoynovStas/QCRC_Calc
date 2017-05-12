#include <QtTest>
#include <QCoreApplication>

#include "qucrc_t.h"





class Test_QuCRC_t : public QObject
{
    Q_OBJECT


    private slots:
        void test_get_check();


    private:
        QuCRC_t  qucrc;
};



void Test_QuCRC_t::test_get_check()
{
    //i = 1 //without custom CRC (custom CRC have index 0)
    for(size_t i = 1; i < QuCRC_t::CRC_List.size(); ++i)
    {
        CRC_Param_Info info = QuCRC_t::CRC_List[i];

        qucrc = info;

        if(qucrc.get_check() != info.check)
        {
            QString msg = "For CRC: " + info.name;

            msg += "  std check: 0x"     + QString::number(info.check, 16);
            msg += "  but get_check: 0x" + QString::number(qucrc.get_check(), 16);


            QFAIL(msg.toStdString().c_str());
        }
    }
}





QTEST_MAIN(Test_QuCRC_t)

#include "test_qucrc_t.moc"
