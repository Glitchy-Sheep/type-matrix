#include "conf.h"

using namespace config;

void config::print_help_msg()
{
    return;
    // TODO - add help msg and print it with ncurses funcs
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
                print_help_msg();
                exit(int(ERRORS::ERR_COLOR_NAME));
            }
            else
                conf.main_color = user_color;
        }
    }
}



static void set_user_speed(TM_CONFIG &conf, argh::parser &cmdl)
{
    if (cmdl({"-s", "--speed"}))
    {
        int speed;
        std::string user_speed_value = cmdl({"-s", "--speed"}).str();

        try
        {
            speed = std::stoi(user_speed_value);
            conf.speed = speed;
        }
        catch (...)
        {
            print_help_msg();
            exit(int(ERRORS::ERR_INVALID_CMD_VALUE));
        }
    }

}



TM_CONFIG config::get_config(int argc, char** argv)
{
    argh::parser cmdl{argc, argv};
    TM_CONFIG conf{};

    // setup
    cmdl.add_params({"-s", "--speed"});
    cmdl.add_params({"-c", "--color"});

    cmdl.parse(argc, argv);

    set_user_color(conf, cmdl);
    set_user_speed(conf, cmdl);

    conf.rainbow_mode = cmdl[{"-r", "--rainbow"}];

    return conf;
}