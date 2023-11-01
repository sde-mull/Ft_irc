/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:49:22 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/01 19:11:41 by sde-mull         ###   ########.fr       */
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

int Server::bindAndListen(void)
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

    int newSocketFd = accept(this->_socketFd, clientAddr, &clientAddrSize);
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
    if (bindAndListen())
        return (2);
    std::cout << B_GREEN "Server is running on port " << this->_port << RESET << std::endl;

    fd_set current_sockets, ready_sockets;
    char    buf[1024];
    size_t     received;
    int client_socket;

    Parse::reserveSpaceClients(15);
    FD_ZERO(&current_sockets);
    FD_SET(this->_socketFd, &current_sockets);

    while (true)
    {
        ready_sockets = current_sockets;

        if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0)
            return (Parse::printErrorMessage("select failed", 3));
        
        for (int i = 0; i < FD_SETSIZE; i++)
        {
            if (FD_ISSET(i, &ready_sockets))
            {
                if (i == this->_socketFd)
                {
                    client_socket = acceptConnection();
                    FD_SET(client_socket, &current_sockets);
                    Parse::addClient(client_socket);
                }
                else
                {
                    Handle_Message(Parse::searchClient(i));
                }
            }
        }
    }
    

    return (0);
}

int     Server::Handle_Message(Client &client)
{
    char    buf[1024];
    size_t     received;
    int     i;
    received = recv(client.getSocketFd(), buf, 1024, 0);
    if (received <= 0 && close(client.getSocketFd()))
        return (1);
    std::cout << "response: " << buf << std::endl;
    i = 0;
    while (i < received)
        buf[i++] = '\0';
    return (0);
}