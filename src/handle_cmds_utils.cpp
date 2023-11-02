/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds_utils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:21:53 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/02 17:25:38 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cinclude.hpp"

int	Parse::try_joining(std::vector<Channel>::iterator ch_it, std::vector<std::string> buffer, Client client)
{
	bool	F_banned;

	if (mode invite only is on)
		
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
		while((buf[i] == ' ' || buf[i] == '\r') && buf[i])
			i++;
		while (buf[i] != ' ' && buf[i])
			buffer[j++] = buf[i++];
		ret.push_back(buffer);
		buffer.clear();
	}
	return (ret);
}