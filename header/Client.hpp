/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 13:54:17 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/24 11:56:59 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Lincludes.hpp"

class Client
{
	private:

		int _socket_fd;
		struct sockaddr_in *_address;
		
	public:

		Client();
		Client(char *ip, int port);
		~Client();
		Client(Client const &src);
		Client & operator=(Client const &rhs);

		/* void Create_Socket();
		void Create_Address(char *ip, int port); */
		int	Connect_Socket();
		void Send(char *msg);
		void Receive();
};

#endif