/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcpclient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmorales <moralesrojascr@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:26:36 by cmorales          #+#    #+#             */
/*   Updated: 2024/02/08 19:58:38 by cmorales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

#define PORT 8080
#define SERVER_PORT 80
#define BUFFER 4096

void p_error(const char *msg) {
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}

int main(int ac, char **av) {
    int sockfd;
    struct sockaddr_in servaddr;
    int addrlen = sizeof(servaddr);

    char sendline[BUFFER];
    char recvline[BUFFER];

    if (ac != 2) {
        std::cout << "usage: " << av[0] << " <server address>" << std::endl;
        return 1;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        p_error("Error while creating socket");

    bzero(&servaddr, addrlen);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, av[1], &servaddr.sin_addr) <= 0)
        p_error("Inet_pton error for av1");

    if (connect(sockfd, (struct sockaddr *) &servaddr, addrlen) < 0)
        p_error("Error conecting to the server");

    sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
    int sendbytes = strlen(sendline);
    if (write(sockfd, sendline, sendbytes) != sendbytes)
        p_error("Write error");

    // Close the connection immediately after sending the request
    close(sockfd);

    return 0;
}