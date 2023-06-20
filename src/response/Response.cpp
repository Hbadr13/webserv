#include "Response.hpp"

Response::Response()
{
}
Response::~Response()
{
}
std::string int_to_string(int numb)
{
    std::ostringstream ss;
    ss << numb;
    return ss.str();
}

std ::string chec_url(std ::string urll)
{
    size_t i = 0;
    int j = 0;
    std ::string result;
    while (urll[i] == '/')
        i++;
    while (urll[i] != '/' && i < strlen(urll.c_str()))
    {
        if (j == 0)
        {
            result = "/";
            j = 1;
        }
        result += urll[i];
        i++;
    }
    return result;
}

std ::string status_delete(int status, std ::string str, std ::map<int, std::string> mymap_erorr)
{
    std ::string bady;
    std ::string url3;
    int h;
    if ((h = open(mymap_erorr[status].c_str(), O_RDWR)) != -1)
    {
        url3 = mymap_erorr[status];
        close(h);
    }
    else
        url3 = "src/error/" + int_to_string(status) + ".html";

    int d = open(url3.c_str(), O_RDWR);
    if (d == -1)
    {
        return (NULL);
    }
    time_t now = time(0);
    char *time = ctime(&now);
    std::ifstream file(url3.c_str());
    std::string http;
    if (file)
    {
        std::ostringstream str;
        str << file.rdbuf();
        http = str.str();
    }
    bady.append("HTTP/1.1 ");
    bady.append(int_to_string(status));
    bady.append(" ");
    bady.append(str);
    bady.append("\nServer: Server\nDate: ");
    bady.append(time);
    bady.append("Content-Type: text/html\nContent-Length: ");
    int len = http.length();
    bady.append(int_to_string(len));
    bady.append("\n\n");
    bady.append(http);
    close(d);
    return (bady);
}
std ::string mesag_error1(int status)
{
    std ::string msg;
    if (status == 200)
        msg = " file deleted";
    if (status == 202)
        msg = " Accepted";
    if (status == 204)
        msg = " No Content";
    if (status == 400)
        msg = " Bad Requestd";
    if (status == 401)
        msg = " Unauthorized";
    if (status == 403)
        msg = " Forbidden";
    if (status == 404)
        msg = " Page not found";
    if (status == 405)
        msg = " Method Not Allowed";
    if (status == 409)
        msg = " Conflict";
    if (status == 505)
        msg = " HTTP Version Not Supported";
    return msg;
}
std ::string check_auto(Location &location, Configuration &conf_serv, std ::string root)
{
    std ::string str;
    if (!location.getindex().empty())
        str = root + "/" + location.getindex();
    else
        str = root + "/" + conf_serv.getindex();
    return str;
}
Response::Response(Request rq, Configuration conf_serv)
{
    std::string str99;
    std::pair<Location, std::string> location_and_url = find_location(rq.get_url(), conf_serv, str99);
    int found_method = 0;
    std ::string root;
    std ::string url2;
    int fd = 0;
    int d;
    int j;
    status = rq.get_status();
    mymap = rq.get_mymap();
    mymap_erorr = conf_serv.geterror();
    std ::string url =  "/" + rq.getUrl2();
    //rq.get_url();
    std ::string method = rq.get_method();
    std::cout << "___________________________________"<<rq.get_url()<<"________________________________\n";
    for (size_t i = 0; i < location_and_url.first.getallow_methods().size(); i++)
        if (method == location_and_url.first.getallow_methods()[i])
            found_method = 1;
    if (status == 200)
    {
        if (location_and_url.first.getroot().empty() && conf_serv.getroot().empty())
            status = 403;
        else if (found_method == 0)
            status = 405;
    }
    if (!location_and_url.first.getroot().empty())
        root = location_and_url.first.getroot() + url;
    else
        root = conf_serv.getroot() + url;
    std ::string autoindex;
    std ::string str = check_auto(location_and_url.first, conf_serv, root);
    if (location_and_url.first.getautoindex() == "on" && (d = open(str.c_str(), O_RDWR)) != -1)
    {
        autoindex = "off";
        close(d);
    }
    else if (!location_and_url.first.getautoindex().empty() && location_and_url.first.getautoindex() == "on")
        autoindex = "on";
    else
        autoindex = "off";
    if (autoindex != "on")
    {
        DIR *dir = opendir(root.c_str());
        if (dir != NULL && !location_and_url.first.getindex().empty())
            url2 = root + "/" + location_and_url.first.getindex();
        else if (dir != NULL && !conf_serv.getindex().empty())
            url2 = root + "/" + conf_serv.getindex();
        else
        {
            fd = 1;
            url2 = root;
            if (!access(url2.c_str(), F_OK) && access(url2.c_str(), R_OK))
                fd = 0;
        }
        if (dir)
            closedir(dir);
    }
    if (status == 200)
    {
        if (method == "POST" || method == "GET")
        {

            DIR *dir;
            dirent *ent;
            if (autoindex == "on")
                dir = opendir(root.c_str());
            else
                dir = opendir(url2.c_str());
            std::string url1;
            if (rq.get_url() == location_and_url.second)
            {

                if (!location_and_url.first.getreturn().empty())
                {
                    std ::string bady;
                    bady = "HTTP/1.1 301 Moved Permanently";
                    bady.append("\nLocation: ");
                    bady.append(location_and_url.first.getreturn()[1]);
                    bady.append("\n");
                    respons = bady;

                    return;
                }
            }
            if (autoindex == "off")
            {
                if ((j = open(url2.c_str(), O_RDWR)) != -1)
                {
                    if (!location_and_url.second.compare("/cgi-bin"))
                    {
                        if (run_cgi(location_and_url.first, rq, conf_serv, url2))
                            return;
                    }
                    std ::string bady;
                    std::ifstream file(url2.c_str());
                    std::string http;
                    if (file)
                    {
                        std::ostringstream str;
                        str << file.rdbuf();
                        http = str.str();
                    }
                    bady.append("HTTP/1.1 ");
                    bady.append(int_to_string(status));
                    bady.append(" OK \nServer: Server\nDate: ");
                    time_t now = time(0);
                    char *time = ctime(&now);
                    bady.append(time);
                    bady.append("Content-Type: ");
                    bady.append(Content_type(url2));
                    bady.append("\nContent-Length: ");
                    int len = http.length();
                    bady.append(int_to_string(len));
                    bady.append("\n\n");
                    bady.append(http);
                    respons = bady;
                    close(j);
                    return;
                }
                else if (autoindex == "off" && location_and_url.first.getautoindex() == "on")
                    autoindex = "on";
                else
                {
                    std ::string url3;
                    int h;
                    if (dir != NULL || fd == 0 || (!access(url2.c_str(), F_OK) && access(url2.c_str(), R_OK)))
                    {
                        status = 403;
                        if ((h = open(mymap_erorr[403].c_str(), O_RDWR)) != -1)
                        {
                            url3 = mymap_erorr[403];
                            close(h);
                        }
                        else
                            url3 = "src/error/403.html";
                    }
                    else
                    {
                        status = 404;
                        if ((h = open(mymap_erorr[404].c_str(), O_RDWR)) != -1)
                        {
                            url3 = mymap_erorr[404];
                            close(h);
                        }
                        else
                            url3 = "src/error/404.html";
                    }
                    std ::string bady;
                    int i = open(url3.c_str(), O_RDWR);
                    if (i == -1)
                        return;
                    std::ifstream file(url3.c_str());
                    std::string http;
                    if (file)
                    {
                        std::ostringstream str;
                        str << file.rdbuf();
                        http = str.str();
                    }
                    bady.append("HTTP/1.1 ");
                    bady.append(int_to_string(status));
                    bady.append(mesag_error1(status));
                    bady.append("\nServer: Server\nDate: ");
                    time_t now = time(0);
                    char *time = ctime(&now);
                    bady.append(time);
                    bady.append("Content-Type: text/html\nContent-Length: ");
                    int len = http.length();
                    bady.append(int_to_string(len));
                    bady.append("\n\n");
                    bady.append(http);
                    respons = bady;
                    close(i);
                    return;
                }
            }
            if (autoindex == "on")
            {
                int i;
                std ::string bady;
                std ::string msg;
                bady.append("HTTP/1.1 ");
                bady.append(int_to_string(status));
                bady.append(" OK \nServer: Server \nDate: ");
                time_t now = time(0);
                char *time = ctime(&now);
                bady.append(time);
                if (dir != NULL)
                {
                    bady.append("Content-Type: text/html\nContent-Length: ");
                    msg = "<!DOCTYPE html>\n\
                        <html lang=\"en\">\n\
                        <ol> ";
                    while ((ent = readdir(dir)) != NULL)
                    {
                        std::string name = ent->d_name;
                        std::string name1;
                        if (url[0] == '/' && !url[1])
                            name1 = name;
                        else
                            name1 = url + "/" + name;
                        if (name != ".")
                            msg += "\n<li><a href=\"" + name1 + "\">" + name + "</a></li>\n";
                    }
                    msg += "</ol>\n\
                           </html>";
                    int len = msg.length();
                    bady.append(int_to_string(len));
                    bady.append("\n\n");
                    bady.append(msg);
                    respons = bady;
                    closedir(dir);
                    return;
                }
                else if ((i = open(root.c_str(), O_RDWR)) != -1)
                {
                    bady.append("Content-Type: ");
                    bady.append(Content_type(root));
                    bady.append("\nContent-Length: ");
                    std::ifstream file(root.c_str());
                    std::string http;
                    if (file)
                    {
                        std::ostringstream str;
                        str << file.rdbuf();
                        http = str.str();
                    }
                    int len = http.length();
                    bady.append(int_to_string(len));
                    bady.append("\n\n");
                    bady.append(http);
                    respons = bady;
                    close(i);
                    return;
                }
                else
                {
                    int h;
                    std ::string url3;
                    if (dir != NULL || (!access(root.c_str(), F_OK) && access(root.c_str(), R_OK)))
                    {
                        status = 403;
                        if ((h = open(mymap_erorr[403].c_str(), O_RDWR)) != -1)
                        {
                            url3 = mymap_erorr[403];
                            close(h);
                        }
                        else
                            url3 = "src/error/403.html";
                    }
                    else
                    {
                        status = 404;
                        if ((h = open(mymap_erorr[404].c_str(), O_RDWR)) != -1)
                        {
                            url3 = mymap_erorr[404];
                            close(h);
                        }
                        else
                            url3 = "src/error/404.html";
                    }
                    int d = open(url3.c_str(), O_RDWR);
                    if (d == -1)
                        return;
                    std::ifstream file(url3.c_str());
                    std::string http;
                    if (file)
                    {
                        std::ostringstream str;
                        str << file.rdbuf();
                        http = str.str();
                    }
                    bady.append("HTTP/1.1 ");
                    bady.append(int_to_string(status));
                    bady.append(mesag_error1(status));
                    bady.append("\nServer: Server\nDate: ");
                    bady.append(time);
                    bady.append("Content-Type: text/html\nContent-Length: ");
                    int len = http.length();
                    bady.append(int_to_string(len));
                    bady.append("\n\n");
                    bady.append(http);
                    respons = bady;
                    close(d);
                    return;
                }
            }
        }
        else
        {
            std ::string del = chec_url(url);

            if (del != "/upload")
            {
                status = 409;
                respons = status_delete(status, "Conflict", mymap_erorr);
                return;
            }

            DIR *dir;
            dir = opendir(root.c_str());
            if (dir == NULL)
            {
                std ::string dl = "/" + root;
                if (remove(root.c_str()) == 0)
                {
                    status = 202;
                    respons = status_delete(status, "Accepted", mymap_erorr);
                    return;
                }
                else
                {
                    status = 204;
                    respons = status_delete(status, "No Content", mymap_erorr);
                    return;
                }
            }

            else if (dir != NULL)
            {
                status = 401;
                respons = status_delete(status, "Unauthorized", mymap_erorr);
                return;
            }
        }
    }
    else
    {
        std ::string bady;
        int h;
        std ::string url3; //= "error/" + int_to_string(status) + ".html";
        if ((h = open(mymap_erorr[status].c_str(), O_RDWR)) != -1)
        {
            url3 = mymap_erorr[status];
            close(h);
        }
        else
            url3 = "src/error/" + int_to_string(status) + ".html";
        int d = open(url3.c_str(), O_RDWR);
        if (d == -1)
            return;
        std::ifstream file(url3.c_str());
        time_t now = time(0);
        char *time = ctime(&now);
        std::string http;
        if (file)
        {
            std::ostringstream str;
            str << file.rdbuf();
            http = str.str();
        }
        bady.append("HTTP/1.1 ");
        bady.append(int_to_string(status));
        bady.append(mesag_error1(status));
        bady.append("\nServer: Server\nDate: ");
        bady.append(time);
        bady.append("Content-Type: text/html\nContent-Length: ");
        int len = http.length();
        bady.append(int_to_string(len));
        bady.append("\n\n");
        bady.append(http);
        respons = bady;
        close(d);
        return;
    }
}

std ::string Response::get_respons()
{
    return (this->respons);
}