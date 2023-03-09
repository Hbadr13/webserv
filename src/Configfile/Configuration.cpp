 
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
void Configuration::config_valide()
{
    int i = 0;
    while (i < this->config_variable.size())
    {
        this->config_variable[i].second.pop_back();
        if(!this->config_variable[i].first.compare("listen"))
        {
            if(this->config_variable[i].second.size() != 1)
                error_conf(330);
        }
        else if(!this->config_variable[i].first.compare("server_name"))
        {
            if(this->config_variable[i].second.size() != 1)
                error_conf(331);
        }
        else if(!this->config_variable[i].first.compare("host"))
        {
            if(this->config_variable[i].second.size() != 1)
                error_conf(332);
        }
        else if(!this->config_variable[i].first.compare("root"))
        {
            if(this->config_variable[i].second.size() != 1)
                error_conf(333);
        }
        else if(!this->config_variable[i].first.compare("limit_client_body_size"))
        {
            if(this->config_variable[i].second.size() != 1)
                error_conf(334);
        }
        else if(!this->config_variable[i].first.compare("index"))
        {
            if(this->config_variable[i].second.size() != 1)
                error_conf(335);
        }
        else
        {
            std::cout<<"error varaible11 "<<this->config_variable[i].first<<i<<":\n\n";
            exit(1);
        }
        i++;
    }  
    i = 0;
    while(i < this->locations.size())
    {
        int j = 0;
        while (j < this->locations[i].second.size())
        {
            if(!this->locations[i].second[j].first.compare("root"))
            {
                if(this->locations[i].second[j].second.size() != 1)
                    error_conf(222);
            }
            else if(!this->locations[i].second[j].first.compare("cgi_execute"))
            ;
            else if(!this->locations[i].second[j].first.compare("index"))
            {
                if(this->locations[i].second[j].second.size() != 1)
                    error_conf(222);
            }
            else if(!this->locations[i].second[j].first.compare("autoindex"))
            {
                if(this->locations[i].second[j].second.size() != 1)
                    error_conf(222);
            }
            else if(!this->locations[i].second[j].first.compare("allow_methods"))
            ;
            else if(!this->locations[i].second[j].first.compare("limit_client_body_size"))
            {
                if(this->locations[i].second[j].second.size() != 1)
                    error_conf(222);
            }
            else
            {
                std::cout<<"error varaible22 "<<this->locations[i].second[j].first<< j <<":\n\n";
                exit(1);
            }
            j++;
        }
        i++;
    }
    // exit(1);
}
Configuration::Configuration(std::vector<std::string> &vect_conf)
{
    this->config = vect_conf;
    if (handling_bracket())
        error_conf(3);
    // for(int i = 0; i < vect_conf.size(); i++)
        // std::cout<<"|"<<vect_conf[i]<<"|\n";
    // std::cout<<vect_conf.size()<<" ";
    syntax_error();
    parsing_Config_file();
    init_my_config();
    config_valide();
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
        this->config_variable.push_back(std::make_pair(word0, vectr));
        if (!this->config[i].compare("location"))
            break;
        i++;
    }
    i++;
    while (i < this->config.size() - 1)
    {
        std::string mot1 = this->config[i];
        i += 2;
        std::vector<std::pair<std::string, std::vector<std::string> > > location;
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
            location.push_back(std::make_pair(mot2, vraibl));
                i++;
        }
               if(location.empty())
            {
                std::cout<<"location 5awi:  3"<<mot1<<"\n\n";
                exit(2);
            }
        this->locations.push_back(std::make_pair(mot1, location));
        i++;
        i++;
    }
    //print_config(this->config_variable, this->locations);
}

void  Configuration::init_my_config()
{
    int i = 0;
    while (i < this->config_variable.size())
    {
        if(!this->config_variable[i].first.compare("listen"))
            this->listen = atoi(this->config_variable[i].second[0].c_str());
        else if(!this->config_variable[i].first.compare("server_name"))
            this->server_names = this->config_variable[i].second;
        else if(!this->config_variable[i].first.compare("host"))
            this->host = this->config_variable[i].second[0];
        else if(!this->config_variable[i].first.compare("root"))
            this->root = this->config_variable[i].second[0]; 
        else if(!this->config_variable[i].first.compare("limit_client_body_size"))
            this->limit_client_body_size = this->config_variable[i].second[0];
        else if(!this->config_variable[i].first.compare("index"))
            this->index = this->config_variable[i].second;
        i++;
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


std::vector<std::pair<std::string, std::vector<std::string> > > Configuration::getconfig_variable()
{
    return this->config_variable;
}

std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::vector<std::string> > > > > Configuration::getlocations()
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
