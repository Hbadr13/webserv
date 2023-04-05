#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>

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

class Location {
    private:
    std::string                                                                 _limit_client_body_size;
    std::vector<std::string>                                                    _allow_methods;
    std::vector<std::string>                                                    _return;
    std::string                                                                 _root;
    std::string                                                                 _autoindex;
    std::string                                                                 _index;
    std::string                                                                 _cgi_execute;
    int                                                                         _location_exist;
    public :
    //---->  Construction & Destructor <---\\.
    Location(Configuration &conf, std::string);
    ~Location();
    Location();

    //---->      Getters & Setters     <---\\.
    std::string                                                                 &getroot();
    std::string                                                                 &getautoindex();
    std::string                                                                 &getindex();
    std::vector<std::string>                                                    &getreturn();
    std::string                                                                 &getcgi_execute();
    std::vector<std::string>                                                    &getallow_methods();
    int                                                                         &getlocation_exist();
    std::string                                                                 &get_limit_client_body_size();
    //---->       Memeber Fuction      <---\\.

};
int                                                                             parsingLocation(std::map<std::string, std::vector<std::string> >::iterator it3);
void                                                                            error_conf(int status);
std::vector<std::string>                                                        split_string(std::string str, char c);
std::string                                                                     parsing_url(std::string url);
int                                                                             ft_isdigit(std::string str);
#endif