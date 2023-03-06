#include "Configuration.hpp"

std::vector<std::string> search_in_location(std::vector<std::pair<std::string, std::vector<std::string> > > &location, std::string varaible)
{
    int i = 0;
    while (i < location.size())
    {
        if(!location[i].first.compare(varaible))
            return location[i].second;
        i++;
    }
    return std::vector<std::string>();
}

Location::Location(Configuration &conf, std::string path)
{
    int i = 0;
    while (i < conf.getlocations().size())
    {
        if(!conf.getlocations()[i].first.compare(path))
        {
            this->allow_methods = search_in_location(conf.getlocations()[i].second, "allow_methods");
            this->cgi_execute = search_in_location(conf.getlocations()[i].second, "cgi_execute");
            this->return_path = search_in_location(conf.getlocations()[i].second, "return_path");
            this->autoindex = search_in_location(conf.getlocations()[i].second, "autoindex");
            this->cgi_path = search_in_location(conf.getlocations()[i].second, "cgi_path");
            this->index = search_in_location(conf.getlocations()[i].second, "index");
            this->root = search_in_location(conf.getlocations()[i].second, "root");
            std::cout<<"--------------------))))))))))))))))"<<this->autoindex[0];
        }
        i++;
    }
    

}

std::vector<std::string> Location::getroot()
{
    return this->root;
}

std::vector<std::string> Location::getautoindex()
{
    return this->autoindex;
}

std::vector<std::string> Location::getallow_methods()
{
    return this->allow_methods;
}

std::vector<std::string> Location::getindex()
{
    return this->index;
}

std::vector<std::string> Location::getcgi_path()
{
    return this->cgi_path;
}
std::vector<std::string> Location::getcgi_execute()
{
    return this->cgi_execute;
}
std::vector<std::string> Location::getreturn_path()
{
    return this->return_path;
}

int Location::getlocation_exist()
{
    return this->location_exist;
}