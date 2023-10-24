/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:57:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/24 11:59:01 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void)
{
    std::cout << B_GREEN "Client default contrutor called" RESET << std::endl;
}

Client::Client(char *ip, int port)
{
    std::cout << B_GREEN "Client Initialized contrutor called" RESET << std::endl;
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

Client::~Client(void)
{
    std::cout << B_RED "Client destructor called" RESET << std::endl;
}

Client::Client(Client const &src)
{
    *this = src;
}

Client & Client::operator=(Client const &rhs)
{
    (void)rhs;
    return (*this);
}

/* void Client::Create_Socket()
{
    this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
}

void Client::Create_Address(char *ip, int port)
{
    struct sockaddr_in *address = static_cast<struct sockaddr_in*>(malloc((sizeof(struct sockaddr_in))));
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    if (strlen(ip) == 0)
        address->sin_addr.s_addr = INADDR_ANY;
    else
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    this->address = address;
} */

int Client::Connect_Socket()
{
    return (connect(this->_socket_fd, (struct sockaddr*)this->_address, sizeof(*(this->_address))));
}

void Client::Send(char *msg)
{
    send(_socket_fd, msg, strlen(msg), 0);
}

void Client::Receive()
{
    std::string line;
    char    buf[1024];

    while (1)
    {
        std::cin.ignore('\n');
        std::getline(std::cin, line);
        int charcount = line.size();
        //std::cout << RED << line << std::endl;
        if (charcount > 0)
        {
            if(!strcmp(line.c_str(), "exit\n"))
                break ;
            send(_socket_fd, line.c_str(), line.size(), 0);
        }
        else
            break ;
    } 
    recv(_socket_fd, buf, 1024, 0);
    std::cout << "response was: " << buf << std::endl;
}