/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:57:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/01 18:51:31 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void)
{
    std::cout << B_GREEN "Client default contrutor called" RESET << std::endl;
}


Client::Client(int id) : _socketFd(id), _nick("\0"), _user("\0"), f_pass(0), f_auth(0)
{
    std::cout << B_GREEN "Client id contrutor called" RESET << std::endl;
}

Client::~Client(void)
{
    std::cout << B_RED "Client destructor called" RESET << std::endl;
}

Client::Client(Client const &src)
{
    *this = src;
}

Client& Client::operator=(const Client& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    _socketFd = rhs._socketFd;
    _user = rhs._user;
    _nick = rhs._nick;

    return *this;
}

int     Client::getSocketFd() const
{
    return (this->_socketFd);
}

std::string Client::getUser()
{
    return (this->_user);
}

std::string Client::getNick()
{
    return (this->_nick);
}

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
