/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandleMessages.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:47:25 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/22 12:37:14 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::shut_the_duck_up()
{
	delete this->_address;
	this->m.clear();
	exit(0);
}

bool	Server::ConstructMessage(char *buf, int received, Client &client)
{
    client.message.append(buf, received);

    if (!client.message.empty() && client.message[client.message.size() - 1] == '\n') {
        return true;
    }
    return false;
}

int     Server::Handle_Message(Client &client)
{
	char    buf[MAXBUFF];
	size_t     received;
	received = recv(client.GettersInt(GETCLIENTFD), buf, MAXBUFF, 0);

	if (received <= 0 || !strcmp(buf, "QUIT :Leaving\r\n"))
		return (-1);
	if (!ConstructMessage(buf, received, client))
		return (2);
	std::copy(client.message.begin(), client.message.end(), buf);

	if (!strncmp(buf, "SHUTDOWN", 8))
		shut_the_duck_up();
	if (checkUserAuthentication(client, buf, client.message.size())){
		Parse::Handle_commands(buf, &client);
	}
	std::fill(buf, buf + MAXBUFF, 0);
	client.message.clear();
	return (0);
}