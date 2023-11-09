/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:54:17 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/09 18:03:05 by pcoimbra         ###   ########.fr       */
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
		
	public:
		Client();
		Client(int id);
		~Client();
		Client(Client const &src);
		Client & operator=(Client const &rhs);

		//getters
		std::string	Getters(int	option);

		std::string getUser();
		std::string getNick();

		//setters
		void setUser(std::string user);
		void setNick(std::string nick);

		//flags
		int			f_pass;
		int   		f_auth;

		int 	getSocketFd() const;
		void	setSocketFd(int socktFd);
};

#endif