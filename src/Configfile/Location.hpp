#ifndef LOCATION_HPP
#define LOCATION_HPP
#include "Configuration.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
class Configuration;

class Location {
    private:
    std::string                                                                 _limit_client_body_size;
    std::vector<std::string>                                                    _allow_methods;
    std::vector<std::string>                                                    _return;
    std::string                                                                 _root;
    std::string                                                                 _autoindex;
    std::string                                                                 _index;
    std::vector<std::string>                                                    _cgi_execute;
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
    std::vector<std::string>                                                    &getcgi_execute();
    std::vector<std::string>                                                    &getallow_methods();
    int                                                                         &getlocation_exist();
    std::string                                                                 &get_limit_client_body_size();
    //---->       Memeber Fuction      <---\\.

};
#endif
