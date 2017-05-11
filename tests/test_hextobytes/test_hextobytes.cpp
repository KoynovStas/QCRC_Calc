#include <QString>
#include <QtTest>

#include "hextobytes.h"





class Test_HexToBytes : public QObject
{
    Q_OBJECT


    private slots:
        void test_num_words_data();
        void test_num_words();


    private:
        HexToBytes hex_to_bytes;
};



void Test_HexToBytes::test_num_words_data()
{
    QTest::addColumn<QString>("string");
    QTest::addColumn<int>    ("result");


    // Format  Result.Number_Test
    QTest::newRow("0.0") << ""       << 0;
    QTest::newRow("0.1") << "qwerty" << 0;
    QTest::newRow("0.2") << "      " << 0;
    QTest::newRow("0.3") << "___12_" << 0;

    QTest::newRow("1.0") << "1"         << 1;
    QTest::newRow("1.1") << "11"        << 1;
    QTest::newRow("1.2") << "0xF"       << 1;
    QTest::newRow("1.3") << "0xFF"      << 1;
    QTest::newRow("1.4") << "  0xFF"    << 1;
    QTest::newRow("1.5") << "  0xFF   " << 1;
    QTest::newRow("1.6") << "  0xFF, "  << 1;



    QTest::newRow("2.0")  << "1 2"       << 2;
    QTest::newRow("2.1")  << "0x1 2"     << 2;
    QTest::newRow("2.2")  << "FF 2"      << 2;
    QTest::newRow("2.3")  << "0xFF; 2"   << 2;
    QTest::newRow("2.4")  << "1 0xFF"    << 2;
    QTest::newRow("2.5")  << "1; 2"      << 2;
    QTest::newRow("2.6")  << "1 2;"      << 2;
    QTest::newRow("2.7")  << "1, 2;"     << 2;
    QTest::newRow("2.8")  << "12345 2"   << 2;
    QTest::newRow("2.9")  << "0x1122334455667788 2"  << 2;
    QTest::newRow("2.10") << "0x11223344556677881122334455667788 2" << 2;
}



void Test_HexToBytes::test_num_words()
{
    QFETCH(QString, string);
    QFETCH(int,     result);


    hex_to_bytes.str_to_bytes(string);
    QCOMPARE(hex_to_bytes.get_num_words(), (quint32)result);
}





QTEST_APPLESS_MAIN(Test_HexToBytes)

#include "test_hextobytes.moc"
