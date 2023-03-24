

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <vector>
#include <fcntl.h>
#include <map>
#include <sys/time.h>

fd_set g_ReadSet;
fd_set g_WriteSet;
fd_set g_ExceptSet;
int fd_set_Max;

int fdd[20];

class client // To store and manage client related information
{
public:
    std::string data;
    client(std::string data)
    {
        this->data = data;
    }
};
std::map<int, client> server;
long get_time_of_day(void)
{
    struct timeval time;
    long milliseconds;

    gettimeofday(&time, NULL);
    milliseconds = time.tv_sec * 1000 + time.tv_usec / 1000;
    return (milliseconds);
}
int main0(void)
{
    sockaddr_in ClientAddress;
    socklen_t nClientLength = sizeof(ClientAddress);
    std::string respons;
    respons = "HTTP/1.0 200\n\n";
    respons += "<!DOCTYPE html>";
    respons += "<html>";
    respons += "	<head>";
    respons += "		<title>Cerveur 200</title>";
    respons += "	</head>";
    respons += "	<body>";
    respons += "		<h1> may server<br> sev sev  sss </h1>";
    respons += "	</body>";
    respons += "</html>";
    fd_set read_fds;               // temp file descriptor list for select()
    struct sockaddr_in myaddr;     // server address
    struct sockaddr_in remoteaddr; // client address
    int listener;                  // listening socket descriptor
    int newfd;                     // newly accept()ed socket descriptor
    char buf[200];                 // buffer for client data
    int nbytes;
    int yes = 1; // for setsockopt() SO_REUSEADDR, below
    socklen_t addrlen;
    // get the listener
    if ((listener = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes,
                   sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    // bind
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons(9090);
    memset(&(myaddr.sin_zero), '\0', 8);
    if (bind(listener, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    // listen
    if (listen(listener, 10) == -1)
    {
        perror("listen");
        exit(1);
    }
    fd_set_Max = listener;
    FD_ZERO(&g_ReadSet); // clear the master and temp sets
    FD_ZERO(&g_WriteSet);
    FD_SET(listener, &g_ReadSet); // add to master set

    int clien[9000];
    fd_set read_set_cpy;
    fd_set write_set_cpy;
    while (true)
    {

        // InitSets(listener);
        read_set_cpy = g_ReadSet;
        write_set_cpy = g_WriteSet;

        select(fd_set_Max + 1, &read_set_cpy, &write_set_cpy, NULL, 0);
        int newfd = 0;
        for (int fd = 0; fd <= fd_set_Max; fd++)
        {

            if (FD_ISSET(fd, &read_set_cpy) && (fd == listener))
            {
                newfd = accept(listener, (sockaddr *)&ClientAddress, &nClientLength);
                if (-1 == newfd)
                {
                    printf("\nError occurred while accepting socket:");
                }
                // printf("\nClient connected from: %s", inet_ntoa(ClientAddress.sin_addr));
                FD_SET(newfd, &g_ReadSet); // add to master set
                if (newfd > fd_set_Max)
                { // keep track of the maximum
                    fd_set_Max = newfd;
                }
                // fcntl(newfd, F_SETFL, O_NONBLOCK);
                server.insert(std::make_pair(newfd, client("127.0.0.1 database")));
                // FD_CLR(fd, &g_ReadSet);
                // if (fd == fd_set_Max)
                //     fd_set_Max--;
            }
            else if (FD_ISSET(fd, &read_set_cpy))
            {
                bzero(buf, sizeof(buf));
                int n = read(fd, buf, sizeof(buf));
                if (n <= 0)
                    close(fd);
                // removeFromSet(i, _recv_fd_pool);
                // addToSet(i, _write_fd_pool);
                FD_CLR(fd, &g_ReadSet);
                if (fd == fd_set_Max)
                    fd_set_Max--;
                FD_SET(fd, &g_WriteSet);
                if (fd > fd_set_Max)
                    fd_set_Max = fd;
                printf("%s", buf);
                // printf("wait to send data:\n");
            }
            else if (FD_ISSET(fd, &write_set_cpy))
            {
                // bzero(buf, sizeof(buf));
                //     nbytes = server[fd].data.length();
                //     printf("%s", server[fd].data.c_str());
                // printf("wait to send data:\n");
                // removeFromSet(i, _write_fd_pool);
                // addToSet(i, _recv_fd_pool);
                int n = write(fd, respons.c_str(), respons.size());
                if (n <= 0)
                    close(fd);
                FD_CLR(fd, &g_WriteSet);
                if (fd == fd_set_Max)
                    fd_set_Max--;
                FD_SET(fd, &g_ReadSet);
                if (fd > fd_set_Max)
                    fd_set_Max = fd;
                // close(fd);
            }
        }
    }
    return 0;
}
std::string return_response()
{
    std::string respons;
    respons = "HTTP/1.0 200\n\n";
    respons += "<!DOCTYPE html>";
    respons += "<html>";
    respons += "	<head>";
    respons += "		<title>Cerveur 200</title>";
    respons += "	</head>";
    respons += "	<body>";
    respons += "		<h1> may server<br> sev sev  sss </h1>";
    respons += "	</body>";
    respons += "</html>";
    return respons;
}
int main1(void)
{
    std::string respons = return_response();
    fd_set master;                 // master file descriptor list
    fd_set read_fds;               // temp file descriptor list for select()
    struct sockaddr_in myaddr;     // server address
    struct sockaddr_in remoteaddr; // client address
    int fdmax;                     // maximum file descriptor number
    int listener;                  // listening socket descriptor
    int newfd;                     // newly accept()ed socket descriptor
    char buf[256];                 // buffer for client data
    int nbytes;
    int yes = 1; // for setsockopt() SO_REUSEADDR, below
    socklen_t addrlen;
    int i, j;
    FD_ZERO(&master); // clear the master and temp sets
    FD_ZERO(&read_fds);
    // get the listener
    if ((listener = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    // if (fcntl(listener, F_SETFL, O_NONBLOCK) < 0)
    // {
    //     exit(1);
    // }
    // lose the pesky "address already in use" error message
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes,
                   sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    // bind
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons(9090);
    memset(&(myaddr.sin_zero), '\0', 8);
    if (bind(listener, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    // listen
    if (listen(listener, 10) == -1)
    {
        perror("listen");
        exit(1);
    }
    // add the listener to the master set
    FD_SET(listener, &master);
    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it’s this one
    // main loop
    for (;;)
    {
        read_fds = master; // copy it
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(1);
        }
        // run through the existing connections looking for data to read
        for (i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(listener, &read_fds))
            {
                if ((newfd = accept(i, (sockaddr *)&remoteaddr, &addrlen)) == -1)
                {
                    perror("accept");
                    exit(1);
                }
                printf("\nClient connected from: %s", inet_ntoa(remoteaddr.sin_addr));
            }

            if (FD_ISSET(i, &read_fds))
            { // we got one!!
                if (i == listener)
                {
                    // handle new connections
                    addrlen = sizeof(remoteaddr);
                    if ((newfd = accept(listener, (struct sockaddr *)&remoteaddr,
                                        &addrlen)) == -1)
                    {
                        perror("accept");
                    }
                    else
                    {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax)
                        { // keep track of the maximum
                            fdmax = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                               "socket %d\n",
                               inet_ntoa(remoteaddr.sin_addr), newfd);
                    }
                    if (fcntl(newfd, F_SETFL, O_NONBLOCK) < 0)
                    {
                        exit(1);
                    }
                }
                else
                {
                    // handle data from a client
                    if ((nbytes = read(i, buf, sizeof(buf))) <= 0)
                    {
                        // got error or connection closed by client
                        if (nbytes == 0)
                        {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        }
                        else
                        {
                            perror("recv");
                        }
                        close(i);           // bye!
                        FD_CLR(i, &master); // remove from master set
                    }
                    else
                    {
                        // we got some data from a client
                        for (j = 0; j <= fdmax; j++)
                        {
                            // send to everyone!
                            if (FD_ISSET(j, &master))
                            {
                                // except the listener and ourselves
                                if (j != listener && j != i)
                                {
                                    if (send(j, respons.c_str(), respons.size(), 0) == -1)
                                    {
                                        perror("send");
                                    }
                                }
                            }
                        }
                    }
                } // it’s SO UGLY!
            }
        }
    }
    return 0;
}

int main(void)
{
    std::string respons = return_response();
    fd_set master;                 // master file descriptor list
    fd_set read_fds;               // temp file descriptor list for select()
    struct sockaddr_in myaddr;     // server address
    struct sockaddr_in remoteaddr; // client address
    int fdmax;                     // maximum file descriptor number
    int listener;                  // listening socket descriptor
    int newfd;                     // newly accept()ed socket descriptor
    char buf[40000];               // buffer for client data
    int nbytes;
    int yes = 1; // for setsockopt() SO_REUSEADDR, below
    socklen_t addrlen;
    int i, j;
    FD_ZERO(&master); // clear the master and temp sets
    FD_ZERO(&read_fds);
    // get the listener
    if ((listener = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    // lose the pesky "address already in use" error message
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes,
                   sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    // bind
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons(9090);
    memset(&(myaddr.sin_zero), '\0', 8);
    if (bind(listener, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    // listen
    if (listen(listener, 10) == -1)
    {
        perror("listen");
        exit(1);
    }
    // add the listener to the master set
    FD_SET(listener, &master);
    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it’s this one
    // main loop
    for (;;)
    {
        read_fds = master; // copy it
        if (select(fdmax + 1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(1);
        }
        // run through the existing connections looking for data to read
        for (i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &read_fds))
            { // we got one!!
                if (i == listener)
                {
                    // handle new connections
                    addrlen = sizeof(remoteaddr);
                    if ((newfd = accept(listener, (struct sockaddr *)&remoteaddr,
                                        &addrlen)) == -1)
                    {
                        perror("accept");
                    }
                    else
                    {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax)
                        { // keep track of the maximum
                            fdmax = newfd;
                        }
                        printf("selectserver: new connection from %s on "
                               "socket %d\n",
                               inet_ntoa(remoteaddr.sin_addr), newfd);
                    }
                }
                else
                {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
                    {
                        // got error or connection closed by client
                        if (nbytes == 0)
                        {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        }
                        else
                        {
                            perror("recv");
                        }
                        // exit(1);
                        close(i);           // bye!
                        FD_CLR(i, &master); // remove from master set
                    }
                    else
                    {
                        // we got some data from a client
                        std::cout << "----" << buf;
                        for (j = 0; j <= fdmax; j++)
                        {
                            // send to everyone!
                            if (FD_ISSET(j, &master))
                            {
                                // except the listener and ourselves
                                if (j != listener && j != i)
                                {
                                    if (send(j,respons.c_str() , respons.size(), 0) == -1)
                                    {
                                        perror("send");
                                    }
                                }
                            }
                        }
                    }
                } // it’s SO UGLY!
            }
        }
    }
    return 0;
}