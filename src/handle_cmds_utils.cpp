/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds_utils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:21:53 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/10/31 17:07:07 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Lincludes.hpp"
#include "../header/Cinclude.hpp"

int	Parse::try_joining(std::vector<Channel>::iterator ch_it, std::string buffer, Client client)
{
	bool	F_banned;

	if (ch_it->Banneduser(client.Getters(GETUSER)) == 0)
		ch_it->addUser(client.Getters(GETUSER));
	else
		return (printErrorMessage("YOU ARE BANNED FROM THE CHANNEL!", 5));
}

int	Parse::sendIrcMessage(std::string message, int clientId)
{
	message = message + "\r\n";
	std::cout << "Sending message: " << message << std::endl;
	if (send(clientId, message.c_str(), message.length(), 0) == -1)
		exit(1);
	return 0;
}

std::string	Parse::strdup_tilspc(char *buf)
{
	std::string	ret;

	for (int i = 0; buf[i] != ' '; i++)
		ret[i] = buf[i];
	return (ret);
}

std::string	Parse::strdup_aftspc(char *buf)
{
	std::string	ret;
	int			i;

	while (buf[i] != ' ')
		i++;
	while (buf[i] == ' ')
		i++;
	for (int j = 0; buf[i] != '\0'; j++)
	{
		ret[j] = buf[i];
		i++;
	}
	return (ret);
}