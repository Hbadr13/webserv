#include "Response.hpp"

std::string ft_read(std::string name)
{
    std::string line_s;
    std::string line;

    std::ifstream file(name.c_str());
    if (file.is_open() == 0)
    {
        std::cout << "error: configiuration file note founde\n";
        exit(1);
    }
    while (getline(file, line))
    {
        line.append("\n");
        line_s += line;
    }
    return line_s;
}
int ft_exitt(std::string &res)
{

    res += "<!DOCTYPE html>\n";
    res += "<html>\n";
    res += "	<head>\n";
    res += "		<title>Cerveur 404</title>\n";
    res += "	</head>\n";
    res += "	<body>\n";
    res += "		<h1>Error 404<br>Page not found</h1>\n";
    res += "	</body>\n";
    res += "</html>\n";
    return 1;
}

int Response::run_cgi(Location &location, Prasing_Request &requst, Configuration &conf_serv)
{
    std::cout << "cookie = " << requst.get_mymap()["Cookie"] << std::endl;
    std::map<std::string, std::string> map_env;
    if (!requst.get_method().compare("POST"))
        map_env["CONTENT_LENGTH"] = "";
    map_env["CONTENT_TYPE"] = "";
    map_env["HTTP_COOKIE"] = requst.get_mymap()["Cookie"];
    map_env["HTTP_USER_AGENT"] = requst.get_mymap()["User-Agent"];
    map_env["PATH_INFO"] = requst.get_mymap()[""];
    map_env["QUERY_STRING"] = "";
    map_env["REMOTE_ADDR"] = "localhost" + conf_serv.getlisten();
    map_env["REQUEST_METHOD"] = requst.get_method();
    map_env["SCRIPT_FILENAME"] = "";
    map_env["SERVER_NAME"] = "localhost";
    
    std::string status;
    std::string root;
    if (!location.getroot().empty() && !conf_serv.getroot().empty())
        return ft_exitt(this->respons);
    root = conf_serv.getroot();
    if (!location.getroot().empty())
        root = location.getroot();
    char **av;
    av = (char **)malloc(sizeof(char *) * 3);
    std::string path = requst.get_url();
    if (path.compare(path.length() - 3, 3, ".py"))
        return ft_exitt(this->respons);
    path = root + path;
    av[0] = strdup("/usr/bin/python3");
    av[1] = strdup(path.c_str());
    av[2] = NULL;
    std::cout << path << std::endl;
    int fd_execute = open(path.c_str(), O_RDONLY);
    if (fd_execute < 0)
    {
        this->respons = "HTTP/1.1 404 not found\n\n";
        return ft_exitt(this->respons);
    }
    int fd = open("trash", O_WRONLY | O_TRUNC);
    if (fd < 0)
        return ft_exitt(this->respons);
    int pid = fork();
    if (pid == 0)
    {
        dup2(fd, 1);
        execve(av[0], av, NULL);
        std::cout << "hello\n";
        exit(1);
    }
    else
    {
        waitpid(pid, NULL, 0);
        close(fd);
        close(fd_execute);
    }
    this->respons = ft_read("trash");
    return 1;
}

// GET /cgi-bin/test.py HTTP/1.1
// Host: localhost:9010
// Connection: keep-alive
// Cache-Control: max-age=0
// sec-ch-ua: "Not_A Brand";v="99", "Google Chrome";v="109", "Chromium";v="109"
// sec-ch-ua-mobile: ?0
// sec-ch-ua-platform: "Linux"
// Upgrade-Insecure-Requests: 1
// User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36
// Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
// Sec-Fetch-Site: none
// Sec-Fetch-Mode: navigate
// Sec-Fetch-User: ?1
// Sec-Fetch-Dest: document
// Accept-Encoding: gzip, deflate, br
// Accept-Language: en-US,en;q=0.9,fr-MA;q=0.8,fr;q=0.7,ar-MA;q=0.6,ar;q=0.5,en-CA;q=0.4,es-US;q=0.3,es;q=0.2
// Cookie: SL_G_WPT_TO=en; SL_GWPT_Show_Hide_tmp=undefined; SL_wptGlobTipTmp=undefined

// 200 OK: The request was successful
// 201 Created: The request was successful and a new resource was created
// 204 No Content: The request was successful but there is no content to return
// 400 Bad Request: The request was malformed or invalid
// 401 Unauthorized: The user is not authenticated and cannot access the requested resource
// 403 Forbidden: The user is authenticated but does not have permission to access the requested resource
// 404 Not Found: The requested resource could not be found
// 500 Internal Server Error: An error occurred on the server while processing the request
// CGI scripts can also return other status codes, such as 302 Found or 303 See Other, which are used for redirection. However, the above codes are the most commonly used in HTTP responses.
