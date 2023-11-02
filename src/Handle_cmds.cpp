/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_cmds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:53:31 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/02 12:16:49 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Cinclude.hpp"

int	Privmsg_cmd(std::vector<std::string> buf, Client client)
{
	std::string	message;

	for (int i = 2; i < buf.size(); i++)
		message = message + ' ' + buf[i];

	Parse::sendIrcMessage(message, client.getSocketFd());
}

int	Mode_cmd(std::vector<std::string> buf, Client client)
{
	
}

int	Topic_cmd(std::vector<std::string> buf, Client client)
{
	
}

int	Invite_cmd(std::vector<std::string> buf, Client client)
{
	
}

int	Kick_cmd(std::vector<std::string> buf, Client client)
{
	
}

int	Parse::Join_cmd(std::vector<std::string> buf, Client client)
{
	std::string						ChannelName = buf[1];
	std::vector<Channel>::iterator	ch_it = _Channels.begin();
	bool							exist = false;

	while (ch_it != _Channels.end())
	{
		if (ChannelName == ch_it->getName())
		{
			Parse::try_joining(ch_it, buf, client);
			exist = true;
		}
		ch_it++;
	}
	if (!exist)
		Parse::_Channels.push_back(Channel(ChannelName, client.Getters(GETUSER)));
}

int	Parse::Handle_commands(char *buf, Client *client)
{
	if (!buf)
	{
		std::cout << RED << "No buffer in Handle_commands" << std::endl;
		return 0;
	}
	std::string									opts[6] = {"JOIN", "KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG"};
	int (*function[6])(std::vector<std::string> buf, Client client) = {&Join_cmd, &Kick_cmd, &Invite_cmd, &Topic_cmd, &Mode_cmd, &Privmsg_cmd};
	std::vector<std::string>					parsed_buffer = Parse::Split_spc(buf);

	for (int i = 0; i < 5; i++)
		if (parsed_buffer[0] == opts[i])
			return (function[i](parsed_buffer, *client));
	std::string	Buffer = buf;
	sendIrcMessage(Buffer, client->getSocketFd());
}