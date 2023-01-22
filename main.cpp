#include "include/webserv.hpp"

// int main(int argc, char const *argv[])
// {
//     int server_fd, new_socket, valread;
//     struct sockaddr_in address;
//     int opt = 1;
//     int addrlen = sizeof(address);
//     char buffer[1024] = {0};
//     char *hello = (char *)"Hello from server";
//     server_fd = socket(AF_INET, SOCK_STREAM, 0);
//     setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;
//     address.sin_port = htons(PORT);
//     bind(server_fd, (struct sockaddr *)&address, sizeof(address));
//     listen(server_fd, 3);
//     new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
//     std::cout << "connected" << std::endl;
//     valread = read(new_socket, buffer, 1000);
//     printf("%s", buffer);
//     return 0;
// }

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    // Create a socket and bind it to an IP and port
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(7070);
    bind(server_socket, (sockaddr*) &address, sizeof(address));

    // Listen for incoming connections
    listen(server_socket, 5);

    // while (true) {
        // Accept a connection from a client
        sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int client_socket = accept(server_socket, (sockaddr*) &client_address, &client_len);

        // Read the request from the client
        char buffer[1024];
        recv(client_socket, buffer, sizeof(buffer), 0);

        // Check if the request is for the index.html file
        std::string request(buffer);
        if (request.find("GET /index.html") != std::string::npos) {
            // Open the index.html file
            std::ifstream file("index.html");
            std::stringstream html;
            html << file.rdbuf();

            // Create the HTTP response
            std::string response = "HTTP/1.1 200 OK\r\n";
            response += "Content-Type: text/html\r\n";
            response += "Content-Length: " + std::to_string(html.str().size()) + "\r\n";
            response += "\r\n";
            response += html.str();

            // Send the response to the client
            send(client_socket, response.c_str(), response.size(), 0);
        }
    printf("\r\njsd");
        // Close the connection to the client
        close(client_socket);
    // }
    return 0;
}

