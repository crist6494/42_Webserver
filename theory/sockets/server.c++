/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c++                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:39:16 by cmorales          #+#    #+#             */
/*   Updated: 2024/01/30 00:30:12 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/*
SOCKET is the mechanism that most popular operating systems 
provide to give programs access to the network

Programming with TCP/IP sockets
There are a few steps involved in using sockets:
1° Create the socket
2° Identify the socket
3° On the server, wait for an incoming connection
4° Send and receive messages
5° Close the socket
*/


/* struct  sockaddr_in
{
    sin -> sokcet internet
    
    __uint8_t         sin_len; -> Struct len, in most cases it is usually omitted
    sa_family_t       sin_family; -> directions family: ipv4 ipv6...
    in_port_t         sin_port;  -> the port of the ip
    struct in_addr    sin_addr; -> IP direction
    char              sin_zero[8];  -> fill the struct so that it has the same size
}; */



int main()
{   
    //1° Create a socket => int socket(int domain, int type, int protocol); -> return (1 correct | -1 wrong)
    int server_socket_fd;
    if((server_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Cannot create the socket");
        return 1;
    }
    

    //2° Identify (name) socket ==> int bind(int socket, const struct sockaddr *address, sockerlen_t adress_len)
    const int port = 8080;
    struct sockaddr_in address;
    
    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    /* htonl converts a long integer (e.g. address) to a network representation  | INADDR_ANY = 0.0.0.0*/ 
    /* htons converts a short integer (e.g. port) to a network representation */ 
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);

    if(bind(server_socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Bind failed");
        return 1;
    }

    //3° On the server, wait for an incoming connection => server should have a socket that is prepared to accept the connections
    //Socket mode listen, more than 10 conection = conection refused and send an error
    if(listen(server_socket_fd, 10) < 0)
     {
        perror("In listen");
        return(1);
    }
    int new_socket;
    int addrlen = sizeof(address);
    //If accept is successful return a new socket with the conection accepted
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if((new_socket = accept(server_socket_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
        {
            perror("In accept");
            return (1);
        }
        /*The original socket that was set up for listening is used only for accepting connections, not for exchanging data. 
        By default, socket operations are synchronous, or blocking, 
        and accept will block until a connection is present on the queue.*/


        //4° Send and receive messages
        char buffer[1024] = {0};
        int valread = read(new_socket, buffer, 1024);
        if(valread < 0)
            printf("No bytes aree there ro read");
        char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
        write(new_socket, hello, strlen(hello));
        printf("------------------ Server message sent-------------------\n");
        //5° Close the socket
        close(new_socket);
    }
    return (0);
}