#include "Response.hpp"
#include <ctime>
#include <fstream>
#include <filesystem>
#include <dirent.h>


#include <iostream>
Response::Response()
{

}

std :: string chec_url(std :: string  urll)
{
    int i = 0;
    int j= 0;
    std :: string result;
   while(urll[i] == '/')
        i++;
    while(urll[i] != '/' && i < strlen(urll.c_str()))
    {
        if(j == 0)
        {
            result = "/";
              j = 1;  
        }
        result += urll[i];
        i++;
    }
    return result;
}
Response::Response(Prasing_Request  rq,Configuration conf_serv)
{
    status = rq.get_status();
    mymap = rq.get_mymap();
    std :: string url = rq.get_url();
    std :: string def_url = chec_url(url);
    Location loct(conf_serv,"/");
   std::cout<<"->" <<loct.getautoindex()[0]<<std::endl;
   std::cout<<"->" <<loct.getindex()[0]<<std::endl;
   std::cout<<"->" <<loct.getroot()[0]<<std::endl;
   std::cout<<"->" <<loct.getautoindex()[0]<<std::endl;
   std ::cout<<"|||||||||||||||||||||||||||||||||||||||||||||\n";
    exit(1);
    std :: cout << def_url << std::endl;
    std :: string method = rq.get_method();
    std :: string autoindex =  "on";
        // if(autoindex == "off")
        //    url1 = "/index.html";
    std :: string root  = "../my_web/" + url;
    if(1)
    {

        std::string url1;
        if(url == "/return")
        {
            std ::string bady;
            bady = "HTTP/1.1 301 Moved Permanently";
            bady.append("\nLocation: ");
            bady.append("../my_web/www");
            bady.append("\n");
            respons = bady;
            return ;

        }
        if(autoindex == "on")
        {

                 DIR *dir;
                 dirent *ent;
                 std ::string bady;
                 std ::string msg;
                 bady.append("HTTP/1.1 ");
                 bady.append(std::to_string(status));
                 bady.append(" OK \nServer: Server \nDate: ");
                 time_t now = time(0); 
                 char *time = ctime(&now); 
                 bady.append(time);
                 bady.append("Content-Type: text/html\nContent-Length: "); 

            if((dir = opendir(root.c_str())) != NULL)
            {
                 msg = "<!DOCTYPE html>\n\
                        <html lang=\"en\">\n\
                        <ol> ";
                while ((ent = readdir (dir)) != NULL)
                {
                    std ::string name = ent->d_name;
                    std::string name1;
                     if (url[0] == '/' && !url[1])   
                        name1 =  name;
                    else 
                     name1 = url + "/" + name;
                    msg+= "\n<li><a href=\"" + name1 + "\">" + name + "</a></li>\n";
                }
                    msg+= "</ol>\n\
                           </html>";
             int len = msg.length();
            bady.append(std::to_string(len));
            bady.append("\n\n");
            bady.append(msg);
             respons = bady;
               closedir (dir);
                return;

            }
            else if(int i = open(root.c_str(),O_RDWR))
            {
                std::ifstream file(root.c_str()); 
                std::string http;
                if(file)
                {    
                    std::ostringstream str;
                    str << file.rdbuf(); 
                    http = str.str();
                }
                int len = http.length();
                bady.append(std::to_string(len));
                bady.append("\n\n");
                bady.append(http);
                respons = bady;
                close (i);
                return;
            }
            


        }
        else {
             std :: string url2 = root + url1;
            int  i = open(url2.c_str(),O_RDWR);
               std ::string bady;
               std::ifstream file(url2.c_str()); 
               std::string http;
               if(file) 
               {
                      std::ostringstream str;
                      str << file.rdbuf(); 
                      http = str.str();
               }
               bady.append("HTTP/1.1 ");
               bady.append(std::to_string(status));
               bady.append(" OK \nServer: Server\nDate: ");
               time_t now = time(0); 
               char *time = ctime(&now); 
               bady.append(time);
               bady.append("Content-Type: text/html\nContent-Length: "); 
               int  len = http.length();
               bady.append(std::to_string(len));
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