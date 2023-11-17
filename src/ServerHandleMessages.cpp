/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerHandleMessages.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:47:25 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/16 19:57:28 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int     Server::Handle_Message(Client &client)
{
	char    buf[8192];
	size_t     received;
	received = recv(client.GettersInt(GETCLIENTFD), buf, 1024, 0);
	// std::cout << "RESPONSE: " << buf << std::endl;
	if (received <= 0 || !strcmp(buf, "QUIT :Leaving\r\n"))
		return (-1);
	if (checkUserAuthentication(client, buf, received)){
		Parse::Handle_commands(buf, &client);
	}
	for (size_t i = 0; i < received; i++)
		buf[i] = '\0';
	return (0);
}