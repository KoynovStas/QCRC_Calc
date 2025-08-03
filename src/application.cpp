#include "application.h"

#ifdef Q_OS_WIN
    #include <windows.h>  //need for support console (It's Windows baby)
#endif

#include <iostream>
#include <getopt.h>




#define STRINGIFY(x) #x
#define DEF_TO_STR(x) STRINGIFY(x)



#ifdef TEST
    int Application::app_exitcode;  //In TEST not exit from app, but save exitcode in this var
#endif




Application::Application(int &argc, char **argv) :
    QGuiApplication(argc, argv),

    //private
    calc_text(uCRC),
    calc_hex(uCRC),
    calc_file(uCRC)
{
    setApplicationDisplayName("CRC Calculator ver "
                              DEF_TO_STR(MAJOR_VERSION) "."
                              DEF_TO_STR(MINOR_VERSION));

#ifndef TEST
    attach_console();
    processing_cmd(argc, argv);

    // GUI
    engine.rootContext()->setContextProperty("uCRC", &uCRC);
    engine.rootContext()->setContextProperty("calc_text", &calc_text);
    engine.rootContext()->setContextProperty("calc_hex", &calc_hex);

    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
#endif
}



void Application::attach_console()
{
#ifdef Q_OS_WIN

    // attach the new console to this application's process
    AttachConsole(ATTACH_PARENT_PROCESS);

    // reopen the std I/O streams to redirect I/O to the new console
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
    freopen("CON", "r", stdin);

#endif
}



static const char *help_str =
        " ===============  Help  ===============\n"
        " Application:  CRC Calculator\n"
        " App version:  "  DEF_TO_STR(MAJOR_VERSION) "." DEF_TO_STR(MINOR_VERSION) "\n"
#ifdef  QT_DEBUG
        " Build  mode:  debug\n"
#else
        " Build  mode:  release\n"
#endif
        " Build  date:  " __DATE__ "\n"
        " Build  time:  " __TIME__ "\n\n"
        "Options:        Description:\n\n"
        " --bits         [value] Set Bits    (value 1..64)\n"
        " --poly         [value] Set Polynom (value in hex)\n"
        " --init         [value] Set Init    (value in hex)\n"
        " --xor_out      [value] Set XorOut  (value in hex)\n"
        " --ref_in       [value] Set RefIn   ({0|false} or {!=0|true})\n"
        " --ref_out      [value] Set RefOut  ({0|false} or {!=0|true})\n"
        " --crc_index    [value] Set CRC     (value is index see --list_crc)\n"
        " --crc_name     [value] Set CRC     (value is name see --list_crc)\n\n"
        " --revers_word  [value] Set revers word for HEX ({0|false} or {!=0|true})\n"
        " --revers_data  [value] Set revers data for HEX ({0|false} or {!=0|true})\n"
        " --hex_file     [value] Get CRC for HEX from file (value is path of file)\n"
        " --hex          [value] Get CRC for HEX (value in hex format)\n\n"
        " --BOM          [value] Set BOM for Text ({0|false} or {!=0|true})\n"
        " --end_line     [value] Set format End Line (value is index see --list_endl)\n"
        " --enc_index    [value] Set Encoding (value is index see --list_enc)\n"
        " --enc_name     [value] Set Encoding (value is name see --list_enc)\n"
        " --text_file    [value] Get CRC for Text from file (value is path of file)\n"
        " --text         [value] Get CRC for Text (value is text)\n\n"
        " --file         [value] Get CRC for File (value is path of file)\n\n"
        " --list_endl            Show List of End Line with indexes\n"
        " --list_enc             Show List of Encodings with indexes\n"
        " --list_crc             Show List of std CRC with indexes\n\n"
        " --version              Display version information\n"
        " --help                 Display this information\n\n";



// indexes for long_opt function
namespace LongOpts
{
    enum
    {
        version = 0,
        help,

        // Set CRC param
        bits,
        poly,
        init,
        xor_out,
        ref_in,
        ref_out,
        crc_index,
        crc_name,

        // CRC for Hex
        revers_word,
        revers_data,
        hex_file,
        hex,

        // CRC for Text
        BOM,
        end_line,
        enc_index,
        enc_name,
        text_file,
        text,

        // CRC for File
        file,

        // Common
        list_endl,
        list_enc,
        list_crc
    };
}



static const struct option long_opts[] =
{

    { "version",      no_argument,       NULL, LongOpts::version       },
    { "help",         no_argument,       NULL, LongOpts::help          },

    // Set CRC param
    { "bits",         required_argument, NULL, LongOpts::bits          },
    { "poly",         required_argument, NULL, LongOpts::poly          },
    { "init",         required_argument, NULL, LongOpts::init          },
    { "xor_out",      required_argument, NULL, LongOpts::xor_out       },
    { "ref_in",       required_argument, NULL, LongOpts::ref_in        },
    { "ref_out",      required_argument, NULL, LongOpts::ref_out       },
    { "crc_index",    required_argument, NULL, LongOpts::crc_index     },
    { "crc_name",     required_argument, NULL, LongOpts::crc_name      },

    // CRC for Hex
    { "revers_word",  required_argument, NULL, LongOpts::revers_word   },
    { "revers_data",  required_argument, NULL, LongOpts::revers_data   },
    { "hex_file",     required_argument, NULL, LongOpts::hex_file      },
    { "hex",          required_argument, NULL, LongOpts::hex           },

    // CRC for Text
    { "BOM",          required_argument, NULL, LongOpts::BOM           },
    { "end_line",     required_argument, NULL, LongOpts::end_line      },
    { "enc_index",    required_argument, NULL, LongOpts::enc_index     },
    { "enc_name",     required_argument, NULL, LongOpts::enc_name      },
    { "text_file",    required_argument, NULL, LongOpts::text_file     },
    { "text",         required_argument, NULL, LongOpts::text          },

    // CRC for File
    { "file",         required_argument, NULL, LongOpts::file          },

    // Common
    { "list_endl",    no_argument,       NULL, LongOpts::list_endl     },
    { "list_enc",     no_argument,       NULL, LongOpts::list_enc      },
    { "list_crc",     no_argument,       NULL, LongOpts::list_crc      },

    { NULL,           no_argument,       NULL,  0                      }
};



void Application::processing_cmd(int argc, char *argv[])
{
    int opt;

    while( (opt = getopt_long(argc, argv, "", long_opts, NULL)) != -1 )
    {
        switch( opt )
        {
            case LongOpts::version:
                    std::cout << "CRC Calculator version "
                                 DEF_TO_STR(MAJOR_VERSION) "."
                                 DEF_TO_STR(MINOR_VERSION) "\n";
                    app_exit(EXIT_SUCCESS);
                    break;


            case LongOpts::help:
                    std::cout << help_str;
                    app_exit(EXIT_SUCCESS);
                    break;


            // Set CRC param
            case LongOpts::bits:
                    if( uCRC.set_bits(str_to_uint64(optarg)) != 0 )
                    {
                        std::cout << "Cant set bits from val: " << optarg << "\n";
                        app_exit(EXIT_FAILURE);
                    }
                    break;


            case LongOpts::poly:
                    uCRC.set_poly(str_to_uint64(optarg, 16));
                    break;


            case LongOpts::init:
                    uCRC.set_init(str_to_uint64(optarg, 16));
                    break;


            case LongOpts::xor_out:
                    uCRC.set_xor_out(str_to_uint64(optarg, 16));
                    break;


            case LongOpts::ref_in:
                    uCRC.set_ref_in(str_to_bool(optarg));
                    break;


            case LongOpts::ref_out:
                    uCRC.set_ref_out(str_to_bool(optarg));
                    break;


            case LongOpts::crc_index:
                    set_crc_index(str_to_uint64(optarg));
                    break;


            case LongOpts::crc_name:
                    set_crc_name(optarg);
                    break;


            // CRC for Hex
            case LongOpts::revers_word:
                    calc_hex.set_revers_chunk(str_to_bool(optarg));
                    break;


            case LongOpts::revers_data:
                    calc_hex.set_revers_data(str_to_bool(optarg));
                    break;


            case LongOpts::hex_file:
                    check_and_print_res(calc_hex.get_crc_data_from_file(optarg), calc_hex);
                    break;


            case LongOpts::hex:
                    check_and_print_res(calc_hex.calculate(optarg, true), calc_hex);
                    break;


            // CRC for Text
            case LongOpts::BOM:
                    calc_text.set_BOM(str_to_bool(optarg));
                    break;


            case LongOpts::end_line:
                    if( calc_text.set_end_line_index(str_to_uint64(optarg)) != 0 )
                    {
                        std::cout << "Cant set end line index from val: " << optarg << "\n";
                        app_exit(EXIT_FAILURE);
                    }
                    break;


            case LongOpts::enc_index:
                    set_encoding_index(str_to_uint64(optarg));
                    break;


            case LongOpts::enc_name:
                    set_encoding_name(optarg);
                    break;


            case LongOpts::text_file:
                    check_and_print_res(calc_text.get_crc_data_from_file(optarg), calc_text);
                    break;


            case LongOpts::text:
                    check_and_print_res(calc_text.calculate(optarg, true), calc_text);
                    break;


            // CRC for File
            case LongOpts::file:
                    check_and_print_res(calc_file.calculate(optarg, true), calc_file);
                    break;


            // Common
            case LongOpts::list_endl:
                    show_list(calc_text.end_line_names());
                    app_exit(EXIT_SUCCESS);
                    break;


            case LongOpts::list_enc:
                    show_list(calc_text.encodings());
                    app_exit(EXIT_SUCCESS);
                    break;


            case LongOpts::list_crc:
                    show_list(uCRC.crc_names());
                    app_exit(EXIT_SUCCESS);
                    break;


            default:
                    // getopt_long function itself prints an error message
                    std::cout << "for more detail see help\n\n";
                    app_exit(EXIT_FAILURE);
                    break;
        }
    }
}



quint64 Application::str_to_uint64(const char *val, int base)
{
    bool ok;
    QString tmp(val);

    quint64 res = tmp.toULongLong(&ok, base);

    if(!ok)
    {
        std::cout << "Cant convert: " << val << " to uint64\n";
        app_exit(EXIT_FAILURE);
    }


    return res; //good job
}



bool Application::str_to_bool(const char *val)
{
    QString tmp(val);

    return (tmp.compare("true", Qt::CaseInsensitive) == 0) || (atoi(val) != 0);
}



void Application::show_list(const QStringList &list)
{
    std::cout << "Index:   Name:\n";

    for(int i = 0; i < list.size(); ++i)
        std::cout << i << "  " << list[i].toStdString() << "\n";
}



void Application::set_encoding_index(int index)
{
    if( calc_text.set_encoding_index(index) != 0 )
    {
        std::cout << "Cant set encoding\n";
        app_exit(EXIT_FAILURE);
    }
}



void Application::set_encoding_name(const char *name)
{
    int index = calc_text.encodings().indexOf(QRegExp(name, Qt::CaseInsensitive));
    set_encoding_index(index);
}



void Application::set_crc_index(int index)
{
    if( uCRC.set_index(index) != 0 )
    {
        std::cout << "Cant set CRC\n";
        app_exit(EXIT_FAILURE);
    }
}



void Application::set_crc_name(const char *name)
{
    int index = uCRC.crc_names().indexOf(QRegExp(".*" + QString(name) + ".*", Qt::CaseInsensitive));
    set_crc_index(index);
}



void Application::check_and_print_res(int res, Abstract_CRC_Calc & calc)
{
    if( res != 0 )
    {
        std::cout << "Cant get CRC error: "
                  << calc.get_str_error().toStdString() << "\n";
        app_exit(EXIT_FAILURE);
    }

    std::cout << calc.result.get_result_hex().toStdString()<< "\n";
    app_exit(EXIT_SUCCESS);
}
