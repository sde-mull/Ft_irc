/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:18:40 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/06 23:48:14 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Exceptions.hpp"

/*
Exceptions used to send specific type of messages inside a try catch block
*/

const char* FailedSocketCreation::what() const throw()
{
	return ("Failed to create the socket!");
}

const char* FailedBind::what() const throw()
{
	return ("Failed to bind server socket to IPv4 address");
}

const char* FailedListen::what() const throw()
{
	return ("Failed to Listen");
}

const char* FailedSelect::what() const throw()
{
	return ("Select Failed");
}

const char* FailedSetSockopt::what() const throw()
{
	return ("Failed setting SO_REUSEADDR");
}