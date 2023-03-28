#include "Response.hpp"
#include <ctime>
#include <fstream>
#include <filesystem>
#include <dirent.h>

#include <iostream>

std ::string Content_type(std ::string root)
{
    int i = 0;
    while (root[i] && root[i] != '.')
        i++;
    i++;
    std ::string re;
    while (root[i])
        re += root[i++];
    std::map<std::string, std::string> Content_type;

    Content_type["html"] = "text/html";
    Content_type["htm"] = "text/html";
    Content_type["shtml"] = "text/html";
    Content_type["css"] = "text/css";
    Content_type["xml"] = "text/xml";
    Content_type["gif"] = "image/gif";
    Content_type["jpeg"] = "image/jpeg";
    Content_type["jpg"] = "image/jpeg";
    Content_type["js"] = "application/javascript";
    Content_type["atom"] = "application/atom+xml";
    Content_type["rss"] = "application/rss+xml";
    Content_type["mml"] = "text/mathml";
    Content_type["txt"] = "text/plain";
    Content_type["jad"] = "text/vnd.sun.j2me.app-descriptor";
    Content_type["wml"] = "text/vnd.wap.wml";
    Content_type["htc"] = "text/x-component";
    Content_type["avif"] = "image/avif";
    Content_type["png"] = "image/png";
    Content_type["svgz"] = "image/svg+xml";
    Content_type["svg"] = "image/svg+xml";
    Content_type["tiff"] = "image/tiff";
    Content_type["tif"] = "image/tiff";
    Content_type["wbmp"] = "image/vnd.wap.wbmp";
    Content_type["webp"] = "image/webp";
    Content_type["ico"] = "image/x-icon";
    Content_type["jng"] = "image/x-jng";
    Content_type["bmp"] = "image/x-ms-bmp";
    Content_type["woff"] = "font/woff";
    Content_type["woff2"] = "font/woff2";
    Content_type["jar"] = "application/java-archive";
    Content_type["war"] = "application/java-archive";
    Content_type["ear"] = "application/java-archive";
    Content_type["json"] = "application/json";
    Content_type["hqx"] = "application/mac-binhex40";
    Content_type["doc"] = "application/msword";
    Content_type["pdf"] = "application/pdf";
    Content_type["eps"] = "application/postscript";
    Content_type["ps"] = "application/postscript";
    Content_type["ai"] = "application/postscript";
    Content_type["rtf"] = "application/rtf";
    Content_type["m3u8"] = "application/vnd.apple.mpegurl";
    Content_type["kml"] = "application/vnd.google-earth.kml+xml";
    Content_type["kmz"] = "application/vnd.google-earth.kmz";
    Content_type["xls"] = "application/vnd.ms-excel";
    Content_type["eot"] = "application/vnd.ms-fontobject";
    Content_type["ppt"] = "application/vnd.ms-powerpoint";
    Content_type["odg"] = "application/vnd.oasis.opendocument.graphics";
    Content_type["odp"] = "application/vnd.oasis.opendocument.presentation";
    Content_type["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
    Content_type["odt"] = "application/vnd.oasis.opendocument.text";
    Content_type["wmlc"] = "application/vnd.wap.wmlc";
    Content_type["wasm"] = "application/wasm";
    Content_type["7z"] = "application/x-7z-compressed";
    Content_type["cco"] = "application/x-cocoa";
    Content_type["jardiff"] = "application/x-java-archive-diff";
    Content_type["jnlp"] = "application/x-java-jnlp-file";
    Content_type["run"] = "application/x-makeself";
    Content_type["pl"] = "application/x-perl";
    Content_type["pm"] = "application/x-perl";
    Content_type["pdb"] = "application/x-pilot";
    Content_type["prc"] = "application/x-pilot";
    Content_type["rar"] = "application/x-rar-compressed";
    Content_type["rpm"] = "application/x-redhat-package-manager";
    Content_type["sea"] = "application/x-sea";
    Content_type["swf"] = "application/x-shockwave-flash";
    Content_type["sit"] = "application/x-stuffit";
    Content_type["tcl"] = "application/x-tcl";
    Content_type["tk"] = "application/x-tcl";
    Content_type["der"] = "application/x-x509-ca-cert";
    Content_type["pem"] = "application/x-x509-ca-cert";
    Content_type["crt"] = "application/x-x509-ca-cert";
    Content_type["xpi"] = "application/x-xpinstall";
    Content_type["xhtml"] = "application/xhtml+xml";
    Content_type["xspf"] = "application/xspf+xml";
    Content_type["zip"] = "application/zip";
    Content_type["dll"] = "application/octet-stream";
    Content_type["exe"] = "application/octet-stream";
    Content_type["bin"] = "application/octet-stream";
    Content_type["deb"] = "application/octet-stream";
    Content_type["dmg"] = "application/octet-stream";
    Content_type["iso"] = "application/octet-stream";
    Content_type["img"] = "application/octet-stream";
    Content_type["msi"] = "application/octet-stream";
    Content_type["msp"] = "application/octet-stream";
    Content_type["msm"] = "application/octet-stream";
    Content_type["midi"] = "midi";
    Content_type["mid"] = "audio/midi";
    Content_type["kar"] = "audio/midi";
    Content_type["mp3"] = "audio/mpeg";
    Content_type["ogg"] = "audio/ogg";
    Content_type["m4a"] = "audio/x-m4a    ";
    Content_type["ra"] = "audio/x-realaudio";
    Content_type["3gp"] = "video/3gpp";
    Content_type["3gpp"] = "video/3gpp";
    Content_type["ts"] = "video/mp2t";
    Content_type["mp4"] = "video/mp4";
    Content_type["mpg"] = "video/mpeg";
    Content_type["mpeg"] = "video/mpeg";
    Content_type["mov"] = "video/quicktime";
    Content_type["webm"] = "video/webm";
    Content_type["flv"] = "video/x-flv";
    Content_type["m4v"] = "video/x-m4v";
    Content_type["mng"] = "video/x-mng";
    Content_type["asf"] = "video/x-ms-asf";
    Content_type["asx"] = "video/x-ms-asf";
    Content_type["wmv"] = "video/x-ms-wmv";
    Content_type["avi"] = "video/x-msvideo";
    Content_type["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    Content_type["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    return (Content_type[re]);
}

Response::Response()
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
    std::cout<<"url: "<<urll<<std::endl;
    int i = 0;
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
                // Location l()
                Location location(conf_serv, it->first);
                // std::cout << it->first << std::endl;
                return std::pair<Location, std::string>(location, it->first);
            }
            it++;
        }
        if (!url_check.compare("/"))
            break;
    }
    return std::pair<Location, std::string>(Location(), std::string());
}

Response::Response(Prasing_Request rq, Configuration conf_serv)
{

    std::cout << "url = " << rq.get_url() << std::endl;
    std::pair<Location, std::string> location_and_url = find_location(rq.get_url(), conf_serv);
    // std::cout << "-->"<<rq.get_mymap()["Cookie"]<<std::endl;

    // std::cout<<"------>"<<location_and_url.first.getallow_methods()[0]<<std::endl;
    try
    {
        if (!location_and_url.second.compare("/cgi-bin"))
            run_cgi(location_and_url.first, rq, conf_serv);
    }
    catch (std::string &var)
    {
        std::cerr << var << '\n';
    }
    status = rq.get_status();
    mymap = rq.get_mymap();
    std ::string url = rq.get_url();
    // Location loca(conf_serv, url);
    std ::string method = rq.get_method();
    std ::string root;
    std ::string url2;
    int j;
    if (!location_and_url.first.getroot().empty())
        root = location_and_url.first.getroot() + url;
    else
        root = conf_serv.getroot() + url;
    std ::string autoindex;
    if ( !location_and_url.first.getautoindex().empty() && location_and_url.first.getautoindex() == "on")
        autoindex = "on";
    else
        autoindex = "off";
    if (autoindex != "on")
    {
        DIR *dir = opendir(root.c_str());
        if (dir  != NULL && !location_and_url.first.getindex().empty())
            url2 = root + "/" + location_and_url.first.getindex();
        else if (dir!= NULL && !conf_serv.getindex().empty())
             url2 = root + "/" + conf_serv.getindex()[0];
        else
            url2 = root;
        closedir(dir);
    }
    // if(autoindex == "off")
    //    url1 = "/index.html";
    if (1)
    {
        DIR *dir;
        dirent *ent;
        if(autoindex == "on")
            dir = opendir(root.c_str());
        else
            dir = opendir(url2.c_str());

        std::string url1;
        if (!location_and_url.first.getreturn_path().empty())
        {
            std ::string bady;
            bady = "HTTP/1.1 301 Moved Permanently";
            bady.append("\nLocation: ");
            bady.append(location_and_url.first.getreturn_path());
            bady.append("\n");
            respons = bady;
            return;
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
                status = 404;
                std ::string bady;
                std ::string url3 = "www/error.html";
                int d = open(url3.c_str(), O_RDWR);
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
                bady.append(" ErrorDocument \nServer: Server\nDate: ");
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
        else if ((j = open(url2.c_str(), O_RDWR)) != -1)
        {
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
        else if (dir != NULL)
        {
            // std :: cout << "ssssssssssssssssssssss\n";
            std ::string bady;
            std ::string msg;
            bady.append("HTTP/1.1 ");
            bady.append(int_to_string(status));
            bady.append(" OK \nServer: Server \nDate: ");
            time_t now = time(0);
            char *time = ctime(&now);
            bady.append(time);
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
        else
        {
            status = 404;
            std ::string bady;
            std ::string url3 = "www/error.html";
            int i = open(url3.c_str(), O_RDWR);
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
            bady.append(" ErrorDocument \nServer: Server\nDate: ");
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
}

std ::string Response::get_respons()
{
    return (this->respons);
}