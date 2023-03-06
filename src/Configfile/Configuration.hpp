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
    std::vector<std::string> config;

    int listen ;
    int limit_client_body_size;
    std::string host;
    std::string root;
    std::vector<std::string> index;
    std::vector<std::string> cgi;
    std::vector<std::string> server_names;

    std::vector<std::pair<std::string, std::vector<std::string> > > config_variable;

    std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::vector<std::string> > > > > locations;

public:
    Configuration(std::vector<std::string> &vect_conf);
    Configuration();
    void parsing_Config_file();

    ~Configuration();
    void init_my_config();
    void syntax_error();
    int handling_bracket();
    std::vector<std::pair<std::string, std::vector<std::string> > > getconfig_variable();
    std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::vector<std::string> > > > > getlocations();


    int getlisten() ;
    int getlimit_client_body_size();
    std::string gethost();
    std::string getroot();
    std::vector<std::string> getindex();
    std::vector<std::string> getcgi();
    std::vector<std::string> getserver_names();
};

class Location{
    private:
    int location_exist;
    std::vector<std::string> root;
    std::vector<std::string> autoindex;
    std::vector<std::string> allow_methods;
    std::vector<std::string> index;
    std::vector<std::string> cgi_path;
    std::vector<std::string> cgi_execute;
    std::vector<std::string> return_path;
    public :
    Location(Configuration &conf, std::string);
    std::vector<std::string> getroot();
    std::vector<std::string> getautoindex();
    std::vector<std::string> getallow_methods();
    std::vector<std::string> getindex();
    std::vector<std::string> getcgi_path();
    std::vector<std::string> getcgi_execute();
    std::vector<std::string> getreturn_path();
    int getlocation_exist();

};

void print_config(std::vector<std::pair<std::string, std::vector<std::string> > > config_variable, std::vector<std::pair<std::string, std::vector<std::pair<std::string, std::vector<std::string> > > > > locations);
void error_conf(int status);
#endif
