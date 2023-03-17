What is web server? :

vidoe       https://www.youtube.com/watch?v=Ad7nbWf6fjQ&ab_channel=AlmTech                            
document    https://www.techtarget.com/whatis/definition/Web-server
![Screenshot](https://www.elegantthemes.com/blog/wp-content/uploads/2022/07/Featured-Image-3-1.jpg)

[HTTP: What are HTTP requests and response? :](https://www.cronj.com/blogwhat-are-http-requests-and-response/jFM6D7pdptSbA4zy)




https://github.com/sFinOe/HTTP-Web-Server#readme

![Screenshot](https://media.geeksforgeeks.org/wp-content/uploads/20220330131350/StatediagramforserverandclientmodelofSocketdrawio2-448x660.png)

What is **OSI** : video
[![Watch the video](https://shardeum.org/blog/wp-content/uploads/2022/09/The-Physical-Layer-in-OSI-Model-Explained-thumbnail.jpg)](https://youtu.be/9zqHMl9_s5k)


**Sockets**
Programming with TCP/IP sockets
There are a few steps involved in using sockets:

Create the socket
Identify the socket
On the server, wait for an incoming connection
Send and receive messages
Close the socket
https://www.geeksforgeeks.org/socket-programming-cc/

Learn **Select** system call in C
The select() system call in C allows a program to monitor multiple file descriptor sources for events or data availability. It can be used to implement timeouts and to wait for multiple file descriptors to become ready for operations such as reading or writing.

The general syntax of the select() system call is as follows:

```c
#include<sys/select.h>
int select(int nfds, fd_set *readfds, fd_set *writefds,
           fd_set *exceptfds, struct timeval *timeout);
```

**nfds**: The highest-numbered file descriptor in any of the three sets, plus 1.

**readfds**: A set of file descriptors to be checked for readability.

**writefds**: A set of file descriptors to be checked for writability.\n**

**exceptfds**: A set of file descriptors to be checked for exceptions.

**timeout**: A pointer to a struct timeval structure that specifies the maximum time for which the call 
should block, or NULL if the call should block indefinitely.

The select() system call modifies the file descriptor sets to indicate which file descriptors are ready for the specified operations. It returns the number of ready file descriptors, or -1 if an error occurred.

Here is an example of how to use select() to wait for data to be available on a socket:

```c
fd_set readfds;
struct timeval timeout;

FD_ZERO(&readfds);
FD_SET(sockfd, &readfds);
timeout.tv_sec = 5;
timeout.tv_usec = 0;

int n = select(sockfd + 1, &readfds, NULL, NULL, &timeout);

if (n == -1) {
    // handle error
} else if (n == 0) {
    // handle timeout
} else {
    if (FD_ISSET(sockfd, &readfds)) {
        // read data from sockfd
    }
}
more information => https://www.mkssoftware.com/docs/man3/select.3.asp 

```


**configuration file** : https://docs.nginx.com/nginx/admin-guide/web-server/web-server/

readmi https://github.com/c3b5aw/webserv/blob/main/docs/config_file.md




**CGI**
run cgi in my laptop : https://techexpert.tips/nginx/python-cgi-nginx/

[ CGI Environment Variables](https://www6.uniovi.es/~antonio/ncsa_httpd/cgi/env.html)

git add . ; git commit -m "http server" ; git push origin master 
