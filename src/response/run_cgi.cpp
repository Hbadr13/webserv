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

char **init_may_env(Prasing_Request &requst, Configuration &conf_serv)
{
    std::string name;
    std::string value;
    std::string url1 = requst.get_budy_url();
    if (!url1.empty())
    {     
        size_t lenName = url1.find("=");
        if (lenName == std::string::npos)
            ;
        else
        {
            lenName++;
            for (; url1[lenName] != '&'; lenName++)
                name += url1[lenName];
        }
        size_t lenValue = url1.find("=", lenName);
        if (lenValue == std::string::npos)
            ;
        else
        {
            lenValue++;
            for (; lenValue < url1.size(); lenValue++)
                value += url1[lenValue];
        }
    }
    std::string url = parsing_url(requst.get_url());
    std::map<std::string, std::string> map_env;
    char *ptr;

    if (requst.get_method().compare("POST") == 0)
        map_env["CONTENT_LENGTH"] = "";
    map_env["CONTENT_TYPE"] = "";
    map_env["HTTP_COOKIE"] =  requst.get_mymap()["Cookie"];
    map_env["HTTP_USER_AGENT"] = requst.get_mymap()["User-Agent"];
    map_env["PATH_INFO"] = requst.get_mymap()[""];
    map_env["QUERY_STRING"] = requst.get_budy_url();
    map_env["REMOTE_ADDR"] = requst.get_mymap()["localhost"] + int_to_string(conf_serv.getlisten());
    // map_env["REQUEST_METHOD"] = requst.get_method();
    map_env["SCRIPT_FILENAME"] = requst.get_url().substr(requst.get_url().rfind("/"), requst.get_url().size());
    // map_env["SERVER_NAME"] = "localhost";
    // map_env["GATEWAY_INTERFACE"] = "CGI/1.1";
    map_env["SERVER_PORT"] = int_to_string(conf_serv.getlisten());
    map_env["SERVER_PROTOCOL"] = "HTTP/1.1";
    ptr = getcwd(NULL, 0);
    if (ptr)
        map_env["PATH_TRANSLATED"] = (std::string)getcwd(NULL, 0);
    else
        map_env["PATH_TRANSLATED"] = "";
    if(ptr)
        free(ptr);
    if (!name.empty() || !name.empty())
    {
        map_env["NAME"] = name;
        map_env["VALUE"] = value;
    }
    map_env["SCRIPT_FILENAME"] = url.substr(1, url.size());
    map_env["SCRIPT_NAME"] = url;
    map_env["AUTH_TYPE"] = "Basic";
    map_env["CONTENT_TYPE"] = "";
    char **envp = get_env_form_map(map_env);
    return envp;
}

std::string return_path(std::string path, std::string status)
{
    std::string page;
    std::string buf;
    
    if(open(path.c_str(), O_RDONLY) != -1)
        page =  path;
    else
        page = "src/error/" + status + ".html";
    std::ifstream file(page.c_str());
    if (file)
    {
        std::ostringstream str;
        str << file.rdbuf();
        buf = str.str();
    }
    return buf;
}

int Response::run_cgi(Location &location, Prasing_Request &requst, Configuration &conf_serv,std::string path)
{
    std::string status;
    std::string root;
    int status_exec;
    std::string url;
    char **envp;
    char **av;
    int flag;
    int pid;
    int fd;

    flag = 0;
    size_t i;
    for (i = 0; i < location.getallow_methods().size(); i++)
    {
        if (!location.getallow_methods()[i].compare(requst.get_method()))
            flag = 1;      
    }
    if (path.compare(path.length() - 3, 3, ".py") && path.compare(path.length() - 4, 4, ".php"))
    {
        this->respons = "HTTP/1.1 403 Forbidden\r\n";
        this->respons += "content-type: text/html\r\n";
        this->respons += "\r\n";
        this->respons += return_path(mymap_erorr[403], "403");
        return 0;
    }
    int fd_execute = open(path.c_str(), O_RDONLY);
    std::ofstream outfile("src/server/trash/trash.txt");
    fd = open("src/server/trash/trash.txt", O_WRONLY | O_TRUNC);
    if (fd < 0)
    {
        this->respons = "HTTP/1.1 500 Internal Server Error\r\n";
        this->respons += "content-type: text/html\r\n";
        this->respons += "\r\n";
        this->respons += return_path(mymap_erorr[500], "500");
        return 1;
    }
    av = (char **)malloc(sizeof(char *) * 3);
    if (av == NULL)
    {
        this->respons = "HTTP/1.1 500 Internal Server Error\r\n";
        this->respons += "content-type: text/html\r\n";
        this->respons += "\r\n";
        this->respons += return_path(mymap_erorr[500], "500");
        std::cout<<"ERROR CGI: malloc"<<std::endl;
        return 1;
    }
    if (!path.compare(path.length() - 3, 3, ".py"))
    {
        av[0] = strdup("/usr/bin/python3");
        av[1] = strdup((path).c_str());
        av[2] = NULL;
    }
    else if (!path.compare(path.length() - 4, 4, ".php"))
    {
        av[0] = strdup("./src/server/php-cgi");
        av[1] = strdup((path).c_str());
        av[2] = NULL;
    }
    envp = init_may_env(requst, conf_serv);
    pid = fork();
    if (pid == -1)
    {
        this->respons = "HTTP/1.1 500 Internal Server Error\r\n";
        this->respons += "content-type: text/html\r\n";
        this->respons += "\r\n";
        this->respons += return_path(mymap_erorr[500], "500");
        free_tab(envp);
        unlink("src/server/trash//trash.txt");
        std::cout<<"ERROR CGI: problem in fork"<<std::endl;
        return 1;
    }
    if (pid == 0)
    {
        if(-1 == dup2(fd, 1))
            exit(1);
        if(-1 == execve(av[0], av, envp))
            exit(1);
        exit(1);
    }
    else
    {
        waitpid(pid, &status_exec, 0);
        close(fd);
        close(fd_execute);
        if (status_exec)
        {
            this->respons = "HTTP/1.1 500 Internal Server Error\r\n";
            this->respons += "content-type: text/html\r\n";
            this->respons += "\r\n";
            this->respons += return_path(mymap_erorr[500], "500");
            free_tab(envp);
            unlink("src/server/trash/trash.txt");
            std::cout<<"ERROR CGI: error in execve"<<std::endl;
            return 1;
        }
    }
    this->respons = "HTTP/1.1 200\r\n";
    this->respons += return_path("src/server/trash/trash.txt", "-1");
    free_tab(envp);
    unlink("src/server/trash/trash.txt");
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
// 