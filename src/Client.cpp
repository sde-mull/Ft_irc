/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:57:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/31 16:41:50 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(void)
{
    std::cout << B_GREEN "Client default contrutor called" RESET << std::endl;
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