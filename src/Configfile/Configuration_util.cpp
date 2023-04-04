#include "Configuration.hpp"
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

bool searchStr(std::map<std::string, std::vector<std::string> >::iterator it3) 
{
    int d = 0, p = 0, g = 0;
    for (size_t i = 0; i < it3->second.size(); i++)
    {
        if (!it3->second[i].compare("DELETE"))
            d++;
        else if (!it3->second[i].compare("POST"))
            p++;
        else if (!it3->second[i].compare("GET"))
            g++;
        else
            return (false);
    }
    if (d > 1 || p > 1 || g > 1)
        return (false);
    return true;
}

int ft_isdigit(std::string str)
{
    for (size_t i = 0; i < str.size(); i++)
    {
        if (!isdigit(str[i]))
            return (1);
    }
    return (0);
}

int parsingLocation(std::map<std::string, std::vector<std::string> >::iterator it3)
{
    if(!it3->first.compare("root"))
    {
        if(it3->second.size() != 1)
            return (1);
    }
    else if(!it3->first.compare("index"))
    {
        if(it3->second.size() != 1)
            return (1);
    }
    else if(!it3->first.compare("autoindex"))
    {
        if(it3->second.size() != 1)
            return (1);
        if (it3->second[0].compare("off") && it3->second[0].compare("on"))
            error_conf(303);
    }
    else if(!it3->first.compare("allow_methods"))
    {
        if (searchStr(it3) == false)
            error_conf(101);
    }       
    else if(!it3->first.compare("limit_client_body_size"))
    {
        if(it3->second.size() != 1)
            return (1);
        std::string listen = it3->second[0];
        for (size_t i = 0; i < listen.size(); i++)
        {
            if (!isdigit(listen[i]))
                error_conf(100);
        }
    }
    else
        return (2);
    return (0);
}

void error_conf(int status)
{
    std::cout<<"    [Example  About The Configuration File Valid]"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"server{"<<std::endl;
    std::cout<<"    root www;"<<std::endl;
    std::cout<<"    listen 9090;"<<std::endl;
    std::cout<<"    host localhost;"<<std::endl;
    std::cout<<"    index error.html;"<<std::endl;
    std::cout<<"    limit_client_body_size 500;"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"    location / {"<<std::endl;
    std::cout<<"        allow_methods  HEAD POST DELETE;"<<std::endl;
    std::cout<<"        root www;"<<std::endl;
    std::cout<<"        index index.html;"<<std::endl;
    std::cout<<"        autoindex off;"<<std::endl;
    std::cout<<"    }"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"    location /upload{"<<std::endl;
    std::cout<<"      index index.html;"<<std::endl;
    std::cout<<"    }"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"    location /cgi-bin {"<<std::endl;
    std::cout<<"        allow_methods  HEAD POST;"<<std::endl;
    std::cout<<"        root www/;"<<std::endl;
    std::cout<<"        autoindex off;"<<std::endl;
    std::cout<<"        index index.py index.php;"<<std::endl;
    std::cout<<"        cgi_execute .py .php;"<<std::endl;
    std::cout<<"        limit_client_body_size 500;"<<std::endl;
    std::cout<<"    }"<<std::endl;
    std::cout<<"}"<<std::endl;
    exit(status);
}

int Configuration::handling_bracket()
{
    int i = 0;

    std::vector<std::string> bracket;
    if(this->config.size() < 4)
            error_conf(-1);
    while (i < this->config.size())
    {
        if (!this->config[i].compare("{") || !this->config[i].compare("}"))
            bracket.push_back(this->config[i]);
        i++;
    }
    if(bracket.size() < 4)
        error_conf(10);
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