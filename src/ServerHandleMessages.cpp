/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleMessages.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:47:25 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/09 20:47:32 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int     Server::Handle_Message(Client &client)
{
	char    buf[1024];
	size_t     received;
	received = recv(client.GettersInt(GETCLIENTFD), buf, 1024, 0);
	if (received <= 0)
		return (-1);
	if (client.GettersInt(GETAUTH) == 1)
		return (0);
	else
		Client_Authenticate(client, buf, received);
	for (size_t i = 0; i < received; i++)
		buf[i] = '\0';
	return (0);
}