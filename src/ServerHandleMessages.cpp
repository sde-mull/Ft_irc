/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandleMessages.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:47:25 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/19 13:36:50 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::shut_the_duck_up()
{
	std::cout << "STFU" << std::endl;
	delete this->_address;
	this->m.clear();
	exit(0);
}

int     Server::Handle_Message(Client &client)
{
	char    buf[MAXBUFF];
	size_t     received;
	received = recv(client.GettersInt(GETCLIENTFD), buf, MAXBUFF, 0);

	if (received < MAXBUFF)
		buf[received + 1] = 0;
	else
		buf[received] = 0;
	//std::cout << "RESPONSE: " << buf << std::endl;
	if (received <= 0 || !strcmp(buf, "QUIT :Leaving\r\n"))
		return (-1);
	if (!strncmp(buf, "SHUTDOWN", 8))
		shut_the_duck_up();
	if (checkUserAuthentication(client, buf, received)){
		Parse::Handle_commands(buf, &client);
	}
	for (size_t i = 0; i < received; i++)
		buf[i] = '\0';
	return (0);
}