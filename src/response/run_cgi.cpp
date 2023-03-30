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
void free_tab(char **envp)
{
    for (int i = 0; envp[i] != NULL; i++)
    {
        free(envp[i]);
    }
    free(envp);
}

char **get_env_form_map(std::map<std::string, std::string> &map_env)
{
    char **envp;
    envp = (char **)malloc(sizeof(char *) * (map_env.size() + 1));
    if (envp == NULL)
        return NULL;
    int i = 0;
    std::map<std::string, std::string>::iterator it = map_env.begin();
    while (it != map_env.end())
    {
        std::string str = it->first + "=" + it->second;
        envp[i] = strdup(str.c_str());
        if (envp[i] == NULL)
            return envp;
        it++;
        i++;
    }
    envp[i] = NULL;
    return envp;
}

char **init_may_env(Location &location, Prasing_Request &requst, Configuration &conf_serv)
{
    std::string url = parsing_url(requst.get_url());
    std::map<std::string, std::string> map_env;
    char *ptr;

    if (requst.get_method().compare("POST") == 0)
        map_env["CONTENT_LENGTH"] = "";
    map_env["CONTENT_TYPE"] = "";
    map_env["HTTP_COOKIE"] = requst.get_mymap()["Cookie"];
    map_env["HTTP_USER_AGENT"] = requst.get_mymap()["User-Agent"];
    map_env["PATH_INFO"] = requst.get_mymap()[""];
    map_env["QUERY_STRING"] = requst.get_budy_url();
    map_env["REMOTE_ADDR"] = "localhost" + int_to_string(conf_serv.getlisten());
    map_env["REQUEST_METHOD"] = requst.get_method();
    map_env["SCRIPT_FILENAME"] = requst.get_url().substr(requst.get_url().rfind("/"), requst.get_url().size());
    map_env["SERVER_NAME"] = "localhost";
    map_env["GATEWAY_INTERFACE"] = "CGI/1.1";
    map_env["SERVER_PORT"] = int_to_string(conf_serv.getlisten());
    map_env["SERVER_PROTOCOL"] = "HTTP/1.1";
    ptr = getcwd(NULL, 0);
    if (ptr)
        map_env["PATH_TRANSLATED"] = (std::string)getcwd(NULL, 0);
    else
        map_env["PATH_TRANSLATED"] = "";
    free(ptr);
    map_env["SCRIPT_FILENAME"] = url.substr(1, url.size());
    map_env["SCRIPT_NAME"] = url;
    map_env["AUTH_TYPE"] = "Basic";
    map_env["CONTENT_TYPE"] = "";
    char **envp = get_env_form_map(map_env);
    return envp;
}

int Response::run_cgi(Location &location, Prasing_Request &requst, Configuration &conf_serv)
{
    std::string status;
    std::string root;
    std::string path;
    int status_exec;
    std::string url;
    char **envp;
    char **av;
    int pid;
    int fd;

    av = (char **)malloc(sizeof(char *) * 3);
    if (requst.get_method().compare("POST") && requst.get_method().compare("GET"))
    {
        this->respons = "HTTP/1.1 405 Method Not Allowed\r\n";
        this->respons += "content-type: text/html\r\n";
        this->respons += "\r\n";
        this->respons += ft_read("www/error/error404.html");
        throw std::string("ERROR CGI: Method Not Allowed");
    }
    if (av == NULL)
    {
        this->respons = "HTTP/1.1 503 Service Unavailable\r\n";
        this->respons += "content-type: text/html\r\n";
        this->respons += "\r\n";
        this->respons += ft_read("www/error/error404.html");
        throw std::string("ERROR CGI: malloc");
    }
    url = parsing_url(requst.get_url());
    if (location.getroot().empty() && conf_serv.getroot().empty())
    {
        this->respons = "HTTP/1.1 403 Forbidden\r\n";
        this->respons += "content-type: text/html\r\n";
        this->respons += "\r\n";
        this->respons += ft_read("www/error/error404.html");
        throw std::string("ERROR CGI: root not found");
    }
    root = conf_serv.getroot();
    if (!location.getroot().empty())
        root = location.getroot();
    path = url;
    std::cout << "path =" << path << std::endl;
    if (path.compare(path.length() - 3, 3, ".py") && path.compare(path.length() - 4, 4, ".php"))
    {
        this->respons = "HTTP/1.1 403 Forbidden\r\n";
        this->respons += "content-type: text/html\r\n";
        this->respons += "\r\n";
        this->respons += ft_read("www/error/error404.html");
        this->respons += "403";
        throw std::string("ERROR CGI: may cgi works with code python only");
    }
    path = root + path;
    if (!path.compare(path.length() - 3, 3, ".py"))
    {
        av[0] = strdup("/usr/bin/python3");
        av[1] = strdup((path).c_str());
        av[2] = NULL;
    }
    else if (!path.compare(path.length() - 4, 4, ".php"))
    {
        av[0] = strdup("/usr/bin/php");
        av[1] = strdup((path).c_str());
        av[2] = NULL;
    }
    int fd_execute = open(path.c_str(), O_RDONLY);
    if (fd_execute < 0)
    {
        this->respons = "HTTP/1.1 404 not found\r\n";
        this->respons += "content-type: text/html\r\n";
        this->respons += "\r\n";
        this->respons += ft_read("www/error/error404.html");
        this->respons += "404";
        throw std::string("ERROR CGI: path not found {" + path + "}");
    }
    std::ofstream outfile("www/trash/trash.txt");
    fd = open("www/trash/trash.txt", O_WRONLY | O_TRUNC);
    if (fd < 0)
    {
        this->respons = "HTTP/1.1 500 Internal Server Error\r\n";
        this->respons += "content-type: text/html\r\n";
        this->respons += "\r\n";
        this->respons += ft_read("www/error/error404.html");
        this->respons += "500";
        throw std::string("ERROR CGI: www/trash/trash.txt not found");
    }
    envp = init_may_env(location, requst, conf_serv);
    pid = fork();
    if (pid == -1)
    {
        this->respons = "HTTP/1.1 500 Internal Server Error\r\n";
        this->respons += "content-type: text/html\r\n";
        this->respons += "\r\n";
        this->respons += ft_read("www/error/error404.html");
        this->respons += "500";
        throw std::string("ERROR CGI: problem in fork");
    }
    if (pid == 0)
    {
        dup2(fd, 1);
        execve(av[0], av, envp);
        exit(1);
    }
    else
    {
        waitpid(pid, &status_exec, 0);
        close(fd);
        close(fd_execute);
        if (status_exec)
        {
            this->respons = "HTTP/1.1 501 Not Implemented\r\n";
            this->respons += "content-type: text/html\r\n";
            this->respons += "\r\n";
            this->respons += ft_read("www/error/error404.html");
            this->respons += "501";
            free_tab(envp);
            unlink("www/trash/trash.txt");
            throw std::string("ERROR CGI: error in execve");
        }
    }
    this->respons = "HTTP/1.0 200\r\n";
    this->respons += ft_read("www/trash/trash.txt");
    free_tab(envp);
    std::cout << this->respons << std::endl;
    unlink("www/trash/trash.txt");
    return 1;
}

// 200 OK: The request was successful
// 201 Created: The request was successful and a new resource was created
// 204 No Content: The request was successful but there is no content to return
// 400 Bad Request: The request was malformed or invalid
// 401 Unauthorized: The user is not authenticated and cannot access the requested resource
// 403 Forbidden: The user is authenticated but does not have permission to access the requested resource
// 404 Not Found: The requested resource could not be found
// 500 Internal Server Error: An error occurred on the server while processing the request
// CGI scripts can also return other status codes, such as 302 Found or 303 See Other, which are used for redirection. However, the above codes are the most commonly used in HTTP responses.
