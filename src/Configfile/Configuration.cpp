#include "Configuration.hpp"
#include "../Webserv.hpp"
Configuration::Configuration()
{
}

Configuration::~Configuration()
{

}

Configuration::Configuration(std::vector<std::string> &vect_conf)
{
    _config = vect_conf;
    handling_bracket();
    syntax_error();
    parsing_Config_file();
    init_my_config();
    config_valide();
}

void Configuration::config_valide()
{
    std::map<std::string, std::vector<std::string> >::iterator it = _config_variable.begin();
    while (it != _config_variable.end())
    {
        std::string str = it->first.substr(0, 6);
        it->second.pop_back();
        if (!it->first.compare("listen"))
        {
            if (it->second.size() != 1)
                error_conf();
            if(ft_isdigit( it->second[0]))
                error_conf();
            if (atoi(it->second[0].c_str())  <= 0 || atoi(it->second[0].c_str())  > 65535)
                error_conf();
        }
        else if (!str.compare("error_"))
        {
            if (it->second.size() != 1)
                error_conf();
            if (it->first.length() != 9)
                error_conf();
            if(ft_isdigit(it->first.substr(6, it->first.length())))
                error_conf();
        }
        else if (!it->first.compare("host"))
        {
            if (it->second.size() != 1)
                error_conf();
        }
        else if (!it->first.compare("root"))
        {
            if (it->second.size() != 1)
                error_conf();
        }
        else if (!it->first.compare("limit_client_body_size"))
        {
            if (it->second.size() != 1)
                error_conf();
            if(ft_isdigit(it->second[0]))
                error_conf();
        }
        else if (!it->first.compare("index"))
        {
            if (it->second.size() != 1)
                error_conf();
        }
        else
            error_conf();
        it++;
    }
    std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator it2 = _locations.begin();
    while (it2 != _locations.end())
    {
        std::map<std::string, std::vector<std::string> >::iterator it3 = it2->second.begin();
        if (!it2->first.compare("/cgi-bin"))
        {
            std::string str1;
            std::string str2;
            while (it3 != it2->second.end())
            {
                int check = parsingLocation(it3);
                if (!it3->first.compare("index"))
                {
                    if (it3->second.size() != 1)
                        error_conf();
                    int ind = it3->second[0].find(".");
                    str1 = it3->second[0].substr(ind, it3->second[0].length());
                    if (str1.compare(".py") && str1.compare(".php"))
                        error_conf();
                }
                else if (check == 1)
                    error_conf();
                else if (check == 2)
                {
                    if (!it3->first.compare("cgi_execute"))
                    {
                        str2 = it3->second[0];
                        if (it3->second.size() != 1)
                            error_conf();
                        if (it3->second[0].compare(".py") && it3->second[0].compare(".php"))
                            error_conf();
                        else
                            ;
                    }
                }
                it3++;
            }
            if (str2 != str1)
                error_conf();
        }
        else
        {
            while (it3 != it2->second.end())
            {
                int check = parsingLocation(it3);
                if (check == 1)
                    error_conf();
                else if (check == 2)
                    error_conf();
                it3++;
            }
        }
        it2++;
    }
}

std::vector<std::string> split_string(std::string str, char c)
{
    std::vector<std::string> vect;
    std::string mot;
    int start;
    size_t i;

    i = 0;

    while (i < str.size())
    {
        while (str[i] && str[i] == c)
            i++;
        start = i;
        while (str[i] && str[i] != c)
            i++;
        mot = str.substr(start, i - start);
        if (!mot.empty())
            vect.push_back(mot);
        i++;
    }
    return vect;
}

std::string parsing_url(std::string url)
{
    std::string new_url;
    std::vector<std::string> vect_str = split_string(url, '/');
    if (vect_str.empty())
        return "/";
    for (size_t i = 0; i < vect_str.size(); i++)
    {
        if (i == 0)
            new_url += "/";
        new_url += vect_str[i];
        if (!(i == vect_str.size() - 1))
            new_url += "/";
    }
    return new_url;
}

void Configuration::parsing_Config_file()
{
    size_t i = 2;
    while (i < _config.size() && _config[i].compare("location"))
    {
        std::vector<std::string> vectr;
        std::string word0;
        word0 = _config[i];
        i++;
        while (i < _config.size() && _config[i].compare(";") && _config[i].compare("location"))
        {
            vectr.push_back(_config[i]);
            i++;
            if (!_config[i].compare(";"))
                vectr.push_back(_config[i]);
        }
        if (vectr.empty())
            error_conf();
        if(_config_variable.count(word0))
            error_conf();
        _config_variable.insert(std::make_pair(word0, vectr));
        if (!_config[i].compare("location"))
            break;
        i++;
    }

    i++;
    while (i < _config.size())
    {
        std::string mot1 = _config[i];
        i += 2;
        std::map<std::string, std::vector<std::string> > location;
        while (i <_config.size() && _config[i].compare("}"))
        {
            std::string mot2 = _config[i];
            i++;
            std::vector<std::string> vraibl;
            while (i < _config.size() && _config[i].compare(";") && _config[i].compare("}"))
                vraibl.push_back(_config[i++]);
            if (vraibl.empty())
                error_conf();
            if(location.count(mot2))
                error_conf();
            location.insert(std::make_pair(mot2, vraibl));
            i++;
        }
        if (location.empty())
            error_conf();
        std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator itt = _locations.find(mot1);
        if (itt != _locations.end())
            error_conf();
        mot1 = parsing_url(mot1);
        if(_locations.count(mot1))
            error_conf();
        _locations.insert(std::make_pair(mot1, location));
        i++;
        i++;
    }
}

void Configuration::init_my_config()
{
    std::map<std::string, std::vector<std::string> >::iterator it = _config_variable.begin();
    while (it != _config_variable.end())
    {
        std::string str = it->first.substr(0, 6);
        if (!it->first.compare("listen"))
            _listen = atoi(it->second[0].c_str());
        else if (!it->first.compare("server_name"))
            _server_names = it->second;
        else if (!it->first.compare("host"))
            _host = it->second[0];
        else if (!it->first.compare("root"))
            _root = it->second[0];
        else if (!it->first.compare("limit_client_body_size"))
            _limit_client_body_size = it->second[0];
        else if (!it->first.compare("index"))
            _index = it->second[0];
        else if (!str.compare("error_"))
            _error.insert(std::make_pair(atoi(it->first.substr(6, 3).c_str()), it->second[0]));
        else
            error_conf();
        it++;
    }
}

std::map<std::string, std::vector<std::string> > &Configuration::getconfig_variable()
{
    return _config_variable;
}

std::map<std::string, std::map<std::string, std::vector<std::string> > > &Configuration::getlocations()
{
    return _locations;
}

int &Configuration::getlisten()
{
    return _listen;
}
std::string &Configuration::getlimit_client_body_size()
{
    return _limit_client_body_size;
}
std::string &Configuration::gethost()
{
    return _host;
}
std::string &Configuration::getroot()
{

    return _root;
}
std::string &Configuration::getindex()
{
    return _index;
}
std::vector<std::string> &Configuration::getcgi()
{
    return _cgi;
}
std::vector<std::string> &Configuration::getserver_names()
{
    return _server_names;
}
std::map<int , std::string> &Configuration::geterror()
{
    return _error;
}

void Configuration::setconfig_variable(std::map<std::string, std::vector<std::string> > &conf_v)
{
    _config_variable = conf_v;
}