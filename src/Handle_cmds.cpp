/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_cmds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:53:31 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/11 16:59:03 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

std::vector<Channel> Parse::_Channels;

int	Privmsg_cmd(std::vector<std::string> buf, Client client)
{
	std::string	message;
	std::vector<std::string>::iterator Ite = buf.begin();

	std::advance(Ite, 2);
	for (Ite; Ite != buf.end(); Ite++)
		message = message + ' ' + *Ite;

	Parse::sendIrcMessage(message, client.GettersInt(GETCLIENTFD));
	return(0);
}

int	Mode_cmd(std::vector<std::string> buf, Client client)
{
	return (0);
}

int	Topic_cmd(std::vector<std::string> buf, Client client)
{
	return (0);
}

int	Invite_cmd(std::vector<std::string> buf, Client client)
{
	return (0);
}

int	Parse::Kick_cmd(std::vector<std::string> buf, Client client)
{
	std::vector<Channel>::iterator	ch_it = _Channels.begin();

	while (ch_it != _Channels.end() && ch_it->getName() != buf[1])
		ch_it++;
	if (ch_it == _Channels.end())
		printErrorMessage("Error: Channel not found!", NOCHERR);
	else if (ch_it->IsUserMod(client.Getters(GETUSER)) == 0)
		printErrorMessage("Error: You are not a moderator of this channel!", NOMODERR);
	else if (ch_it->SearchForUser(buf[2]) == 0)
		printErrorMessage("Error: There is no such user.", NOUSERERR);
	else if (ch_it->IsUserMod(buf[2]) == 1 && (ch_it->getSuperUser() != client.Getters(GETUSER)))
		printErrorMessage("Error: The user you are trying to kick is also a mod.", NOTENOUGHPERMSERR);
	else
		ch_it->rmUser(buf[2]);
	return 0;
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
			exist = true;
			if (Parse::try_joining(ch_it, buf, client) == 1)
			{
				if (ch_it->getTopic() != "\0")
					Parse::sendIrcMessage(":localhost 332 " + client.Getters(GETNICK) + " " + ch_it->getName() + " :" + ch_it->getTopic(), client.GettersInt(GETCLIENTFD));
				else
					Parse::sendIrcMessage(":localhost 331 " + client.Getters(GETNICK) + " " + ch_it->getName() + " :No topic is set", client.GettersInt(GETCLIENTFD));
				exist = false;
				return 1;
			}
			else
			{
				std::cout << "This channel is invite only and you are not invited!" << std::endl;
				return 1;
			}
		}
		ch_it++;
	}
	if (!exist) //":" + client.Getters(GETNICK) + "!" + client.Getters(GETUSER) + "@localhost JOIN " + channel.getName()
	{
		Parse::_Channels.push_back(Channel(ChannelName, client.Getters(GETUSER)));
		Channel channel = _Channels.back();
		Parse::sendIrcMessage(Parse::SendCommandIRC("", client, channel, "", 3), client.GettersInt(GETCLIENTFD));
		Parse::sendIrcMessage(Parse::SendCommandIRC("331", client, channel, " :No topic is set", 1), client.GettersInt(GETCLIENTFD));
		Parse::sendIrcMessage(Parse::SendCommandIRC("353", client, channel, " :" + channel.getPrefix(client.Getters(GETUSER)) + client.Getters(GETUSER), 2), client.GettersInt(GETCLIENTFD));
		Parse::sendIrcMessage(Parse::SendCommandIRC("366", client, channel, " :End of NAMES list", 1), client.GettersInt(GETCLIENTFD));
		Parse::sendIrcMessage(Parse::SendCommandIRC("324", client, channel, channel.getModeString(), 1), client.GettersInt(GETCLIENTFD));
		Parse::sendIrcMessage(Parse::SendCommandIRC("315", client, channel, " :End of WHO list", 1), client.GettersInt(GETCLIENTFD));
		return 1;
	}
		
	return 0;
}

int	Parse::Handle_commands(char *buf, Client *client)
{
	std::string					opts[6] = {"JOIN", "KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG"};
	int 						(*function[6])(std::vector<std::string> buf, Client client)	= {&Join_cmd, &Kick_cmd, &Invite_cmd, &Topic_cmd, &Mode_cmd, &Privmsg_cmd};
	std::vector<std::string>	parsed_buffer = Parse::ft_split(buf, strlen(buf));
	std::string	message;
	
	if (!buf)
	{
		std::cout << RED << "No buffer in Handle_commands" << std::endl;
		return 0;
	}
	for (int i = 0; i < 5; i++)
		if (parsed_buffer[0] == opts[i])
			return (function[i](parsed_buffer, *client));

	std::vector<std::string>::iterator Ite = parsed_buffer.begin();
	std::advance(Ite, 2);
	for (Ite; Ite != parsed_buffer.end(); Ite++)
		message = message + ' ' + *Ite;
	sendIrcMessage(message, client->GettersInt(GETCLIENTFD));
	return (0);
}
