/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_cmds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:53:31 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/14 15:38:11 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cinclude.hpp"

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
	else if (buf.size() == 2)
	{
		ch_it->displayModes();
		return 1;
	}
	else if (buf[2].size() != 2 || (buf[2][0] != '-' && buf[2][0] != '+'))
	{
		std::string testing = "ERROR:" + buf[2];
		printErrorMessage(testing, GENERICERROR);
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
		{
			Parse::BroadcastChannel(2, "332", " " + buf[2], client, &(*ch_it), 0);
			return 1;
		}
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
		{
			Parse::sendIrcMessage(":localhost 341 " + client.Getters(GETNICK) + " " + (*ch_it).getName(), client.GettersInt(GETCLIENTFD));
			return 1;
		}
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
	
  
	while (ch_it != _Channels.end() && ch_it->getName() != ChannelName)
		ch_it++;
	if (ch_it == _Channels.end())
	{
		Parse::_Channels.push_back(Channel(ChannelName, client.Getters(GETUSER)));
		Channel channel = _Channels.back();
    	Parse::sendIrcNumeric(3, "", "", client, &channel);
		Parse::sendIrcNumeric(2, "331", " :No topic is set", client, &channel);
		Parse::BroadcastChannel(1, "353", PrefixString(client, channel), client, &channel, 0);
		Parse::BroadcastChannel(2, "366", " :End of NAMES list", client, &channel, 0);
		Parse::sendIrcMessage(":localhost 324 " + channel.getName() + channel.getModeString(), client.GettersInt(GETCLIENTFD));
		return 1;
	}
	else if (ch_it->getMode(MODEUSERLIMIT) == 1 && ch_it->getUserAmount() >= ch_it->getUserLimit())
		printErrorMessage("Error: Channel is already full.", GENERICERROR);
	else
		return (try_joining(ch_it, buf, client));
	return 0;
}

int	Parse::Nick_cmd(std::vector<std::string> buf, Client client)
{
	std::string str = buf[1];
	if (!Parse::CheckNickRules(str))
	{
		Parse::sendIrcNumeric(1, "432", ":Erroneus nickname", client);
		return 0;
	}
	if (!Parse::CheckClientByNick(str))
	{
		Parse::sendIrcNumeric(1, "433", " :Nickname is already in use", client);
		return 0;
	}
	Parse::sendIrcMessage(":" + client.Getters(GETNICK) + " NICK :" + str, client.GettersInt(GETCLIENTFD));
	client.Setters(SETNICK, str);
	return 0;
}

int Parse::Who_cmd(std::vector<std::string> buf, Client client)
{
	std::string						ChannelName = buf[1];
	std::vector<Channel>::iterator	ch_it = _Channels.begin();

	while (ch_it != _Channels.end() && ch_it->getName() != ChannelName)
		ch_it++;
	//std::string flag = " H" + ch_it->getPrefix(client.Getters(GETNICK)) + " :1 ";
	//std::cout << "flag: " << flag << std::endl;
	//std::cout << "getprefix: " << ch_it->getPrefix(client.Getters(GETNICK)) << std::endl;
	Parse::BroadcastWho(client, &(*ch_it));
	Parse::sendIrcNumeric(2, "315", " :End of WHO list", client, &(*ch_it));
	return (0);
}

int	Parse::Handle_commands(char *buf, Client *client)
{
	std::string					opts[8] = {"JOIN", "KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG", "NICK", "WHO"};
	int 						(*function[8])(std::vector<std::string> buf, Client client)	= {&Join_cmd, &Kick_cmd, &Invite_cmd, &Topic_cmd, &Mode_cmd, &Privmsg_cmd, &Nick_cmd, &Who_cmd};
	std::vector<std::string>	parsed_buffer = Parse::ft_split(buf, strlen(buf));
	std::string	message;

	if (!buf)
	{
		std::cout << RED << "No buffer in Handle_commands" << std::endl;
		return 0;
	}
	for (int i = 0; i < 8; i++)
	{\
		if (parsed_buffer[0] == opts[i])
		{
			if (parsed_buffer.size() == 1)
				Parse::sendIrcNumeric(1, "461", " " +  parsed_buffer[0] + " :Not enough parameters", *client);
			else
				return (function[i](parsed_buffer, *client));
		}
	}
	std::string str(buf);
	str.erase(str.begin() + str.find_last_of('\n'));
	Parse::sendIrcNumeric(1, "421", " " + str + " :Unknown command", *client);
	/* std::vector<std::string>::iterator Ite = parsed_buffer.begin();
	for (Ite; Ite != parsed_buffer.end(); Ite++)
		message = message + ' ' + *Ite;
	sendIrcMessage(message, client->GettersInt(GETCLIENTFD)); */
	return (0);
}
