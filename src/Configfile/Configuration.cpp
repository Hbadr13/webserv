 
#include "Configuration.hpp"
#include "../webserv.hpp"




////////////////////////////////////////////////////////////////////////////////////////// ////////////////////////////////////////////////////
//     ______      ____    _____  _____    _______   _________   _______    _____    ____     ______   _________      ____     _______      //
//   .' ___  |   .'    `. |__   \|_   _   /  ___  | |  _   _  | |_   __ \  |_   _|  |_   |  .' ___  | |  _   _  |   .'    `.  |_   __ \     //
//  / .'   \_|  /  .--.  \   |   \ | |   |  (__ \_| |_/ | | \_|   | |__) |   | |      | |  / .'   \_| |_/ | | \_|  /  .--.  \   | |__) |    //
//  | |         | |    | |   | |\ \| |    '.___`-.      | |       |  __ /    | '      ' |  | |            | |      | |    | |   |  __ /     //
//  \ `.___.'\  \  `--'  / __| |_\   |_  |`\____) |    _| |_     _| |  \ \    \ `-----'/   \ `.___.'\    _| |_     \  `--'  /  _| |  \ \_   //
//   `._____.'   `.____.' |______|\____| |_______.'   |_____|   |____| |__|    `.____.'     `._____.'   |_____|     `.____.'  |____| |___|  //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Configuration::Configuration()
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
        it->second.pop_back();
        if(!it->first.compare("listen"))
        {
            if(it->second.size() != 1)
                error_conf(330);
        }
        else if(!it->first.compare("server_name"))
        {
            if(it->second.size() != 1)
                error_conf(331);
        }
        else if(!it->first.compare("host"))
        {
            if(it->second.size() != 1)
                error_conf(332);
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
        }
        else if(!it->first.compare("index"))
        {
            if(it->second.size() != 1)
                error_conf(335);
        }
        else
        {
            std::cout<<"error varaible11 "<<it->first<<":\n\n";
            exit(1);
        }
        it++;
    }  
    std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator it2 = this->locations.begin();
    while(it2 != this->locations.end())
    {
        std::map<std::string, std::vector<std::string> >::iterator it3 =  it2->second.begin();
        while (it3 != it2->second.end())
        {
            if(!it3->first.compare("root"))
            {
                if(it3->second.size() != 1)
                    error_conf(222);
            }
            else if(!it3->first.compare("cgi_execute"))
            ;
            else if(!it3->first.compare("index"))
            {
                if(it3->second.size() != 1)
                    error_conf(222);
            }
            else if(!it3->first.compare("autoindex"))
            {
                if(it3->second.size() != 1)
                    error_conf(222);
            }
            else if(!it3->first.compare("allow_methods"))
            ;
            else if(!it3->first.compare("limit_client_body_size"))
            {
                if(it3->second.size() != 1)
                    error_conf(222);
            }
            else
            {
                std::cout<<"error varaible22 "<<it3->first <<":\n\n";
                exit(1);
            }
            it3++;
        }
        it2++;
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ________    _________     _______   _________   _______     _____    ____      ______   _________     ____     _______     //
// |_   ___ `. |_   ___  |   /  ___  | |  _   _  | |_   __ \   |_   _|  |_   |   .' ___  | |  _   _  |  .'    `.  |_   __ \    //
//   | |   `. \  | |_  \_|  |  (__ \_| |_/ | | \_|   | |__) |    | |      | |   / .'   \_| |_/ | | \_| /  .--.  \   | |__) |   //
//   | |    | |  |  _|  _    '.___`-.      | |       |  __ /     | '      ' |   | |            | |     | |    | |   |  __ /    //
//  _| |___.' / _| |___/ |  |`\____) |    _| |_     _| |  \ \_    \ `-----'/    \ `.___.'\    _| |_    \  `--'  /  _| |  \ \_  //
// |________.' |_________|  |_______.'   |_____|   |____| |___|    `.____.'      `._____.'   |_____|    `.____.'  |____| |___| //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Configuration::~Configuration()
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  ____    ___  _________  ____    ___   ______     _________   _______        _________   _____    ____   ____  _____     ______   _________   _____     ____   _____  _____   //
// |_   \  /  _||_   ___  | _   \  /     |_   _ \   |_   ___  | |_   __ \      |_   ___  | |_   _|  |_   | |_   \|_   _|  .' ___  | |  _   _  | |_   _|  .'    `. |_   \|_   _|  //
//   |   \/   |   | |_  \_|  |   \/   |    | |_) |    | |_  \_|   | |__) |       | |_  \_|   | |      | |    |   \ | |   / .'   \_| |_/ | | \_|   | |   /  .--.  \  |   \ | |    //
//   | |\  /| |   |  _|  _   | |\  /| |    |  __'.    |  _|  _    |  __ /        |  _|       | '      ' |    | |\ \| |   | |            | |       | |   | |    | |  | |\ \| |    //
//  _| |_\/_| |  _| |___/ | _| |_\/_| |_  _| |__)|   _| |___/ |  _| |  \ \      _| |_         \ `-----'/    _| |_\   |_  \ `.___.'\    _| |_     _| |_  \  `--'  / _| |_\   |_   //
// |_____||____||_________| _____||_____ |_______/  |_________| |____| |__|    |_____|         `.____.'    |_____|\____|  `._____.'   |_____|   |_____|  `.____.' |_____|\____|  //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
    //print_config(this->config_variable, this->locations);
}

void  Configuration::init_my_config()
{


    std::map<std::string, std::vector<std::string> >::iterator it = this->config_variable.begin();
    while (it != this->config_variable.end())
    {
        if(!it->first.compare("listen"))
            this->listen = atoi(it->second[0].c_str());
        else if(!it->first.compare("server_name"))
            this->server_names = it->second;
        else if(!it->first.compare("host"))
            this->host = it->second[0];
        else if(!it->first.compare("root"))
            this->root = "it->second[0]"; 
        else if(!it->first.compare("limit_client_body_size"))
            this->limit_client_body_size = it->second[0];
        else if(!it->first.compare("index"))
            this->index = it->second;
        it++;
    }
}

///////////////////////////////////////////////////////////////////////////////////////
//    ______    _________   _________               _______   _________   _________  //
//  .' ___  |  |_   ___  | |  _   _  |             /  ___  | |_   ___  | |  _   _  | //
// / .'   \_|    | |_  \_| |_/ | | \_|  ________  |  (__ \_|   | |_  \_| |_/ | | \_| //
// | |    ____   |  _|  _      | |     |________|  '.___`-.    |  _|  _      | |     //
// \ `.___]  _/ _| |___/ |    _| |_               |`\____) |  _| |___/ |    _| |_    //
//  `._____.'  |_________|   |_____|              |_______.' |_________|   |_____|   //
///////////////////////////////////////////////////////////////////////////////////////  


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
std::vector<std::string> Configuration::getindex()
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
