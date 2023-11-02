/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds_utils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:21:53 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/02 12:17:24 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Cinclude.hpp"

int	Parse::try_joining(std::vector<Channel>::iterator ch_it, std::string *buffer, Client client)
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

std::vector<std::string> Parse::Split_spc(char *buf)
{
	int							i = 0;
	int							j;
	std::vector<std::string>	ret;
	std::string					buffer;

	while (buf[i])
	{
		j = 0;
		while(buf[i] == ' ' && buf[i])
			i++;
		while (buf[i] != ' ' && buf[i])
			buffer[j++] = buf[i++];
		ret.push_back(buffer);
		buffer.clear();
	}
	return (ret);
}