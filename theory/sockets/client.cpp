/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c++                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 21:03:07 by cmorales          #+#    #+#             */
/*   Updated: 2024/01/30 00:09:13 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char const **argv)
{
    int sock = 0; 
    long valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    
    //Create the communicating socket to the server with IPv4 localhost and TCP conexion
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    
    //Cofigurete the serv_addr to set up the socket
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Inet_pton => Convert IPv4 and IPv6 addresses from text to binary form and put in sin_addr
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    
    //Try to conect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    //Send a text to the server
    send(sock , hello , strlen(hello) , 0 );
    printf("Client message sent\n");
    
    //Catch the server dates and alloc in the buffer, then print it
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}