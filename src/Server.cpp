/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:49:22 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/07 00:10:35 by sde-mull         ###   ########.fr       */
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
    this->m["PASS"] = &Server::ft_pass;
    this->m["USER"] = &Server::ft_user;
    this->m["NICK"] = &Server::ft_nick;
    Parse::printMessage("Server Object Constructed!", CYAN);
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

int Server::bindAndListenServer(void)
{
    Parse::printMessage("Binding Server Socket to IPv4 Address", YELLOW);
    if (bind(this->_serverSocketFd, (struct sockaddr*)this->_address, sizeof(*(this->_address))) == -1)
        throw FailedBind();
    Parse::printMessage("Bind Successfull!", GREEN);
    if (listen(this->_serverSocketFd, 10) == -1)
        throw FailedListen();
    Parse::printMessage("Server is listening...", GREEN);
    return (0);
}

void   Server::creatingIPv4Address(void)
{
    Parse::printMessage("Creating IPv4 Address", YELLOW);
    struct sockaddr_in *address = static_cast<struct sockaddr_in*>(new struct sockaddr_in);
    address->sin_family = AF_INET;
    address->sin_port = htons(this->_port);
    address->sin_addr.s_addr = INADDR_ANY;
    this->_address = address;
    Parse::printMessage("IPv4 Address Created Sucessfully", GREEN);
}

int Server::acceptConnection(void)
{
    struct sockaddr clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);

    Parse::printMessage("Server is accepting a new client", YELLOW);
    int newSocketFd = accept(this->_serverSocketFd, (struct sockaddr*)&clientAddr, &clientAddrSize);
    return (newSocketFd);
}

void    Server::CreatingSocket(int domain, int type, int protocol) // We can use this way in case we need to create other type of sockets beside this one
{
    int enable = 1;

    this->_serverSocketFd = socket(domain, type, protocol);
    if (this->_serverSocketFd == -1)
        throw FailedSocketCreation();
    Parse::printMessage("Server Socket Created Successfully!", GREEN);
    if (setsockopt(this->_serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
        throw FailedSetSockopt();
}

int    Server::ServerRunning(void)
{
    fd_set  ready_sockets;
    int     client_socket;
    int     nbr_clients = 5;

    FD_ZERO(&this->_currentSockets);
    FD_SET(this->_serverSocketFd, &this->_currentSockets);

    while (true){
        ready_sockets = this->_currentSockets;
        if (select(nbr_clients + 1, &ready_sockets, NULL, NULL, NULL) == -1){
            Parse::printErrorMessage("Select Failed", 2);
            continue ;
        }
        for (int i = 0; i <= nbr_clients; i++){
            if (FD_ISSET(i, &ready_sockets)){
                if (i == this->_serverSocketFd){
                    client_socket = acceptConnection();
                    if (client_socket == -1){
                        Parse::printErrorMessage("Failed to accept the new Client", 1);
                        continue ;
                    }
                    FD_SET(client_socket, &this->_currentSockets);
                    Parse::addClient(client_socket);
                    Parse::printMessage("New Client Accepted", GREEN);
                    if (client_socket > nbr_clients)
                        nbr_clients = client_socket;
                }
                else{
                    if (Handle_Message(Parse::searchClientById(i)) == 1){
                        
                    }
                }
            }
        }
    }
    return (0);
}

int    Server::startConnection(void)
{
    try{
        Parse::printMessage("---------Initializing Server---------", GREEN);
        Parse::printMessage("Creating Server Socket", YELLOW);
        CreatingSocket(AF_INET, SOCK_STREAM, 0);
        creatingIPv4Address();
        bindAndListenServer();
        std::cout << GREEN "---------Server is running on port " << this->_port << "---------" <<RESET << std::endl;
    }
    catch(const std::exception& e){
        std::cerr << RED "Error: " << e.what() << RESET << std::endl;
        return (2);
    }
    return (ServerRunning());
}

int     Server::Handle_Message(Client &client)
{
    char    buf[1024];
    size_t     received;
    received = recv(client.getSocketFd(), buf, 1024, 0);
    if (received <= 0 && close(client.getSocketFd()))
        return (1);
    std::cout << std::endl << "response: " << buf << std::endl;
    if (client.getFAuth() == 1)
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
    Parse::PrintClientArgs(client);
    if (client.getFPass()== 1 && client.getNick() != "\0" && client.getUser() != "\0")
    {
        std::cout << GREEN "CLIENT AUTHENTICATE" << RESET << std::endl;
        client.setFAuth(1);
    }
}

int Server::Call_Functions(Client &client, char *buf, int received)
{
    std::vector<std::string> vec = Parse::ft_split(buf, received);
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
        client.setFPass(1);
    else
        client.setFPass(0);
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
