#ifndef APPLICATION_H
#define APPLICATION_H


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <unistd.h>     // _exit

#include "qucrc_t.h"
#include "crc_calc_for_text.h"
#include "crc_calc_for_hex.h"





class Application : public QGuiApplication
{

    public:

        static Application& get_instance(int &argc, char **argv)
        {
            static Application* singleton = new Application(argc, argv);
            return *singleton;
        }



    private:

        Application(int &argc, char **argv);
        Q_DISABLE_COPY(Application)


        static void app_exit(int exitcode);
        static void attach_console(void);

        void processing_cmd(int argc, char *argv[]);

        static quint64 str_to_uint64(const char *val, int base=10);
        static bool    str_to_bool(const char *val);

        static void show_list(const QStringList & list);


        void set_encoding_index(int index);
        void set_encoding_name(const char *name);

        void set_crc_index(int index);
        void set_crc_name(const char *name);


        QuCRC_t uCRC;

        CRC_Calc_for_Text calc_text;
        CRC_Calc_for_Hex  calc_hex;


        QQmlApplicationEngine engine;  //must be last field (must be destroyed first
                                       //(it's GUI) only next destroyed data)



        #ifdef TEST
            static int app_exitcode;  //In TEST not exit from app, but save exitcode in this var


            friend class Test_Application;
        #endif
};





inline void Application::app_exit(int exitcode)
{
#ifdef TEST
    app_exitcode = exitcode;
#else
    _exit(exitcode);
#endif
}





#endif // APPLICATION_H
