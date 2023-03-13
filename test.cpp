#include <netdb.h>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <fcntl.h>
#include <iostream>
#include <iostream>
#include <sys/wait.h>

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
        if (!mot.empty())
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
int main(int ac, char **av)
{
    std::map<std::string, std::string> conf;
    conf.insert(std::make_pair("/", "data1"));
    conf.insert(std::make_pair("/home", "date2"));
    conf.insert(std::make_pair("/home/code/test", "date3"));
    std::string url = (std::string)av[1];

    url = parsing_url(url);
    std::vector<std::string> vect_str = split_string(url, '/');
    std::string url_check;
    int len = vect_str.size();

    while (1)
    {
        url_check = "/";
        int i = 0;
        while (i < len)
        {
            url_check += vect_str[i];
            if (i != len - 1)
                url_check += "/";
            i++;
        }
        len--;
        std::map<std::string, std::string>::iterator it = conf.begin();
        while (it != conf.end())
        {
            if (!it->first.compare(url_check))
            {
                std::cout << it->second << std::endl;
                return 1;
            }
            it++;
        }
        if (!url_check.compare("/"))
            break;
    }
    return 1;
}