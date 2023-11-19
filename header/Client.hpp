/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:54:17 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/11 15:18:48 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Lincludes.hpp"

class Client
{
	private:
		int         _socketFd;
		std::string _user;
		std::string _nick;
		//flags
		int			_f_pass;
		int   		_f_auth;
		
	public:
		std::string	message;

		Client();
		Client(int id);
		~Client();
		Client(Client const &src);
		Client & operator=(Client const &rhs);

		//getters
		std::string	Getters(int	opt) const;
		int			GettersInt(int opt) const;

		//setters
		void		Setters(int opt, std::string str);
		void		SettersInt(int opt, int n);
};

#endif