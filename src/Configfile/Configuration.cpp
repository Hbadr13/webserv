#include "Configuration.hpp"
#include "../webserv.hpp"
Configuration::Configuration()
{
}

Configuration::~Configuration()
{
}
Configuration::Configuration(std::vector<std::string> &vect_conf)
{    

    this->config = vect_conf;

    if (handling_bracket())
        error_conf(3);
    syntax_error();
    parsing_Config_file();
    init_my_config();
    config_valide();
}



void Configuration::config_valide()
{
    std::map<std::string, std::vector<std::string > >::iterator it = this->config_variable.begin();
    while (it != this->config_variable.end())
    {
        std::string str = it->first.substr(0, 6);
        it->second.pop_back();
        if(!it->first.compare("listen"))
        {
            if(it->second.size() != 1)
                error_conf(330);
            std::string listen = it->second[0];
            for (size_t i = 0; i < listen.size(); i++)
            {
                if (!isdigit(listen[i]))
                    error_conf(100);
            }
        }
        else if (!str.compare("error_"))
        {
            if (it->second.size() != 1)
                error_conf(303);
            std::string mote = it->first.substr(6, it->first.length());
            if (it->first.length() != 9)
                error_conf(103);
            for (size_t i = 0; i < mote.size(); i++)
            {
                if (!isdigit(mote[i]))
                    error_conf(100);
            }
        }
        else if(!it->first.compare("host"))
        {
            if(it->second.size() != 1)
                error_conf(332);
            else if (it->second[0].compare("localhost") && it->second[0].compare("127.0.0.1"))
                error_conf(101);
        }
        else if(!it->first.compare("root"))
        {
            if(it->second.size() != 1)
                error_conf(333);
        }
        else if(!it->first.compare("limit_client_body_size"))
        {
            if(it->second.size() != 1)
                error_conf(334);
            std::string listen = it->second[0];
            for (size_t i = 0; i < listen.size(); i++)
            {
                if (!isdigit(listen[i]))
                    error_conf(100);
            }
        }
        else if(!it->first.compare("index"))
        {
            if(it->second.size() != 1)
                error_conf(335);
        }
        else
            error_conf(336);
        it++;
    }  
    std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator it2 = this->locations.begin();
    while(it2 != this->locations.end())
    {
        std::map<std::string, std::vector<std::string> >::iterator it3 =  it2->second.begin();
        if(!it2->first.compare("/cgi-bin"))
        {
            while (it3 != it2->second.end())
            {
                int check = parsingLocation(it3);
                if (!it3->first.compare("index"))
                {
                    for (size_t i = 0; i < it3->second.size(); i++)
                    {
                        int ind = it3->second[i].find(".");
                        std::string str = it3->second[i].substr(ind, it3->second[i].length());
                        if (str.compare(".py") && str.compare(".php"))
                            error_conf(123);
                    }
                }
                else if (check == 1)
                    error_conf(337);
                else if (check == 2)
                {
                    if(!it3->first.compare("cgi_execute"))
                    {
                        if((it3->second[0].compare(".py") || it3->second[1].compare(".php")) 
                            && (it3->second[0].compare(".php") || it3->second[1].compare(".py")))
                            error_conf(337);
                        else
                            ;
                    }
                }
                it3++;
            }
        }
        else
        {
            while (it3 != it2->second.end())
            {
                int check = parsingLocation(it3);
                if (check == 1)
                    error_conf(337);
                else if (check == 2)
                    error_conf(337);
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
    int i;

    i = 0;

    while (i < str.size())
    {
        while (str[i] && str[i] == c)
            i++;
        start = i;
        while (str[i] && str[i] != c)
            i++;
        mot = str.substr(start, i - start);
        if(!mot.empty())
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
    for (int i = 0; i < vect_str.size(); i++)
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

    int i = 2;
    while (i < this->config.size() && this->config[i].compare("location"))
    {
        std::vector<std::string> vectr;
        std::string word0;
        word0 = this->config[i];
        i++;
        while (i < this->config.size() && this->config[i].compare(";") && this->config[i].compare("location"))
        {
            vectr.push_back(this->config[i]);
            i++;
            if (!this->config[i].compare(";"))
                vectr.push_back(this->config[i]);
        }
         if(vectr.empty())
            {
                std::cout<<"variable 5awi: "<<word0<<"\n\n";
                exit(2);
        }
        this->config_variable.insert(std::make_pair(word0, vectr));
        if (!this->config[i].compare("location"))
            break;
        i++;
    }
    i++;
    while (i < this->config.size() - 1)
    {
        std::string mot1 = this->config[i];
        i += 2;
        std::map<std::string, std::vector<std::string> > location;
        while (this->config[i].compare("}"))
        {
            std::string mot2 = this->config[i];
            i++;
            std::vector<std::string> vraibl;
            while (this->config[i].compare(";") && this->config[i].compare("}"))
                vraibl.push_back(this->config[i++]);
            if(vraibl.empty())
            {
                std::cout<<"variable 5awi 2\n\n";
                exit(2);
            }
            location.insert(std::make_pair(mot2, vraibl));
                i++;
        }
               if(location.empty())
            {
                std::cout<<"location 5awi:  3"<<mot1<<"\n\n";
                exit(2);
            }
        std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator itt = this->locations.find(mot1);
        if(itt != this->locations.end())
            error_conf(800);
        mot1 = parsing_url(mot1);
        std::cout<<mot1<<std::endl;
        this->locations.insert(std::make_pair(mot1, location));
        i++;
        i++;
    }
}

void  Configuration::init_my_config()
{
    std::map<std::string, std::vector<std::string> >::iterator it = this->config_variable.begin();
    while (it != this->config_variable.end())
    {
        std::string str = it->first.substr(0, 6);
        if(!it->first.compare("listen"))
            this->listen = atoi(it->second[0].c_str());
        else if(!it->first.compare("server_name"))
            this->server_names = it->second;
        else if(!it->first.compare("host"))
            this->host = it->second[0];
        else if(!it->first.compare("root"))
            this->root = it->second[0]; 
        else if(!it->first.compare("limit_client_body_size"))
            this->limit_client_body_size = it->second[0];
        else if(!it->first.compare("index"))
            this->index = it->second[0];
        else if (!str.compare("error_"))
            this->error.insert(std::make_pair(atoi(it->first.substr(6, 3).c_str()), it->second[0]));
        else
            error_conf(303);
        it++;
    }
    // for ( std::map<int, std::string> ::iterator it= error.begin(); it != error.end(); ++it) {
    //     std::cout <<"error = "<< it->first << ": " << it->second << std::endl;
    // }
}

std::map<std::string, std::vector<std::string> > Configuration::getconfig_variable()
{
    return this->config_variable;
}

std::map<std::string, std::map<std::string, std::vector<std::string> > > &Configuration::getlocations()
{
    return this->locations;
}

int Configuration::getlisten()
{
    return this->listen;
}
std::string Configuration::getlimit_client_body_size()
{
    return this->limit_client_body_size;
}
std::string Configuration::gethost()
{
    return this->host;
}
std::string Configuration::getroot()
{

    return this->root;
}
std::string Configuration::getindex()
{
    return this->index;
}
std::vector<std::string> Configuration::getcgi()
{
    return this->cgi;
}
std::vector<std::string> Configuration::getserver_names()
{
    return this->server_names;
}