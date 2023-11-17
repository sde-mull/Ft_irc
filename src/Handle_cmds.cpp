/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_cmds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:53:31 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/17 14:21:39 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cinclude.hpp"

std::vector<Channel> Parse::_Channels;

int	Privmsg_cmd(std::vector<std::string> buf, Client client)
{
	std::string	message;
	std::string target = buf[1];

	if (!Parse::CheckPrivMessageArguments(client, buf.size(), "\"" + buf[0] + " " + buf[1] + "\""))
		return (1);

	std::vector<int> allTargetsID = Parse::ReturnMessageTargets(target, client);
	for (int i = 2; i < buf.size(); i++)
		message = message + buf[i] + ' ';
	if (message[0] == ':')
    	message.erase(0, 1);
	for (int i = 0; i < allTargetsID.size(); i++)
		Parse::sendIrcMessage(":" + client.Getters(GETNICK) + "!" + client.Getters(GETUSER) + "@localhost PRIVMSG " + target + " " + message, allTargetsID[i]);
	return(0);
}

int	Parse::Mode_cmd(std::vector<std::string> buf, Client client)
{
	std::vector<Channel>::iterator	ch_it = _Channels.begin();

	while (ch_it != _Channels.end() && ch_it->getName() != buf[1])
		ch_it++;
	if (ch_it == _Channels.end())
	{
		printErrorMessage("Channel not found", GENERICERROR);
		return 0;
	}
	else if (buf.size() == 2)
	{
		if (ch_it->getIsUser(client.Getters(GETNICK)) == 0)
			printErrorMessage("You must be an user in this channel.", GENERICERROR);
		ch_it->displayModes();
		return 1;
	}
	else if (buf[2].size() > 2 || (buf[2][0] != '-' && buf[2][0] != '+'))
	{
		printErrorMessage("Bad args", GENERICERROR);
		return 0;
	}
	
	if (ch_it->getIsMod(client.Getters(GETNICK)) == 0)
		printErrorMessage("You are not a moderator of this channel!", NOTENOUGHPERMSERR);
	else if (ch_it->getMode(buf[2][1]) == -1)
		printErrorMessage("That mode does not exist!", GENERICERROR);
	else
		return (ch_it->changeMode(buf[2][1], buf));
	return (0);
}

int	Parse::Topic_cmd(std::vector<std::string> buf, Client client)
{
	std::vector<Channel>::iterator	ch_it = _Channels.begin();

	while (ch_it != _Channels.end() && ch_it->getName() != buf[1])
		ch_it++;
	if (ch_it == _Channels.end())
		printErrorMessage("Channel not found.", NOCHANNELERR);
	else if(buf.size() == 2)
	{
		if (ch_it->getIsUser(client.Getters(GETNICK)) == 0)
			printErrorMessage("You must be an user in this channel.", GENERICERROR);
		sendIrcMessage(ch_it->getTopic(), client.GettersInt(GETCLIENTFD));
		return 1;
	}
	else if (ch_it->getMode(MODETOPIC) == 0 && ch_it->getIsMod(client.Getters(GETNICK)) == 0)
		printErrorMessage("You are not a moderator of this channel.", NOTENOUGHPERMSERR);
	else if (ch_it->getIsUser(client.Getters(GETNICK)) == 0)
		printErrorMessage("You must be an user in this channel.", GENERICERROR);
	else
	{
		if (ch_it->changeTopic(buf) == 0)
			printErrorMessage("The topic couldnt be changed.", GENERICERROR);
		else
		{
			Parse::BroadcastChannel(2, "332", " " + buf[2], client, &(*ch_it));
			return 1;
		}
	}
	return (0);
}

int	Parse::Invite_cmd(std::vector<std::string> buf, Client client)
{
	std::string	channel_name = buf[2];
	std::vector<Channel>::iterator	ch_it = _Channels.begin();
	Client *invitedUser = Parse::ReturnClientByNick(buf[1]);
 
	while (ch_it != _Channels.end() && ch_it->getName() != channel_name)
		ch_it++;
	if (buf.size() < 3)
		sendIrcNumeric(1, "461", buf[0] + " :Not enough parameters", client);
	else if (ch_it == _Channels.end())
		sendIrcNumeric(1, "403", channel_name + " :No such channel", client);
	else if (ch_it->getIsUser(client.Getters(GETNICK)) == 0)
		sendIrcNumeric(2, "442", " :You're not on that channel", client, &(*ch_it));
	else if (ch_it->getIsMod(client.Getters(GETNICK)) == 0)
		sendIrcNumeric(2, "482", " :You're not channel operator", client, &(*ch_it));
	else if (ch_it->getIsUser(buf[1]) == 1)
		sendIrcNumeric(1, "443 ", buf[1] + " " + channel_name + " :is already on channel", client);
	else if (!Parse::CheckClientByNick(buf[1]))
		sendIrcNumeric(1, "401", " " + buf[1] + " :No such nick", client);
		
	else
	{
		Parse::sendIrcMessage(":localhost 341 " + client.Getters(GETNICK) + " " + buf[1] + " " + (*ch_it).getName(), client.GettersInt(GETCLIENTFD));
		Parse::sendIrcMessage(":" + client.Getters(GETNICK) + "!" + client.Getters(GETUSER) + "@localhost NOTICE " + buf[1] + " you have been invited to join " + (*ch_it).getName(), invitedUser->GettersInt(GETCLIENTFD));
		return 1;
	}
	return (0);
}

int	Parse::Kick_cmd(std::vector<std::string> buf, Client client)
{
	std::string	channel_name = buf[1];
	std::vector<Channel>::iterator	ch_it = _Channels.begin();

	while (ch_it != _Channels.end() && ch_it->getName() != channel_name)
		ch_it++;
	if (ch_it != _Channels.end())
	if (buf.size() < 3)
		sendIrcNumeric(1, "461", buf[0] + " :Not enough parameters", client);
	else if (ch_it == _Channels.end())
		sendIrcNumeric(1, "403", channel_name + " :No such channel", client);
	else if (ch_it->getIsUser(client.Getters(GETNICK)) == 0)
		sendIrcNumeric(2, "442", " :You're not on that channel", client, &(*ch_it));
	else if (ch_it->getIsMod(client.Getters(GETNICK)) == 0)
		sendIrcNumeric(2, "482", " :You're not channel operator", client, &(*ch_it));
	else if (!Parse::CheckClientByNick(buf[2]))
	{
		std::cout << "HELLO" << std::endl;
		sendIrcNumeric(1, "401", " " + channel_name + " :No such nick", client);
	}
	else if (ch_it->getIsUser(buf[2]) == 0)
		sendIrcNumeric(1, "441", buf[2] + " " + channel_name + " :They aren't on that channel", client);
	else
	{
		std::vector<std::string> users = ch_it->getUsers();
		for(int j = 0; j < users.size(); j++)
			Parse::sendIrcMessage(":" + client.Getters(GETNICK) + " KICK " + channel_name + " " + buf[2] + " :No reason Given", (Parse::ReturnClientByNick(users[j]))->GettersInt(GETCLIENTFD));
		return ch_it->rmUser(buf[2]);
	}
	return 0;
}

int	Parse::Join_cmd(std::vector<std::string> buf, Client client)
{
	std::string						ChannelName = buf[1];
	std::vector<Channel>::iterator	ch_it = _Channels.begin();
	
	if (buf[1][0] != '#' || buf[1].size() == 1)
		return printErrorMessage("JOIN #<Channelname>.", WRONGARGSERR);
	while (ch_it != _Channels.end() && ch_it->getName() != ChannelName)
		ch_it++;
	if (ch_it == _Channels.end())
	{
		Parse::_Channels.push_back(Channel(ChannelName, client.Getters(GETNICK)));
		Channel channel = _Channels.back();
    	Parse::sendIrcNumeric(3, "", "", client, &channel);
		Parse::sendIrcNumeric(2, "331", " :No topic is set", client, &channel);
		Parse::BroadcastChannel(1, "353", PrefixString(client, channel), client, &channel);
		Parse::BroadcastChannel(2, "366", " :End of NAMES list", client, &channel);
		Parse::sendIrcMessage(":localhost 324 " + channel.getName() + channel.getModeString(), client.GettersInt(GETCLIENTFD));
		return 1;
	}
	else if (ch_it->getMode(MODEUSERLIMIT) == 1 && ch_it->getUserAmount() >= ch_it->getUserLimit())
		Parse::sendIrcNumeric(2, "471", " :Cannot join channel (+l)", client, &(*ch_it));
	else if (ch_it->getMode(MODEINVITEONLY) == 1 && !ch_it->CheckInvite(client.Getters(GETNICK)))
		Parse::sendIrcNumeric(2, "473", " :Cannot join channel (+i)", client, &(*ch_it));
	else if (ch_it->getMode(MODEPASSWORD) == 1 && buf.size() < 3 && ch_it->getIsInvited(client.Getters(GETNICK)) == 0)
		Parse::sendIrcNumeric(2, "461", " :Not enough parameters (+k)", client, &(*ch_it)); // pls check
	else if (ch_it->check_pass(buf[2]) == 0 && ch_it->CheckInvite(client.Getters(GETNICK)) == 0)
		Parse::sendIrcNumeric(2, "475", " :Cannot join channel (+k)", client, &(*ch_it)); // pls check
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
	if (Parse::CheckClientByNick(str))
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
	Parse::BroadcastWho(client, &(*ch_it));
	Parse::sendIrcNumeric(2, "315", " :End of WHO list", client, &(*ch_it));
	return (0);
}

int	Parse::Handle_commands(char *buf, Client *client)
{
	std::string					opts[9] = {"JOIN", "KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG", "NICK", "WHO"};
	int 						(*function[9])(std::vector<std::string> buf, Client client)	= {&Join_cmd, &Kick_cmd, &Invite_cmd, &Topic_cmd, &Mode_cmd, &Privmsg_cmd, &Nick_cmd, &Who_cmd};
	std::vector<std::string>	parsed_buffer = Parse::Hander_ft_split(buf, strlen(buf));
	std::string	message;

	if (!buf)
	{
		std::cout << RED << "No buffer in Handle_commands" << std::endl;
		return 0;
	}
	for (int i = 0; i < 9; i++)
	{
		if (parsed_buffer[0] == opts[i])
		{
			if (parsed_buffer.size() == 1)
			{
				Parse::sendIrcNumeric(1, "461", " " +  parsed_buffer[0] + " :Not enough parameters", *client);
				return 0;
			}
			else
				return (function[i](parsed_buffer, *client));
		}
	}
	std::string str(buf);
	str.erase(str.begin() + str.find_last_of('\n'));
	Parse::sendIrcNumeric(1, "421", " " + str + " :Unknown command", *client);
	return (0);
}
