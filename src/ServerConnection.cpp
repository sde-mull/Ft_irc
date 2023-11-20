/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConnection.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:43:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/19 23:34:44 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

//Server running system

int Server::bindAndListenServer(void)
{
	Parse::printMessage("Binding Server Socket to IPv4 Address", YELLOW);
	if (bind(this->_serverSocketFd, (struct sockaddr*)this->_address, sizeof(*(this->_address))) == -1)
		throw FailedBind();
	Parse::printMessage("Bind Successful!", GREEN);
	if (listen(this->_serverSocketFd, 10) == -1)
		throw FailedListen();
	Parse::printMessage("Server is listening...", GREEN);
	return 0;
}

void Server::creatingIPv4Address(void)
{
	Parse::printMessage("Creating IPv4 Address", YELLOW);
	struct sockaddr_in *address = static_cast<struct sockaddr_in*>(new struct sockaddr_in);
	address->sin_family = AF_INET;
	address->sin_port = htons(this->_port);
	address->sin_addr.s_addr = INADDR_ANY;
	this->_address = address;
	Parse::printMessage("IPv4 Address Created Successfully", GREEN);
}

int Server::acceptConnection(void)
{
	struct sockaddr clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);

	Parse::printMessage("Server is accepting a new client", YELLOW);
	int newSocketFd = accept(this->_serverSocketFd, (struct sockaddr*)&clientAddr, &clientAddrSize);
	return newSocketFd;
}

void Server::CreatingSocket(int domain, int type, int protocol)
{
	int enable = 1;

	this->_serverSocketFd = socket(domain, type, protocol);
	if (this->_serverSocketFd == -1)
		throw FailedSocketCreation();

	Parse::printMessage("Server Socket Created Successfully!", GREEN);
	if (setsockopt(this->_serverSocketFd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) == -1)
		throw FailedSetSockopt();
}

int Server::ConnectingClient(int &nbr_clients)
{
	int client_socket;

	client_socket = acceptConnection();
	if (client_socket == -1){
		Parse::printErrorMessage("Failed to accept the new Client", 1);
		return (-1);
	}
	FD_SET(client_socket, &this->_currentSockets);
	Parse::addClient(client_socket);
	Parse::printMessage("New Client Accepted", GREEN);
	if (client_socket > nbr_clients)
		nbr_clients = client_socket;
	return (0);
}

int Server::DisconnectingClient(int id)
{
	std::vector<std::string> users;
	Client &ClientDisconnecting = Parse::searchClientById(id);
	std::string ClientName = ClientDisconnecting.Getters(GETNICK);

	FD_CLR(id, &this->_currentSockets);
	Parse::RemoveClient(id);

	for (int i = 0; i < Parse::_Channels.size(); i++){
		Parse::_Channels[i].rmUser(ClientName);
		if (Parse::_Channels[i].getUserAmount() == 0)
			Parse::_Channels.erase(Parse::_Channels.begin() + i);
	}
	close(id);
	return (0);
}

int Server::ServerRunning(void)
{
	fd_set ready_sockets;
	int nbr_clients = 5;

	FD_ZERO(&this->_currentSockets);
	FD_SET(this->_serverSocketFd, &this->_currentSockets);

	while (true){
		ready_sockets = this->_currentSockets;
		if (select(nbr_clients + 1, &ready_sockets, NULL, NULL, NULL) == -1){
			Parse::printErrorMessage("Select Failed", 2);
			continue;
		}
		for (int i = 0; i <= nbr_clients; i++){
			if (FD_ISSET(i, &ready_sockets)){
				if (i == this->_serverSocketFd){
					if (ConnectingClient(nbr_clients) == -1)
						continue;
				}
				else{
					if (Handle_Message(Parse::searchClientById(i)) == -1){
						DisconnectingClient(i);
					}
				}
			}
		}
	}
	return 0;
}
