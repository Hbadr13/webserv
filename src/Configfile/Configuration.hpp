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
    std::string root;
    std::string host;
    std::vector<std::string> cgi;
    std::vector<std::string> index;
    std::string limit_client_body_size;
    std::vector<std::string> server_names;
    std::map<std::string, std::map<std::string, std::vector<std::string> > > locations;
    std::map<std::string, std::string> test;
public:
    std::map<std::string ,std::string> gettest()
    {
        return this->test;
    }
    std::map<std::string, std::vector<std::string> > config_variable;
    Configuration(std::vector<std::string> &vect_conf);
    Configuration();
    void parsing_Config_file();

    ~Configuration();
    void init_my_config();
    void syntax_error();
    int handling_bracket();
    void config_valide();
    std::map<std::string, std::vector<std::string> >  getconfig_variable();
    void setconfig_variable(std::map<std::string, std::vector<std::string> > &conf_v)
    {
        this->config_variable = conf_v;
    }
    std::map<std::string, std::map<std::string, std::vector<std::string> > > &getlocations();


    int getlisten() ;
    std::string getlimit_client_body_size();
    std::string gethost();
    std::string getroot();
    std::vector<std::string> getindex();
    std::vector<std::string> getcgi();
    std::vector<std::string> getserver_names();
};

class Location{
    private:
    int location_exist;
    std::string root;
    std::string autoindex;
    std::string index;
    std::string cgi_path;
    std::string return_path;
    std::vector<std::string> cgi_execute;
    std::vector<std::string> allow_methods;
    public :
    Location()
    {

    }
    Location(Configuration &conf, std::string);
    std::string getroot();
    std::string getautoindex();
    std::string getindex();
    std::string getcgi_path();
    std::string getreturn_path();
    std::vector<std::string> getcgi_execute();
    std::vector<std::string> getallow_methods();
    int getlocation_exist();

};

void print_config(std::map<std::string, std::vector<std::string> > config_variable, std::map<std::string, std::map<std::string, std::vector<std::string> > > locations);
void error_conf(int status);
std::vector<std::string> split_string(std::string str, char c);
std::string parsing_url(std::string url);
#endif
