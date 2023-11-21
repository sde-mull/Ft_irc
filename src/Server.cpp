/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:49:22 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/21 16:21:59 by pcoimbra         ###   ########.fr       */
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
	this->_port = rhs.getPort();
	this->_password = rhs.getPassword();
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

/*
startConnection is a function to construct the sockets, creates an ipv4 address, binds and put it to listen. 
*/
int    Server::startConnection(void)
{
	try{
		Parse::printMessage("---------Initializing Server---------", GREEN); //print message in the terminal
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