What is web server? :

vidoe       https://www.youtube.com/watch?v=Ad7nbWf6fjQ&ab_channel=AlmTech                            
document    https://www.techtarget.com/whatis/definition/Web-server
![Screenshot](https://www.elegantthemes.com/blog/wp-content/uploads/2022/07/Featured-Image-3-1.jpg)

HTTP: What are HTTP requests and response? :

https://www.cronj.com/blog/what-are-http-requests-and-response/j
FM6D7pdptSbA4zy


https://github.com/sFinOe/HTTP-Web-Server#readme

![Screenshot](https://media.geeksforgeeks.org/wp-content/uploads/20220330131350/StatediagramforserverandclientmodelofSocketdrawio2-448x660.png)


1. Socket creation:
int sockfd = socket(domain, type, protocol)

sockfd: socket descriptor, an integer (like a file-handle)
domain: integer, specifies communication domain. We use AF_ LOCAL as defined in the POSIX standard for communication between processes on the same host. For communicating between processes on different hosts connected by IPV4, we use AF_INET and AF_I NET 6 for processes connected by IPV6.
type: communication type
SOCK_STREAM: TCP(reliable, connection oriented)
SOCK_DGRAM: UDP(unreliable, connectionless)
protocol: Protocol value for Internet Protocol(IP), which is 0. This is the same number which appears on protocol field in the IP header of a packet.(man protocols for more details)


git add . ; git commit -m "http server" ; git push origin master 
