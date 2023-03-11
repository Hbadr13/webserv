#include "Configuration.hpp"
std::vector<std::string> search_in_location_vector(std::vector<std::pair<std::string, std::vector<std::string> > > &location, std::string varaible)
{
    int i = 0;
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
    int i = 0;
    while (i < location.size())
    {
        if (!location[i].first.compare(varaible))
            return location[i].second[0];
        i++;
    }
    return std::string();
}

Location::Location(Configuration &conf, std::string path)
{
    int i = 0;
    while (i < conf.getlocations().size())
    {
        if (!conf.getlocations()[i].first.compare(path))
        {
            std::vector<std::pair<std::string, std::vector<std::string> > > location = conf.getlocations()[i].second;
            for (int j = 0; j < location.size(); j++)
            {
                if (!location[j].first.compare("allow_methods"))
                    this->allow_methods = location[j].second;
                if (!location[j].first.compare("cgi_execute"))
                    this->cgi_execute = location[j].second;
                if (!location[j].first.compare("return_path"))
                    this->return_path = location[j].second[0];
                if (!location[j].first.compare("cgi_path"))
                    this->cgi_path = location[j].second[0];
                if (!location[j].first.compare("index"))
                    this->index = location[j].second[0];
                if (!location[j].first.compare("root"))
                    this->root = location[j].second[0];
            }
        }
        i++;
    }
}

std::string Location::getroot()
{
    return this->root;
}

std::string Location::getautoindex()
{
    return this->autoindex;
}

std::vector<std::string> Location::getallow_methods()
{
    return this->allow_methods;
}

std::string Location::getindex()
{
    return this->index;
}

std::string Location::getcgi_path()
{
    return this->cgi_path;
}
std::vector<std::string> Location::getcgi_execute()
{
    return this->cgi_execute;
}

std::string Location::getreturn_path()
{
    return this->return_path;
}

int Location::getlocation_exist()
{
    return this->location_exist;
}