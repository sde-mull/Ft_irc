/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:49:22 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/02 14:43:02 by sde-mull         ###   ########.fr       */
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
    struct sockaddr clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    int newSocketFd = accept(this->_socketFd, (struct sockaddr*)&clientAddr, &clientAddrSize);
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
    int client_socket;

    int nbr_clients = 5;
    FD_ZERO(&current_sockets);
    FD_SET(this->_socketFd, &current_sockets);

    while (true)
    {
        ready_sockets = current_sockets;
        if (select(nbr_clients + 1, &ready_sockets, NULL, NULL, NULL) == -1)
            return (Parse::printErrorMessage("select failed", 3));

        for (int i = 0; i <= nbr_clients; i++)
        {
            if (FD_ISSET(i, &ready_sockets))
            {
                if (i == this->_socketFd)
                {
                    client_socket = acceptConnection();
                    FD_SET(client_socket, &current_sockets);
                    Parse::addClient(client_socket);
                    if (client_socket > nbr_clients)
                        nbr_clients = client_socket;
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
    if (client.f_pass == 1 && client.getNick() != "\0" && client.getUser() != "\0")
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
        if (buf[j] == '\n')
            nova += ' ';
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
    client.setUser(str);
}

void    Server::ft_nick(Client &client, std::string str)
{
    if (str[0] == '#' || str[0] == '&' || str[0] == '$' || str[0] == ':')
        return ;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '*' || str[i] == '?'\
        || str[i] == '!' || str[i] == '@' || str[i] == '.')
            return ;
    }
    for(int i = 0; i < this->_clients.size(); i++)
    {
        if (this->_clients[i].getNick() == str)
        {
            std::cout << "NICK ALREADY TAKEN" << std::endl;
            return ;
        }
    }
    std::cout << "SET NICK" << std::endl;
    client.setNick(str);   
}
