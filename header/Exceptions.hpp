/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:18:24 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/06 23:47:43 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include "Lincludes.hpp"

class	FailedSocketCreation : public std::exception
{
	public:
		virtual const char* what() const throw();
};

class	FailedBind : public std::exception
{
	public:
		virtual const char* what() const throw();
};

class	FailedListen : public std::exception
{
	public:
		virtual const char* what() const throw();
};

class	FailedSelect : public std::exception
{
	public:
		virtual const char* what() const throw();
};

class	FailedSetSockopt : public std::exception
{
	public:
		virtual const char* what() const throw();
};

#endif