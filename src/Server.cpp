/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:49:22 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/23 17:08:51 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void)
{
    std::cout << B_GREEN "Server default contrutor called" RESET << std::endl;
}

Server::Server(char *ip, int port)
{
    std::cout << B_GREEN "Server Initialized contrutor called" RESET << std::endl;
    this->_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in *address = static_cast<struct sockaddr_in*>(malloc((sizeof(struct sockaddr_in))));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    if (strlen(ip) == 0)
        address->sin_addr.s_addr = INADDR_ANY;
    else
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    this->_address = address;
}

Server::~Server(void)
{
    std::cout << B_RED "Server destructor called" RESET << std::endl;
}

Server::Server(Server const &src)
{
    *this = src;
}

Server & Server::operator=(Server const &rhs)
{
    (void)rhs;
    return (*this);
}

int Server::bound2BeServer(void)
{
    int i = bind(this->_socket_fd, (struct sockaddr*)this->_address, sizeof(*(this->_address)));
    if (i == 0)
        i = listen(_socket_fd, 10);
    return (i);
}

void    Server::Accept(void)
{
    struct sockaddr *clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    _acceptFd = accept(_socket_fd, clientAddr, &clientAddrSize);
    char    buf[1024];
    size_t     received;
    int     i;
    while (1)
    {
        received = recv(_acceptFd, buf, 1024, 0);
        if (received == -1)
            break ;
        printf("response: %s\n", buf);
        if (!strncmp(buf, "EXIT", 4))
            break ;
        else if (received == 0)
            break ;
        i = 0;
        while (i < received)
            buf[i++] = '\0';
    }
    printf("response: %s\n", buf);
    close (_acceptFd);
}