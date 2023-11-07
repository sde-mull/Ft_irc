/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:49:22 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/06 17:33:54 by rreis-de         ###   ########.fr       */
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
                    Handle_Message(Parse::searchClientById(i));
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
    received = recv(client.getSocketFd(), buf, 1024, 0);
    if (received <= 0 && close(client.getSocketFd()))
        return (1);
    std::cout << std::endl << "response: " << buf << std::endl;
    if (client.f_auth == 1)
        return (0);
    else
        Client_Authenticate(client, buf, received);
    for (size_t i = 0; i < received; i++)
        buf[i] = '\0';
    return (0);
}

void Server::Client_Authenticate(Client &client, char *buf, int received)
{
    if (!Call_Functions(client, buf, received))
        std::cout << RED "Client not authenticated " << RESET << std::endl;
    PrintClientArgs(client);
    if (client.f_pass == 1 && client.getNick() != "\0" && client.getUser() != "\0")
    {
        std::cout << GREEN "CLIENT AUTHENTICATE" << RESET << std::endl;
        client.f_auth = 1;
    }
}

int Server::Call_Functions(Client &client, char *buf, int received)
{
    std::vector<std::string> vec = Parse::ft_split(buf, received);
    if (vec[0] == "SEND")
    {
        if (client.SendFile(client.getSocketFd(), vec[1].c_str()) == 2)
            return (2);
        //ReceiveFile(client.getSocketFd());
    } 
    int f = 0;
    for (int k = 0; k < vec.size(); k++)
    {
        std::map<std::string, function>::iterator it = m.find(std::string(vec[k]));
        if (it != m.end() && k < vec.size() - 1)
        {
            (this->*it->second)(client, vec[k + 1]);
            f = 1;
        }
    }
    return (f);
}

void    Server::ft_pass(Client &client, std::string str)
{
    if (this->_password == str)
        client.f_pass = 1;
    else
        client.f_pass = 0;
}

void    Server::ft_user(Client &client, std::string str)
{
    client.setUser(str);
}

void     Server::ft_nick(Client &client, std::string str)
{
    if (!Parse::CheckNickRules(str))
    {
        Parse::printErrorMessage("Bad Nick", 2);
        return ;
    }
    if (!Parse::CheckClientByNick(str))
    {
        Parse::printErrorMessage("Nick Already Taken", 2);
        return ;
    }
    client.setNick(str);   
}

void    Server::ReceiveFile(int socketFd)
{
    char *filename = "file2.txt";
    FILE *fp;
    char buffer[1024];
    int received;

    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror("Error creating file\n");
        return ;
    }
    while (1)
    {
        received = recv(socketFd, buffer, 1024, 0);
        if (received <= 0)
            return ;
        fprintf(fp, "%s", buffer);
        bzero(buffer, 1024);
    }
    return ;
}

void    Server::SendMsg(Client &client, const char *data)
{
    send(client.getSocketFd(), data, strlen(data), 0);
}

void    Server::PrintClientArgs(Client &client)
{
    if (client.f_pass)
    {
        SendMsg(client, "\nYou have set the correct password");
        SendMsg(client, GREEN);
        SendMsg(client, " ✔\n");
        SendMsg(client, RESET);
    } 
    else
    {
        SendMsg(client, "You have not set the correct password");
        SendMsg(client, RED);
        SendMsg(client, " ✘\n");
        SendMsg(client, RESET);
    }
    SendMsg(client, "This is your Nick: ");
    if (client.getNick() != "\0")
    {
        SendMsg(client, client.getNick().c_str());
        SendMsg(client, GREEN);
        SendMsg(client, " ✔\n");
        SendMsg(client, RESET);
    }  
    else
    {
        SendMsg(client, RED);
        SendMsg(client, " ✘\n");
        SendMsg(client, RESET);
    }
    SendMsg(client, "This is your User: ");
    if (client.getUser() != "\0")
    {
        SendMsg(client, client.getUser().c_str());
        SendMsg(client, GREEN);
        SendMsg(client, " ✔\n");
        SendMsg(client, RESET);

    }
    else
    {
        SendMsg(client, RED);
        SendMsg(client, " ✘\n");
        SendMsg(client, RESET);
    }
}