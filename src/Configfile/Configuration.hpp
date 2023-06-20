#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include "Location.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

class Location;
class Configuration
{
private:
    int                                                                         _listen ;
    std::string                                                                 _root;
    std::string                                                                 _host;
    std::string                                                                 _index;
    std::vector<std::string>                                                    _cgi;
    std::vector<std::string>                                                    _config;
    std::map<int, std::string>                                                  _error;
    std::string                                                                 _limit_client_body_size;
    std::vector<std::string>                                                    _server_names;
    std::map<std::string, std::string>                                          _test;
    std::map<std::string, std::vector<std::string> >                            _config_variable;
    std::map<std::string, std::map<std::string, std::vector<std::string> > >    _locations;
public:

    //---->  Construction & Destructor <---\\.
    Configuration(std::vector<std::string> &vect_conf);
    ~Configuration();
    Configuration();

    //---->       Memeber Fuction      <---\\.
    void                                                                        parsing_Config_file();
    void                                                                        init_my_config();
    void                                                                        syntax_error();
    int                                                                         handling_bracket();
    void                                                                        config_valide();

    //---->      Getters & Setters     <---\\.
    std::map<std::string, std::map<std::string, std::vector<std::string> > >    &getlocations();
    void setconfig_variable(std::map<std::string, std::vector<std::string> >    &conf_v);
    std::map<std::string, std::vector<std::string> >                            &getconfig_variable();
    std::map<int , std::string>                                                 &geterror();
    std::vector<std::string>                                                    &getserver_names();
    std::vector<std::string>                                                    &getcgi();
    std::string                                                                 &getlimit_client_body_size();
    std::string                                                                 &getindex();
    std::string                                                                 &gethost();
    std::string                                                                 &getroot();
    int                                                                         &getlisten() ;
};

int                                                                             parsingLocation(std::map<std::string, std::vector<std::string> >::iterator it3);
void                                                                            error_conf();
std::vector<std::string>                                                        split_string(std::string str, char c);
std::string                                                                     parsing_url(std::string url);
int                                                                             ft_isdigit(std::string str);
#endif