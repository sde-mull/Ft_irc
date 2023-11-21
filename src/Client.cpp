/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:57:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/21 16:13:23 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void){}

Client::Client(int id) : _socketFd(id),  _user("\0"), _nick("\0"), _f_pass(0), _f_auth(0){}

Client::~Client(void){}

Client::Client(Client const &src)
{
	*this = src;
}

Client& Client::operator=(const Client& rhs)
{
	this->_socketFd = rhs.GettersInt(GETCLIENTFD);
	this->_f_pass = rhs.GettersInt(GETPASS);
	this->_f_auth = rhs.GettersInt(GETAUTH);
	this->_user = rhs.Getters(GETUSER);
	this->_nick = rhs.Getters(GETNICK);

	return *this;
}

//Getters

std::string	Client::Getters(int opt) const
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

int Client::GettersInt(int opt) const
{
	switch(opt)
	{
		case GETCLIENTFD:
			return  _socketFd;
			break ;
		case GETAUTH:
			return _f_auth;
			break;
		case GETPASS:
			return _f_pass;
	}
	return 0;
}
//Setters

void Client::Setters(int opt, std::string str)
{
	switch(opt)
	{
		case SETUSER:
			this->_user = str;
			break ;
		case SETNICK:
			this->_nick = str; 
			break;
	}
}

void Client::SettersInt(int opt, int n)
{
	switch(opt)
	{
		case SETCLIENTFD:
			this->_socketFd = n;
			break ;
		case SETAUTH:
			this->_f_auth = n; 
			break;
		case SETPASS:
			this->_f_pass = n;
			break ;
	}
}