/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:49:22 by sde-mull          #+#    #+#             */
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
    Parse::printMessage("Binding Server Socket to IPv4 Address", YELLOW);  // Print binding message
    if (bind(this->_serverSocketFd, (struct sockaddr*)this->_address, sizeof(*(this->_address))) == -1)  // Bind socket to address
        throw FailedBind();  // Throw exception for bind failure
    Parse::printMessage("Bind Successful!", GREEN);  // Print success message
    if (listen(this->_serverSocketFd, 10) == -1)  // Listen for incoming connections
        throw FailedListen();  // Throw exception for listen failure
    Parse::printMessage("Server is listening...", GREEN);  // Print listening message
    return (0);  // Return success
}

void Server::creatingIPv4Address(void)
{
    Parse::printMessage("Creating IPv4 Address", YELLOW);  // Print address creation message
    struct sockaddr_in *address = static_cast<struct sockaddr_in*>(new struct sockaddr_in);  // Create IPv4 address
    address->sin_family = AF_INET;  // Set address family
    address->sin_port = htons(this->_port);  // Set port
    address->sin_addr.s_addr = INADDR_ANY;  // Set IP address to any available
    this->_address = address;  // Store the created address
    Parse::printMessage("IPv4 Address Created Successfully", GREEN);  // Print address creation success message
}

int Server::acceptConnection(void)
{
    struct sockaddr clientAddr;  // Create a structure for client address
    socklen_t clientAddrSize = sizeof(clientAddr);  // Get the size of the client address structure

    Parse::printMessage("Server is accepting a new client", YELLOW);  // Print message about accepting a client
    int newSocketFd = accept(this->_serverSocketFd, (struct sockaddr*)&clientAddr, &clientAddrSize);  // Accept a new client connection
    return (newSocketFd);  // Return the new socket file descriptor
}

void Server::CreatingSocket(int domain, int type, int protocol)
{
    int enable = 1;  // Enable address reuse

    this->_serverSocketFd = socket(domain, type, protocol);  // Create a server socket
    if (this->_serverSocketFd == -1)  // Check if socket creation failed
        throw FailedSocketCreation();  // Throw exception for failed socket creation

    Parse::printMessage("Server Socket Created Successfully!", GREEN);  // Print success message
    if (setsockopt(this->_serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)  // Set socket option for address reuse
        throw FailedSetSockopt();  // Throw exception for failed socket option setting
}

int Server::ServerRunning(void)
{
    fd_set ready_sockets;  // Define a set to hold ready sockets
    int client_socket;  // Declare a variable for the client socket
    int nbr_clients = 5;  // Initialize the number of clients

    FD_ZERO(&this->_currentSockets);  // Initialize the current socket set
    FD_SET(this->_serverSocketFd, &this->_currentSockets);  // Add the server socket to the current socket set

    while (true){
        ready_sockets = this->_currentSockets;  // Copy the current socket set to ready_sockets
        if (select(nbr_clients + 1, &ready_sockets, NULL, NULL, NULL) == -1){  // Use select to monitor sockets
            Parse::printErrorMessage("Select Failed", 2);  // Print an error message for select failure
            continue;  // Continue the loop
        }
        for (int i = 0; i <= nbr_clients; i++){
            if (FD_ISSET(i, &ready_sockets)){  // Check if a socket is ready
                if (i == this->_serverSocketFd){  // If it's the server socket
                    client_socket = acceptConnection();  // Accept a new client connection
                    if (client_socket == -1){  // Check for client accept failure
                        Parse::printErrorMessage("Failed to accept the new Client", 1);  // Print an error message
                        continue;  // Continue the loop
                    }
                    FD_SET(client_socket, &this->_currentSockets);  // Add the client socket to the current socket set
                    Parse::addClient(client_socket);  // Add the client to a data structure
                    Parse::printMessage("New Client Accepted", GREEN);  // Print a message about accepting a new client
                    if (client_socket > nbr_clients)  // Update the maximum number of clients
                        nbr_clients = client_socket;
                }
                else{  // If it's a client socket
                    if (Handle_Message(Parse::searchClientById(i)) == 1){
                        // Handle a message from a client (code for message handling is missing)
                    }
                }
            }
        }
    }
    return (0);  // Return success
}


/*
startConnection is a function to construct the sockets, creates an ipv4 address, binds and put it to listen. 
*/
int    Server::startConnection(void)
{
    try{
        Parse::printMessage("---------Initializing Server---------", GREEN); //print message in the terminal
        Parse::printMessage("Creating Server Socket", YELLOW); 
        CreatingSocket(AF_INET, SOCK_STREAM, 0); //Creates the server socket
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
    received = recv(client.GettersInt(GETCLIENTFD), buf, 1024, 0);
    if (received <= 0 && close(client.GettersInt(GETCLIENTFD)))
        return (1);
    if (client.GettersInt(GETAUTH) == 1)
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
    if (client.GettersInt(GETPASS) == 1 && client.Getters(GETNICK) != "\0" && client.Getters(GETUSER) != "\0")
    {
        std::cout << GREEN "CLIENT AUTHENTICATE" << RESET << std::endl;
        client.SettersInt(SETAUTH, 1);
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
        client.SettersInt(SETPASS, 1);
    else
        client.SettersInt(SETPASS, 0);
}

void    Server::ft_user(Client &client, std::string str)
{
    client.Setters(SETUSER, str);
}

void     Server::ft_nick(Client &client, std::string str)
{
    if (!Parse::CheckNickRules(str))
    {
        SendMsg(client, "\nBad Nick");
        return ;
    }
    if (!Parse::CheckClientByNick(str))
    {
        SendMsg(client, "\nNick Already Taken");
        return ;
    }
    client.Setters(SETNICK, str);  
}

void    Server::SendMsg(Client &client, const char *data)
{
    send(client.GettersInt(GETCLIENTFD), data, strlen(data), 0);
}

void    Server::PrintClientArgs(Client &client)
{
    if (client.GettersInt(GETPASS))
        SendMsg(client, "\nYou have set the correct password ✔\n");
    else
        SendMsg(client, "You have not set the correct password ✘\n");
    SendMsg(client, "This is your Nick: ");
    if (client.Getters(GETNICK) != "\0")
    {
        SendMsg(client, client.Getters(GETNICK).c_str());
        SendMsg(client," ✔\n");
    }  
    else
        SendMsg(client, " ✘\n");
    SendMsg(client, "This is your User: ");
    if (client.Getters(GETUSER) != "\0")
    {
        SendMsg(client, client.Getters(GETUSER).c_str());
        SendMsg(client," ✔\n");
    }
    else
        SendMsg(client, " ✘\n");
}