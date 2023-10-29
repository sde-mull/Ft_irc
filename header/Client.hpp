/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:54:17 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/25 15:50:53 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Lincludes.hpp"
#include "Parse.hpp"

class Client
{
	private:
	    int         _socketFd;
		std::string _user;
		std::string _nick;
		
	public:
		Client();
		Client(int fd);
		~Client();
		Client(Client const &src);
		Client & operator=(Client const &rhs);

		//getters
		int getSocketFd();
		std::string getUser();
		std::string getNick();

		//setters
		void setUser(std::string user);
		void setNick(std::string nick);

		//flags
		int			f_pass;
		int			f_user;
		int			f_nick;
		int   		f_auth;
};

#endif