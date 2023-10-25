/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:49:22 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/25 16:47:56 by sde-mull         ###   ########.fr       */
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

void    Server::acceptConnection(void)
{
    struct sockaddr *clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    std::cout << B_GREEN "Server is running..." RESET << std::endl;
    this->_acceptFd = accept(_socketFd, clientAddr, &clientAddrSize);

    const char* createChannelCommands[] = {
        "NICK yourserver",           // Set a temporary server nickname
        "USER yourserver 0 * :Your Server", // Set user information
        "MODE #mychannel +t",        // Set channel modes (topic settable by operator)
        "JOIN #mychannel",           // JOIN the channel
    };

    for (const char* command : createChannelCommands) {
        send(this->_acceptFd, command, strlen(command), 0);
        send(this->_acceptFd, "\r\n", 2, 0); // Terminate IRC messages with \r\n
    }
    char    buf[1024];
    size_t     received;
    int     i;
    while (1)
    {
        received = recv(this->_acceptFd, buf, 1024, 0);
        // Server::Handle_Message(buf, this->_acceptFd);
        if (received == -1)
            break ;
        printf("response1: %s\n", buf);
        i = 0;
        while (i < received)
            buf[i++] = '\0';
    }
    close (_acceptFd);
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
    acceptConnection();
    return (0);
}

int     Server::Handle_Message(char *message, int fd)
{
    if (!Check_Client(fd))
    {
        std::cout << "New Client" << std::endl;
        return (2);
    }
    else
        std::cout << "Old Client" << std::endl;
    /* char **arr = ft_split(message, 32);
    if (!strcmp(arr[0], "PASS") && !strncmp(arr[1], this->_password.c_str(), strlen(arr[1]) - 1))
        std::cout << "TAS A TENTAR PASSAR" << std::endl;
    else    
        std::cout << "ATAO" << std::endl; */
    return (0);
}

int    Server::Check_Client(int fd)
{
    for (int i = 0; i < _clients.size(); i++)
    {
        if (_clients[i].getSocketFd() == fd)
            return (1);
    }
    return (0);
}