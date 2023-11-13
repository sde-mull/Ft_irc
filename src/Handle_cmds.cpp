/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_cmds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:53:31 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/13 17:24:04 by pcoimbra         ###   ########.fr       */
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

int	Parse::Mode_cmd(std::vector<std::string> buf, Client client)
{
	std::string	channel = buf[1];
	std::vector<Channel>::iterator	ch_it = _Channels.begin();

	if (channel.empty())
	{
		printErrorMessage("Error: No arg for target channel!", NOTENOUGHARGS);
		return 0;
	}
	else if (buf[2].empty())
	{
		ch_it->displayModes();
		return 1;
	}
	else if (buf[2].size() != 2 || (buf[2][0] != '-' && buf[2][0] != '+'))
	{
		printErrorMessage("Error: flag not correctly sent.", GENERICERROR);
		return 0;
	}
		
	char	mode = buf[2][1];
	
	while (ch_it->getName() != channel && ch_it != _Channels.end())
		ch_it++;
	if (ch_it == _Channels.end())
		printErrorMessage("Error: Channel not found!", NOCHANNELERR);
	else if (ch_it->getIsMod(client.Getters(GETUSER)) == 0)
		printErrorMessage("Error: You are not a moderator of this channel!", NOTENOUGHPERMSERR);
	else if (ch_it->getMode(mode) == -1)
		printErrorMessage("Error: That mode does not exist!", GENERICERROR);
	else
		return (ch_it->changeMode(mode, buf));
	return (0);
}

int	Parse::Topic_cmd(std::vector<std::string> buf, Client client)
{
	std::vector<Channel>::iterator	ch_it = _Channels.begin();

	while (ch_it != _Channels.end() && ch_it->getName() != buf[1])
		ch_it++;
	if (ch_it == _Channels.end())
		printErrorMessage("Error: Channel not found.", NOCHANNELERR);
	else if (ch_it->getMode(MODETOPIC) == 0 && ch_it->getIsMod(client.Getters(GETUSER)) == 0)
		printErrorMessage("Error: You are not a moderator of this channel and the channel is flagged to invite only.", NOTENOUGHPERMSERR);
	else if (ch_it->getIsUser(client.Getters(GETUSER)) == 0)
		printErrorMessage("Error: You must be an user in this channel.", GENERICERROR);
	else
	{
		if (ch_it->changeTopic(buf) == 0)
			printErrorMessage("Error: The topic couldnt be changed.", GENERICERROR);
		else
			return 1;
	}
	return (0);
}

int	Parse::Invite_cmd(std::vector<std::string> buf, Client client)
{
	std::vector<Channel>::iterator	ch_it = _Channels.begin();

	while (ch_it != _Channels.end() && ch_it->getName() != buf[2])
		ch_it++;
	if (ch_it == _Channels.end())
		printErrorMessage("Error: Channel not found.", NOCHANNELERR);
	else if (ch_it->getIsUser(client.Getters(GETUSER)) == 0)
		printErrorMessage("Error: You must be an user in this channel.", NOCHANNELERR);
	else if (ch_it->getMode(MODEINVITEONLY) == 1 && ch_it->getIsMod(client.Getters(GETUSER)) == 0)
		printErrorMessage("Error: You are not a moderator of this channel and the channel is flagged to invite only.", NOTENOUGHPERMSERR);
	else if (ch_it->getIsUser(buf[1]) == 1)
		printErrorMessage("Error: The invitee is already an user.", GENERICERROR);
	else
	{
		if (ch_it->inviteUser(buf[1]) == 0)
			printErrorMessage("Error: User is already invited.", GENERICERROR);
		else
			return 1;
	}
	return (0);
}

int	Parse::Kick_cmd(std::vector<std::string> buf, Client client)
{
	std::vector<Channel>::iterator	ch_it = _Channels.begin();

	while (ch_it != _Channels.end() && ch_it->getName() != buf[1])
		ch_it++;
	if (ch_it == _Channels.end())
		printErrorMessage("Error: Channel not found!", NOCHANNELERR);
	else if (ch_it->getIsMod(client.Getters(GETUSER)) == 0)
		printErrorMessage("Error: You are not a moderator of this channel!", NOTENOUGHPERMSERR);
	else if (ch_it->getIsUser(buf[2]) == 0)
		printErrorMessage("Error: There is no such user.", NOUSERERR);
	else if (ch_it->getIsMod(buf[2]) == 1 && (ch_it->getSuperUser() != client.Getters(GETUSER)))
		printErrorMessage("Error: The user you are trying to kick is also a mod.", NOTENOUGHPERMSERR);
	else
		return ch_it->rmUser(buf[2]);;
	return 0;
}

int	Parse::Join_cmd(std::vector<std::string> buf, Client client)
{
	std::string						ChannelName = buf[1];
	std::vector<Channel>::iterator	ch_it = _Channels.begin();
	// bool							exist = false;
	
	// while (ch_it != _Channels.end())
	// {
	// 	if (ChannelName == ch_it->getName())
	// 	{
	// 		exist = true;
	// 		if (Parse::try_joining(ch_it, buf, client) == 1)
	// 		{
	// 			std::cout << "joined channel!" << std::endl;
	// 			if (ch_it->getTopic() != "\0")
	// 				Parse::sendIrcMessage(":localhost 332 " + client.Getters(GETNICK) + " " + ch_it->getName() + " :" + ch_it->getTopic(), client.GettersInt(GETCLIENTFD));
	// 			else
	// 				Parse::sendIrcMessage(":localhost 331 " + client.Getters(GETNICK) + " " + ch_it->getName() + " :No topic is set", client.GettersInt(GETCLIENTFD));
	// 			exist = false;
	// 			return 1;
	// 		}
	// 		else
	// 		{
	// 			std::cout << "This channel is invite only and you are not invited!" << std::endl;
	// 			return 1;
	// 		}
	// 	}
	// 	ch_it++;
	// }
	// if (!exist)
	// {
	// 	Parse::_Channels.push_back(Channel(ChannelName, client.Getters(GETUSER)));
	// 	std::cout << "joined channel!" << std::endl;
	// 	return 1;
	// }

	while (ch_it != _Channels.end() && ch_it->getName() != ChannelName)
		ch_it++;
	if (ch_it == _Channels.end())
	{
		Parse::_Channels.push_back(Channel(ChannelName, client.Getters(GETUSER)));
		return 1;
	}
	else if (ch_it->getMode(MODEUSERLIMIT) == 1 && ch_it->getUserAmount() >= ch_it->getUserLimit())
		printErrorMessage("Error: Channel is already full.", GENERICERROR);
	else
		return (try_joining(ch_it, buf, client));
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
