/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_cmds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:53:31 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/10/31 16:54:07 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Lincludes.hpp"
#include "../header/Cinclude.hpp"

int	Privmsg_cmd(char *buf, Client client)
{
	std::string	buffer = Parse::strdup_aftspc(buf);
	std::string	message = buffer.substr(buffer.find_first_of(' ', 1) + 1, buffer.size());

	Parse::sendIrcMessage(message, client.getSocketFd());
}

int	Mode_cmd(char *buf, Client client)
{
	
}

int	Topic_cmd(char *buf, Client client)
{
	
}

int	Invite_cmd(char *buf, Client client)
{
	
}

int	Kick_cmd(char *buf, Client client)
{
	
}

int	Parse::Join_cmd(char *buf, Client client)
{
	std::string						buffer = strdup_aftspc(buf);
	std::string						ChannelName = buffer.substr(buffer.find_first_of(' ') + 1, buffer.find_first_of(' ', buffer.find_first_of(' ') + 1));
	std::vector<Channel>::iterator	ch_it = _Channels.begin();
	bool							exist = false;

	while (ch_it != _Channels.end())
	{
		if (ChannelName == ch_it->getName())
		{
			Parse::try_joining(ch_it, buffer, client);
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
	std::string	opts[6] = {"JOIN", "KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG"};
	int (*function[6])(char *buf, Client client) = {&Join_cmd, &Kick_cmd, &Invite_cmd, &Topic_cmd, &Mode_cmd, &Privmsg_cmd};
	std::string	buf_treated = strdup_tilspc(buf);

	for (int i = 0; i < 5; i++)
		if (buf_treated == opts[i])
			return (function[i](buf, *client));
	std::string	Buffer = buf;
	sendIrcMessage(Buffer, client->getSocketFd());
}