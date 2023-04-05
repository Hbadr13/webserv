#include "Prasing_Request.hpp"

#include <bits/stdc++.h>

Prasing_Request::Prasing_Request()
{

}
Prasing_Request::~Prasing_Request()
{
    
}
int Prasing_Request::check_first_line(std::string first_line)
{
    this->methode = strtok((char *)first_line.c_str(), " ");
    if (this->methode != "GET" && this->methode != "POST" && this->methode != "DELETE")
    {
        std ::cout << "405 Method Not Allowed" << std::endl;
        status = 405;
        return (0);
    }
    char *urlll = strtok(NULL, " ");
    for (size_t i = 0; i < strlen(urlll); i++)
        if (urlll[i] != '?')
            this->url += urlll[i];
    std::string all_url = std::string(urlll);
    if (all_url.find('?') != std::string::npos)
        this->url = (all_url).substr(0, all_url.find('?'));
    else
        this->url = all_url;
    if (urlll[0] != '/')
    {
        std ::cout << "400 Bad Request" << std::endl;
        status = 400;
        return (0);
    }
    std ::string htb = strtok(NULL, " ");
    if (htb != "HTTP/1.1")
    {
        std::cout << "505 HTTP Version Not Supported" << std::endl;
        status = 505;
        return (0);
    }
    if (strchr(all_url.c_str(), '?'))
    {
        strtok((char *)all_url.c_str(), "?");
        char *str = strtok(NULL, "?");
        if (str)
            this->budy_url = str;
    }
    all_url.clear();
    return (1);
}

std ::vector<std ::string> split(std::string str, std::string delimiter)
{
    std ::vector<std ::string> v;
    if (!str.empty())
    {
        int start = 0;
        do
        {
            size_t idx = str.find(delimiter, start);
            if (idx == std ::string::npos)
            {
                break;
            }

            int length = idx - start;
            v.push_back(str.substr(start, length));
            start += (length + delimiter.size());
        } while (true);
        v.push_back(str.substr(start));
    }
    return v;
}

void Prasing_Request::prasing_headr(std ::string headrs)
{
    std ::vector<std ::string> res = split(headrs, "\r\n");
    for (size_t i = 0; i < res.size(); i++)
    {
        std ::string key = res[i].substr(0, res[i].find(":"));
        std ::string value = res[i].substr(res[i].find(" ") + 1);
        mymap.insert(std ::pair<std ::string, std::string>(key, value));
    }
    if (status == 200)
    {
        if (this->methode == "POST" && mymap["Content-Type"].empty())
        {
            std ::cout << "error on Content-Type !!!" << std::endl;
            status = 400;
            return;
        }
        if (mymap["Transfer-Encoding"] != "chunked")
        {
            if (this->methode == "POST" && (mymap["Content-Length"].empty() || atoi(mymap["Content-Length"].c_str()) < 0))
            {
                std ::cout << "error on Content-Length !!!" << std::endl;
                status = 400;
                return;
            }
        }
        if (mymap["Host"].empty())
        {
            std ::cout << "error om HOST !!" << std ::endl;
            status = 400;
            return;
        }
        if (atoi(mymap["Content-Length"].c_str()) > _limit_pody)
        {
            std ::cout << "eroore on size Content-Length " << std::endl;
            status = 400;
            return;
        }
    }
}
std ::string ft_chanked(std ::string body)
{
    size_t i = 0;
    int tr = 0;
    std ::string chunked;
    while (i < body.length())
    {
        std ::string hex;
        if (body[i] == '\r' && body[i + 1] == '\n')
            i += 2;
        while (body[i] != '\r' && body[i + 1] != '\n')
        {
            hex += body[i];
            i++;
        }
        tr = (int)strtol(hex.c_str(), NULL, 16);
        i += 2;
        while (tr > 0)
        {
            chunked += body[i];
            tr--;
            i++;
        }
    }
    return chunked;
}

std::pair<Location, std::string> find_location(std::string url, Configuration conf_serv)
{
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
        std::map<std::string, std::map<std::string, std::vector<std::string> > >::iterator it = conf_serv.getlocations().begin();
        while (it != conf_serv.getlocations().end())
        {
            if (!it->first.compare(url_check))
            {
                Location location(conf_serv, it->first);
                return std::pair<Location, std::string>(location, it->first);
            }
            it++;
        }
        if (!url_check.compare("/"))
            break;
    }
    return std::pair<Location, std::string>(Location(), std::string());
}

Prasing_Request::Prasing_Request(std::string hedr , Configuration &conf_serv)
{
    if (!hedr.at(0))
        return;
    this->status = 200;
    std ::string first;
    std ::string hdr;
    std ::string body;
    std::string limet;
    size_t i = 0;
    while (i < hedr.length())
    {
        if (hedr.at(i) == '\r' || hedr.at(i) == '\n')
            break;
        i++;
    }

    first = hedr.substr(0, i);
    hdr = hedr.substr(0, hedr.find("\r\n\r\n"));
    body = hedr.substr(hedr.find("\r\n\r\n"));
    std ::string chunked;
    if (!check_first_line(first))
        return;
    std::pair<Location, std::string> location_and_url = find_location(this->url, conf_serv);
    limet = conf_serv.getlimit_client_body_size();
    if(!location_and_url.first.get_limit_client_body_size().empty())
        limet = location_and_url.first.get_limit_client_body_size();
    if(!limet.empty())
        _limit_pody = atoi(limet.c_str());
    else
        _limit_pody = 999999999;
    prasing_headr(hdr);
    if (this->status != 200)
        return;
    if (get_method() == "POST")
    {
        if (mymap["Transfer-Encoding"] == "chunked")
            body = ft_chanked(body);
        std ::string finish_body = hdr + body;

        prasing_body(finish_body, body);
        finish_body.clear();
    }
    hdr.clear();
    first.clear();
    body.clear();
}

void Prasing_Request ::prasing_body(std ::string body1, std::string body2)
{
    std::string nb;
    std::string body;
    int i = 0;
    std::vector<std::string> one_body;
    nb = "--";
    int index = body1.find("boundary=");
    if (index == -1)
        return;
    else
    {
        index += 9;
        for (; body1[index] != '\r'; index++)
            nb.push_back(body1[index]);
    }

    int index2 = 0;
    int fin = 0;
    int rq = 0;
    for (; index2 != -1; i++)
    {

        index2 = body2.find(nb, fin);
        fin = body2.find(nb, index2 + 1);
        if (index2 == -1 || fin == -1)
            return;
        if (index != -1 && fin != -1)
        {
            one_body.push_back(body2.substr(index2, fin - index2));
            if (body2[fin + nb.size() + 1] == '-' && body2[fin + nb.size()] == '-')
                break;
        }
    }

    if (body2.size() > 4)
    {

        while (rq <= i)
        {
            if ((one_body[rq].find("filename=") != std::string::npos))
            {
                std::string fil = "filename=";
                int first = one_body[rq].find(fil) + fil.length() + 1;
                int finish = one_body[rq].find("\"", first);
                std::string filename;
                for (int j = first; j < finish; j++)
                    filename += one_body[rq][j];
                if (filename.empty())
                {
                    rq++;
                    continue;
                }
                std ::string str = one_body[rq].substr(one_body[rq].find("\r\n\r\n") + 4);
                std ::string filee = "html/www/upload/" + filename;
                if (!filename.empty())
                {
                    std ::ofstream MyFile(filee);
                    MyFile << str;
                    MyFile.close();
                }
            }
            rq++;
        }
    }
}

std ::string Prasing_Request::get_url()
{
    return this->url;
}
std::map<std::string, std::string> Prasing_Request::get_mymap()
{
    return (mymap);
}
int Prasing_Request::get_status()
{
    return (status);
}
std::string Prasing_Request::get_method()
{
    return (methode);
}
std::string Prasing_Request::get_budy_url()
{
    return (budy_url);
}