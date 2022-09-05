#include "conf.h"

using namespace config;
#define DEFAULT_FPS 15

#define DEFAULT_MATRIX_COLOR  COLOR_GREEN
#define DEFAULT_MESSAGE_COLOR COLOR_WHITE

#define DEFAULT_MATRIX_LINE_LENGTH 12
#define DEFAULT_MIN_LINE_DEVIATION 3

#define DEFAULT_MATRIX_ALPHABET "abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()"



void config::print_help_msg(argh::parser &cmdl)
{
    printf("\nUsage: "); printf("%s", cmdl[0].c_str()); printf(" [options]\n");
    printf("\n");
    printf("This program creates a matrix effect right in your terminal,\n");
    printf("all you need is just run it and pass some options you want.\n");
    printf("But if you don't pass any options they will be the default.\n");
    printf("To exit the program simply press Ctrl+C or ESC.\n");
    printf("\n");

    printf("Available options:\n");
    printf("-h --help\t\tshow this help message\n");
    printf("\n-i --interactive\tmatrix falls only when you're typing. \n");
    printf("  so you can impress your friends with your hacker skills B)\n");
    printf("\n-c --color\t\tset matrix main color (default=green)\n");
    printf("  Available colors:\n");
    printf("  black, blue, cyan, green, magenta, red, white, yellow\n");
    printf("\n-r --rainbow\t\tturn on matrix disco mode. (ignores --color)\n");
    printf("\n-b --bold\t\tenable random bold symbol generation (default=disabled)\n");
    printf("\n-f --fps\t\tset matrix frames per second limit (default=15)\n");
    printf("\n-l --length\t\tset maximum length of a line tail (default=8)\n");
    printf("\n-d --deviation\t\tset minimum length of a line via deviation");
    printf(" (default=3)\n");
    printf("  this option calculates minimum length as a difference between\n");
    printf("  \"length\" value and \"deviation\" value, so for example:\n");
    printf("  [length=8 deviation=3 -> min_length = 8-3 = 5]\n");
    printf("\n-a --alphabet\t\tset matrix alphabet as a single string\n");
    printf("               \t\texample: -alph abc123\n");
    printf("\n-s --screensaver\texit the program if any key is pressed\n");
    printf("\n-m --message\t\tprint some message to the center of the screen\n");
    printf("\n-C --message-color\tchange color of the message\n");
    printf("  Available colors:\n");
    printf("  black, blue, cyan, green, magenta, red, white, yellow\n");
}



static const int UNKNOWN_COLOR = -1;
static int translate_ncurses_color(std::string color_name)
{
    std::transform(color_name.begin(),
                    color_name.end(),
                    color_name.begin(),
                    ::tolower);

    if (color_name == "white")
        return COLOR_WHITE;
    if (color_name == "black")
        return COLOR_BLACK;
    if (color_name == "blue")
        return COLOR_BLUE;
    if (color_name == "cyan")
        return COLOR_CYAN;
    if (color_name == "green")
        return COLOR_GREEN;
    if (color_name == "magenta")
        return COLOR_MAGENTA;
    if (color_name == "red")
        return COLOR_RED;
    if (color_name == "yellow")
        return COLOR_YELLOW;
    else
        return UNKNOWN_COLOR;
}



static void set_user_color(TM_CONFIG &conf, argh::parser &cmdl)
{
    // check for colors compatibility
    if (cmdl({"-n", "--no-color"}))
        conf.colored_terminal = false;
    else
        conf.colored_terminal = has_colors();

    // set user color
    if (conf.colored_terminal)
    {
        if (cmdl({"-c", "--color"}))
        {
            std::string user_color_name = cmdl({ "-c", "--color" }).str();
            int user_color = translate_ncurses_color(user_color_name);

            if (user_color == UNKNOWN_COLOR)
            {
                ncurses_cleanup();
                print_help_msg(cmdl);
                exit(int(ERRORS::ERR_COLOR_NAME));
            }
            else
                conf.main_color = user_color;
        }
        else
            conf.main_color = DEFAULT_MATRIX_COLOR;
    }
}



static void set_user_message_color(TM_CONFIG &conf, argh::parser &cmdl)
{
    if (cmdl({"-C", "--message-color"}))
    {
        std::string user_color_name = cmdl({"-C", "--message-color"}).str();
        int user_color = translate_ncurses_color(user_color_name);

        if (user_color == UNKNOWN_COLOR)
        {
                ncurses_cleanup();
                print_help_msg(cmdl);
                exit(int(ERRORS::ERR_COLOR_NAME));
        }
        else
            conf.message_color = user_color;
    }
    else
        conf.message_color = DEFAULT_MESSAGE_COLOR;
}



static void set_user_fps(TM_CONFIG &conf, argh::parser &cmdl)
{
    if (cmdl({"-f", "--fps"}))
    {
        int fps;
        std::string user_fps_value = cmdl({"-f", "--fps"}).str();

        try
        {
            fps = std::stoi(user_fps_value);
            if (fps <= 0)
                fps = DEFAULT_FPS;
            conf.fps = fps;
        }
        catch (...)
        {
            ncurses_cleanup();
            print_help_msg(cmdl);
            exit(int(ERRORS::ERR_INVALID_CMD_VALUE));
        }
    }
    else
        conf.fps = DEFAULT_FPS;
}



static void set_user_max_line_length(TM_CONFIG &conf, argh::parser &cmdl)
{
    if (cmdl({"-l", "--length"}))
    {
        int max_line_length;
        std::string user_max_line_length = cmdl({"-l", "--length"}).str();

        try
        {
            max_line_length = std::stoi(user_max_line_length);

            if (max_line_length < 0)
                max_line_length = DEFAULT_MATRIX_LINE_LENGTH;

            conf.max_line_length= max_line_length;
        }
        catch (...)
        {
            ncurses_cleanup();
            print_help_msg(cmdl);
            exit(int(ERRORS::ERR_INVALID_CMD_VALUE));
        }
    }
    else
        conf.max_line_length = DEFAULT_MATRIX_LINE_LENGTH;
}



static void set_user_min_line_deviation(TM_CONFIG &conf, argh::parser &cmdl)
{
    if (cmdl({"-d", "--deviation"}))
    {
        int min_line_length_deviation;
        std::string user_deviation = cmdl({"-d", "--deviation"}).str();

        try
        {
            min_line_length_deviation = std::stoi(user_deviation);

            if (min_line_length_deviation < 0)
                min_line_length_deviation = DEFAULT_MIN_LINE_DEVIATION;

            conf.min_line_length_deviation = min_line_length_deviation;
        }
        catch (...)
        {
            ncurses_cleanup();
            print_help_msg(cmdl);
            exit(int(ERRORS::ERR_INVALID_CMD_VALUE));
        }
    }
    else
        conf.min_line_length_deviation = DEFAULT_MIN_LINE_DEVIATION;
}



void set_user_alphabet(TM_CONFIG &conf, argh::parser &cmdl)
{
    if (cmdl({"-a", "--alphabet"}))
    {
        conf.alphabet = cmdl({"-a", "--alphabet"}).str();
        auto &alph = conf.alphabet;

        if (alph.empty())
        {
            alph = DEFAULT_MATRIX_ALPHABET;
            return;
        }

        // remove all duplicates
        std::sort(alph.begin(), alph.end());
        auto unique_it = std::unique(alph.begin(), alph.end());
        alph.erase(unique_it, alph.end());
    }
    else
        conf.alphabet = DEFAULT_MATRIX_ALPHABET;
}


void set_user_message(TM_CONFIG &conf, argh::parser &cmdl)
{
    if (cmdl({"-m", "--message"}))
    {
        conf.user_message = cmdl({"-m", "--message"}).str();
    }
    else
        conf.user_message = "";
}


TM_CONFIG config::get_config(int argc, char** argv)
{
    argh::parser cmdl{argc, argv};
    TM_CONFIG conf{};

    // setup
    cmdl.add_params({"-f", "--fps"});
    cmdl.add_params({"-c", "--color"});
    cmdl.add_params({"-l", "--length"});
    cmdl.add_params({"-d", "--deviation"});
    cmdl.add_params({"-a", "--alphabet"});
    cmdl.add_params({"-m", "--message"});
    cmdl.add_params({"-C", "--message-color"});

    cmdl.parse(argc, argv);

    if (cmdl[{"-h", "--help"}])
    {
        ncurses_cleanup();
        print_help_msg(cmdl);
        exit(0);
    }

    set_user_fps(conf, cmdl);
    set_user_color(conf, cmdl);
    set_user_max_line_length(conf, cmdl);
    set_user_min_line_deviation(conf, cmdl);
    set_user_alphabet(conf, cmdl);
    set_user_message(conf, cmdl);
    set_user_message_color(conf, cmdl);

    conf.interactive_mode       = cmdl[{"-i", "--interactive"}];
    conf.rainbow_mode           = cmdl[{"-r", "--rainbow"}];
    conf.bold_generation        = cmdl[{"-b", "--bold"}];
    conf.screensaver_mode       = cmdl[{"-s", "--screensaver"}];

    return conf;
}