#include <QString>
#include <QtTest>

#include <getopt.h>

#include "application.h"




#include <iostream>
#include <fstream>



class StreamRedirect
{
    public:
        StreamRedirect(std::ostream & in_original, std::ostream & in_redirect) :
            m_original(in_original),
            m_old_buf(in_original.rdbuf(in_redirect.rdbuf()))
        { }

        ~StreamRedirect()
        {
            m_original.rdbuf(m_old_buf);
        }

    private:
        Q_DISABLE_COPY(ScopedRedirect)

        std::ostream   &m_original;
        std::streambuf *m_old_buf;
};





class Test_Application : public QObject
{
    Q_OBJECT

    public:
        Test_Application();


    private slots:
        void test_process_cmd();
        void test_crc_index_cmd();
        void test_crc_name_cmd();


    private:
        void prepare_report(QuCRC_t & uCRC);
        void prepare_argv(std::vector<std::string> &cmd);


        static const size_t MAX_ARGC = 512;

        QString report;

        int   argc;
        char *argv[MAX_ARGC];

        Application& app;
        CRC_Param_Info info;
};



Test_Application::Test_Application():
    QObject(0),

    //private
    argc(0),
    app(Application::get_instance(argc, NULL))
{
}



void Test_Application::test_process_cmd()
{

    //i = 1 //without custom CRC (custom CRC have index 0)
    for(size_t i = 1; i < QuCRC_t::CRC_List.size(); ++i)
    {
        info = QuCRC_t::CRC_List[i];

        std::vector<std::string> cmd = {
            "--bits"    , QString::number(info.bits,    10).toStdString(),
            "--poly"    , QString::number(info.poly,    16).toStdString(),
            "--init"    , QString::number(info.init,    16).toStdString(),
            "--xor_out" , QString::number(info.xor_out, 16).toStdString(),
            "--ref_in"  , QString::number(info.ref_in,  10).toStdString(),
            "--ref_out" , QString::number(info.ref_out, 10).toStdString()
        };


        prepare_argv(cmd);

        app.processing_cmd(argc, argv);

        if( !(app.uCRC == info) )
        {
            prepare_report(app.uCRC);
            QFAIL(report.toStdString().c_str());
        }
    }
}



void Test_Application::test_crc_index_cmd()
{

    //i = 1 //without custom CRC (custom CRC have index 0)
    for(size_t i = 1; i < QuCRC_t::CRC_List.size(); ++i)
    {
        info = QuCRC_t::CRC_List[i];

        std::vector<std::string> cmd = {
            "--crc_index"  , QString::number(i).toStdString(),
        };


        prepare_argv(cmd);

        app.processing_cmd(argc, argv);

        if( !(app.uCRC == info) )
        {
            prepare_report(app.uCRC);
            QFAIL(report.toStdString().c_str());
        }
    }
}



void Test_Application::test_crc_name_cmd()
{

    //i = 1 //without custom CRC (custom CRC have index 0)
    for(size_t i = 1; i < QuCRC_t::CRC_List.size(); ++i)
    {
        info = QuCRC_t::CRC_List[i];

        std::vector<std::string> cmd = {
            "--crc_name"  , info.name.toStdString(),
        };


        prepare_argv(cmd);

        app.processing_cmd(argc, argv);

        if( !(app.uCRC == info) )
        {
            prepare_report(app.uCRC);
            QFAIL(report.toStdString().c_str());
        }
    }
}



void Test_Application::prepare_report(QuCRC_t & uCRC)
{
    report = "For CRC: " + info.name + "\n cmd: ";


    for(int j = 1; j < argc; j++)
    {
        report += argv[j];
        report += "  ";
    }


    report += "\n but get:";
    report += " bits  "    + QString::number(uCRC.get_bits(),    10);
    report += " poly  "    + QString::number(uCRC.get_poly(),    16);
    report += " init  "    + QString::number(uCRC.get_init(),    16);
    report += " xor_out  " + QString::number(uCRC.get_xor_out(), 16);
    report += " ref_in  "  + QString::number(uCRC.get_ref_in(),  10);
    report += " ref_out  " + QString::number(uCRC.get_ref_out(), 10);
}



void Test_Application::prepare_argv(std::vector<std::string> &cmd)
{
    argc = cmd.size()+1;  //+1 see getopt_long function


    for(size_t j = 1; j <= cmd.size(); j++)
    {
        argv[j] = (char *)cmd[j-1].c_str();
    }


    // We use the processing_cmd function for processing the command line
    // For this we use the getopt_long function several times
    // to work properly, we must reset the optind
    optind = 0;
}





QTEST_APPLESS_MAIN(Test_Application)

#include "test_application.moc"
