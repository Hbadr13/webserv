#include "Configuration.hpp"
std::vector<std::string> search_in_location_vector(std::vector<std::pair<std::string, std::vector<std::string> > > &location, std::string varaible)
{
    size_t i = 0;
    while (i < location.size())
    {
        if (!location[i].first.compare(varaible))
            return location[i].second;
        i++;
    }
    return std::vector<std::string>();
}

std::string search_in_location_string(std::vector<std::pair<std::string, std::vector<std::string> > > &location, std::string varaible)
{
    size_t i = 0;
    while (i < location.size())
    {
        if (!location[i].first.compare(varaible))
            return location[i].second[0];
        i++;
    }
    return std::string();
}
Location::Location()
{
 
}
Location::~Location()
{
    
}
Location::Location(Configuration &conf, std::string path)
{
    std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator it = conf.getlocations().begin();
    while (it != conf.getlocations().end())
    {
        if (!it->first.compare(path))
        {
            std::map<std::string, std::vector<std::string> >::iterator it2 = it->second.begin();
            while (it2 != it->second.end())
            {
                if (!it2->first.compare("allow_methods"))
                    _allow_methods = it2->second;
                if (!it2->first.compare("cgi_execute"))
                    _cgi_execute = it2->second;
                if (!it2->first.compare("return"))
                    _return = it2->second;
                if (!it2->first.compare("index"))
                    _index = it2->second[0];
                if (!it2->first.compare("root"))
                    _root = it2->second[0];
                if (!it2->first.compare("autoindex"))
                    _autoindex = it2->second[0];
                if (!it2->first.compare("limit_client_body_size"))
                    _limit_client_body_size = it2->second[0];
                it2++;
            }
        }
        it++;
    }
}

std::string &Location::getroot()
{
    return _root;
}

std::string &Location::getautoindex()
{
    return _autoindex;
}

std::vector<std::string> &Location::getallow_methods()
{
    return _allow_methods;
}

std::string &Location::getindex()
{
    return _index;
}

std::vector<std::string> &Location::getcgi_execute()
{
    return _cgi_execute;
}

std::vector<std::string> &Location::getreturn()
{
    return _return;
}

int &Location::getlocation_exist()
{
    return _location_exist;
}
std::string &Location::get_limit_client_body_size()
{
    return _limit_client_body_size;
}