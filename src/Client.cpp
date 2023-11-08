/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:57:01 by sde-mull          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void){}

Client::Client(int id) : _socketFd(id), _nick("\0"), _user("\0"), f_pass(0), f_auth(0){}

Client::~Client(void){}

Client::Client(Client const &src)
{
    *this = src;
}

Client& Client::operator=(const Client& rhs)
{
    this->_socketFd = rhs.getSocketFd();
    this->f_pass = rhs.getFPass();
    this->f_auth = rhs.getFAuth();
    this->_user = rhs.getUser();
    this->_nick = rhs.getNick();

    return *this;
}

//Getters

std::string	Client::Getters(int opt)
{
	switch(opt)
	{
		case GETNICK:
			return _nick;
			break ;
		case GETUSER:
			return _user;
			break;
	}
	return NULL;
}

int     Client::getSocketFd() const
{
    return (this->_socketFd);
}

std::string Client::getUser() const
{
    return (this->_user);
}

std::string Client::getNick() const
{
    return (this->_nick);
}

int     Client::getFAuth() const
{
    return (this->f_auth);
}

int     Client::getFPass() const
{
    return (this->f_pass);
}

//Setters

void Client::setUser(std::string user)
{
    this->_user = user;
}

void Client::setNick(std::string nick)
{
    this->_nick = nick;
}

void    Client::setSocketFd(int socketFd)
{
    this->_socketFd = socketFd;
}

void    Client::setFAuth(int f_auth)
{
    this->f_auth = f_auth;
}

void    Client::setFPass(int f_pass)
{
    this->f_pass = f_pass;
}