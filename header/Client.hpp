/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:54:17 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/01 18:51:05 by sde-mull         ###   ########.fr       */
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
		//flags
		int			f_pass;
		int   		f_auth;
		
	public:
		Client();
		Client(int id);
		~Client();
		Client(Client const &src);
		Client & operator=(Client const &rhs);

		//getters
		std::string	Getters(int	option);

		std::string getUser() const;
		std::string getNick() const;
		int 		getSocketFd() const;
		int     	getFAuth() const;
		int     	getFPass() const;

		//setters
		void 		setUser(std::string user);
		void 		setNick(std::string nick);
		void		setSocketFd(int socktFd);
		void    	setFAuth(int f_auth);
		void    	setFPass(int f_pass);
};

#endif