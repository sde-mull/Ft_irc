/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:49:22 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/31 16:54:00 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//Server constructors and desctrucor

Server::Server(void)
{
    std::cout << B_GREEN "Server default contrutor called" RESET << std::endl;
}

Server::Server(uint16_t port, std::string password) : _port(port), _password(password)
{
    std::cout << B_GREEN "Server parametric constructor called" RESET << std::endl;
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
    this->_port = getPort();
    this->_password = getPassword();
    return (*this);
}

//Server getters

uint16_t Server::getPort(void) const
{
    return (this->_port);
}

std::string Server::getPassword(void) const
{
    return (this->_password);
}

//Server running system

int Server::bound2BeServer(void)
{
    if (bind(this->_socketFd, (struct sockaddr*)this->_address, sizeof(*(this->_address))) == -1)
        return (Parse::printErrorMessage(B_YELLOW "Failed to bind ", 1));
    if (listen(this->_socketFd, 10) == -1)
        return (Parse::printErrorMessage(B_YELLOW "Failed to listen ", 1));
    return (0);
}

void   Server::createIPv4Address(void)
{
    struct sockaddr_in *address = static_cast<struct sockaddr_in*>(malloc((sizeof(struct sockaddr_in))));
    address->sin_family = AF_INET;
    address->sin_port = htons(this->_port);
    address->sin_addr.s_addr = INADDR_ANY;
    this->_address = address;
    std::cout << B_GREEN "IPv4Address was created successfully!" RESET << std::endl;
}

int Server::acceptConnection(void)
{
    struct sockaddr *clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    int newSocketFd = accept(_socketFd, clientAddr, &clientAddrSize);
    return (newSocketFd);

}

int    Server::startConnection(void)
{
    std::cout << B_YELLOW "Server is starting the connection" RESET << std::endl;
    this->_socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->_socketFd == -1)
        return (Parse::printErrorMessage(B_YELLOW "Failed to create socket" RESET , 1));
    std::cout << B_GREEN "TCPIPv4Socket was created successfully!" RESET << std::endl;
    createIPv4Address();
    if (bound2BeServer())
        return (2);
    std::cout << B_GREEN "Server is running on port " << this->_port << RESET << std::endl;
    
    
    return (0);
}

int     Server::Handle_Message(Client client)
{
    std::cout << "other action" << std::endl;
    return (0);
}
