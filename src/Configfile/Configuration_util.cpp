#include "Configuration.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//  _________   _____    ____  ____  _____     ______   _________   _____     ____    ____  _____  //
// |_   ___  | |_   _|  |_   ||_   \|_   _|  .' ___  | |  _   _  | |_   _|  .'    `. |_   \|_   _| //
//   | |_  \_|   | |      | |   |   \ | |   / .'   \_| |_/ | | \_|   | |   /  .--.  \  |   \ | |   //
//   |  _|       | '      ' |   | |\ \| |   | |            | |       | |   | |    | |  | |\ \| |   //
//  _| |_         \ `-----'/   _| |_\   |_  \ `.___.'\    _| |_     _| |_  \  `--'  / _| |_\   |_  //
// |_____|         `.____.'   |_____|\____|  `._____.'   |_____|   |_____|  `.____.' |_____|\____| //
/////////////////////////////////////////////////////////////////////////////////////////////////////

void print_config(std::vector<std::pair<std::string, std::vector<std::string> > > config_variable, std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::vector<std::string> > > > > locations)
{
    int i = 0;
    while (i < config_variable.size())
    {
        std::cout << config_variable[i].first << ":  ";
        for (int j = 0; j < config_variable[i].second.size(); j++)
            std::cout << config_variable[i].second[j] << " ";
        std::cout << "\n";
        i++;
    }
    i = 0;
    while (i < locations.size())
    {
        std::cout << locations[i].first << " \n[\n";
        std::vector<std::pair<std::string, std::vector<std::string> > >::iterator it;
        for (it = locations[i].second.begin(); it != locations[i].second.end(); it++)
        {
            std::cout << it->first << "-> ";
            for (int i = 0; i < it->second.size(); i++)
                std::cout << it->second[i] << " ";
            std::cout << "\n";
        }
        std::cout << "]\n------------>\n\n";
        i++;
    }
}


void error_conf(int status)
{
    std::cout << "error " << status << ": configiuration file : syntex error\n";
    exit(1);
}

int Configuration::handling_bracket()
{
    int i = -1;
    std::vector<std::string> bracket;
    while (++i < this->config.size())
        if (!this->config[i].compare("{") || !this->config[i].compare("}"))
            bracket.push_back(this->config[i]);
    if (bracket[0].compare("{") || bracket[1].compare("{"))
        error_conf(4);
    if (bracket[bracket.size() - 1].compare("}") || !this->config[bracket.size() - 2].compare("}"))
        error_conf(4);
    i = 1;
    while (i < bracket.size() - 1)
    {
        if (!bracket[i].compare("{") && !bracket[i + 1].compare("{"))
            error_conf(4);
        if (!bracket[i].compare("}") && !this->config[i + 1].compare("}"))
            error_conf(4);
        i++;
    }
    return 0;
}

void Configuration::syntax_error()
{
    int i = 0;
    int flag = 1;

    if (this->config[0].compare("server"))
        error_conf(61);
    if (this->config[1].compare("{"))
        error_conf(62);
    if (this->config[this->config.size() - 1].compare("}"))
        error_conf(63);
    if (this->config[this->config.size() - 1].compare("}"))
        error_conf(64);
    while (i < this->config.size() - 1)
    {
        if (!this->config[i].compare("}") && this->config[i - 1].compare(";"))
            error_conf(65);
        if (flag == 1 && !this->config[i].compare("location"))
        {
            if (this->config[i - 1].compare(";") || !this->config[i + 1].compare("{") || this->config[i + 2].compare("{"))
                error_conf(66);
            flag = 0;
        }
        else if (flag == 0 && !this->config[i].compare("location"))
        {
            if (this->config[i - 1].compare("}") || !this->config[i + 1].compare("{") || this->config[i + 2].compare("{"))
                error_conf(6);
        }
        i++;
    }
}