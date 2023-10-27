/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:57:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/25 15:51:40 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void)
{
    std::cout << B_GREEN "Client default contrutor called" RESET << std::endl;
}

Client::Client(int fd)
{
    std::cout << B_GREEN "Client fd contrutor called" RESET << std::endl;
    this->_socketFd = fd;
    this->f_pass = 0;
    this->f_nick = 0;
    this->f_user = 0;
}

Client::~Client(void)
{
    std::cout << B_RED "Client destructor called" RESET << std::endl;
}

Client::Client(Client const &src)
{
    *this = src;
}

Client & Client::operator=(Client const &rhs)
{
    (void)rhs;
    return (*this);
}

int Client::getSocketFd()
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
