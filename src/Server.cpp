/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:49:22 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/31 10:37:53 by rreis-de         ###   ########.fr       */
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
    this->m["PASS"] = &Server::ft_pass;
    this->m["USER"] = &Server::ft_user;
    this->m["NICK"] = &Server::ft_nick;
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

    Client client(this->_acceptFd);
    while (1)
    {
        if (Handle_Message(client))
            break ;
    }
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

int     Server::Handle_Message(Client &client)
{
    char    buf[1024];
    size_t     received;
    int     i;
    received = recv(client.getSocketFd(), buf, 1024, 0);
    if (received <= 0 && close(client.getSocketFd()))
        return (1);
    std::cout << "response: " << buf << std::endl;
    if (client.f_auth == 1)
    {
        std::cout << "Old Client" << std::endl;
        return (0);
    }
    else
        std::cout << "New Client" << std::endl;
    std::vector<std::string> vec = this->ft_split(buf, received);
    for (int k = 0; k < vec.size(); k++)
    {
        std::map<std::string, function>::iterator it = m.find(std::string(vec[k]));
        if (it != m.end() && k < vec.size() - 1)
            (this->*it->second)(client, vec[k + 1]);
    }
    if (client.f_pass == 1 && client.f_nick == 1 && client.f_user == 1)
    {
        std::cout << "CLIENT AUTHENTICATE" << std::endl;
        client.f_auth = 1;
    }
    i = 0;
    while (i < received)
        buf[i++] = '\0';
    return (0);
}

std::vector<std::string>    Server::ft_split(char *buf, int received)
{
    std::string nova;
    for (size_t j = 0; j < received; j++)
    {
        if (buf[j] != '\n' && buf[j] != '\r')
            nova += buf[j];
    }
    std::istringstream ss(nova);
    std::vector<std::string> vec;
    std::string token;
    while (std::getline(ss, token, ' '))
        vec.push_back(token);
    return (vec);
}

void    Server::ft_pass(Client &client, std::string str)
{
    if (this->_password == str)
    {
        std::cout << "PASSE CERTA" << std::endl;
        client.f_pass = 1;
    }
    else
    {
        std::cout << "PASSE ERRADA" << std::endl;
        client.f_pass = 0;
    } 
}

void    Server::ft_user(Client &client, std::string str)
{
    std::cout << "SET USER" << std::endl;
    client.f_user = 1;
    client.setUser(str);
}

void    Server::ft_nick(Client &client, std::string str)
{
    int taken = 0;
    for(int i = 0; i < this->_clients.size(); i++)
    {
        if (this->_clients[i].getNick() == str)
        {
            std::cout << "NICK ALREADY TAKEN" << std::endl;
            taken = 1;
            break ;
        }
    }
    if (taken == 0)
    {
        std::cout << "SET NICK" << std::endl;
        client.f_nick = 1;
        client.setNick(str);   
    }
}
