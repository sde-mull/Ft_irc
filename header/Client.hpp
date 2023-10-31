/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:54:17 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/31 14:08:25 by sde-mull         ###   ########.fr       */
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
		~Client();
		Client(Client const &src);
		Client & operator=(Client const &rhs);

		//getters
		int 	getSocketFd() const;
		void	setSocketFd(int socktFd);
};

#endif