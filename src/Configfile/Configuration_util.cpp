#include "Configuration.hpp"

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
            error_conf();
    }
    else if(!it3->first.compare("allow_methods"))
    {
        if (searchStr(it3) == false)
            error_conf();
    }
    else if (!it3->first.compare("return"))
    {
        if (ft_isdigit(it3->second[0]) == 1)
            error_conf();
        int ind = atoi(it3->second[0].c_str());
        if (ind < 0 || ind > 999)
            error_conf ();
    }       
    else if(!it3->first.compare("limit_client_body_size"))
    {
        if(it3->second.size() != 1)
            return (1);
        std::string listen = it3->second[0];
        for (size_t i = 0; i < listen.size(); i++)
        {
            if (!isdigit(listen[i]))
                error_conf();
        }
    }
    else
        return (2);
    return (0);
}

void error_conf()
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
    std::cout<<"        allow_methods  GET POST;"<<std::endl;
    std::cout<<"        root www;"<<std::endl;
    std::cout<<"        index index.html;"<<std::endl;
    std::cout<<"        autoindex off;"<<std::endl;
    std::cout<<"    }"<<std::endl;
    std::cout<<""<<std::endl;
    std::cout<<"    location /cgi-bin {"<<std::endl;
    std::cout<<"        allow_methods  GET POST;"<<std::endl;
    std::cout<<"        root www/;"<<std::endl;
    std::cout<<"        autoindex off;"<<std::endl;
    std::cout<<"        index index.py;"<<std::endl;
    std::cout<<"        cgi_execute .py;"<<std::endl;
    std::cout<<"        limit_client_body_size 500;"<<std::endl;
    std::cout<<"    }"<<std::endl;
    std::cout<<"}"<<std::endl;
    exit(1);
}

int Configuration::handling_bracket()
{
    size_t i = 0;

    std::vector<std::string> bracket;
    if(_config.size() < 4)
            error_conf();
    while (i < _config.size())
    {
        if (!_config[i].compare("{") || !_config[i].compare("}"))
            bracket.push_back(_config[i]);
        i++;
    }
    if(bracket.size() < 4)
        error_conf();
    if (bracket[0].compare("{") || bracket[1].compare("{"))
        error_conf();
    if (bracket[bracket.size() - 1].compare("}") || !_config[bracket.size() - 2].compare("}"))
        error_conf();
    i = 1;
    while (i < bracket.size() - 1)
    {
        if (!bracket[i].compare("{") && !bracket[i + 1].compare("{"))
            error_conf();
        if (!bracket[i].compare("}") && !_config[i + 1].compare("}"))
            error_conf();
        i++;
    }
    return 0;
}

void Configuration::syntax_error()
{
    size_t i = 0;
    int flag = 1;

    if (_config[0].compare("server"))
        error_conf();
    if (_config[1].compare("{"))
        error_conf();
    if (_config[_config.size() - 1].compare("}"))
        error_conf();
    if (_config[_config.size() - 1].compare("}"))
        error_conf();
    while (i < _config.size() - 1)
    {
        if (!_config[i].compare("}") && _config[i - 1].compare(";"))
            error_conf();
        if (flag == 1 && !_config[i].compare("location"))
        {
            if (_config[i - 1].compare(";") || !_config[i + 1].compare("{") || _config[i + 2].compare("{"))
                error_conf();
            flag = 0;
        }
        else if (flag == 0 && !_config[i].compare("location"))
        {
            if (_config[i - 1].compare("}") || !_config[i + 1].compare("{") || _config[i + 2].compare("{"))
                error_conf();
        }
        i++;
    }
}
std::string cleaning_input(std::string str)
{
    std::string dst;
    int start;
    int i = 0;
    while (str[i])
    {
        start = i;
        while (str[i] && str[i] != ';' && str[i] != '{' && str[i] != '}')
            i++;
        dst += str.substr(start, i - start);
        dst += " ";
        dst += str[i];
        dst += " ";
        if (!str[i])
            break;
        i++;
    }
    return dst;
}