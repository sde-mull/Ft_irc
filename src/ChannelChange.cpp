/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelChange.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:21:07 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/21 16:24:39 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

void	Channel::setPassword(std::string pass)
{
	if (pass == "\0")
		_password.clear();
	_password = pass;
}

int	Channel::changeMode(std::vector<std::string> buf, Client client)
{
	std::map<char, int>::iterator	ite;
	char							mode = buf[2][1];

	for (ite = _modes.begin(); ite != _modes.end(); ite++)
	{
		if (ite->first == mode)
		{
			if (mode == MODEINVITEONLY || mode == MODETOPIC)
			{
				if (buf[2][0] == '+' && ite->second == 0)
					ite->second = 1;
				else if (buf[2][0] == '-' && ite->second == 1)
					ite->second = 0;
				return 0;
			}
			else
				break;
		}
	}
	if	(mode == MODEPASSWORD)
		return mode_password(buf, ite, client);
	else if (mode == MODECHANNELOP)
		return mode_addmod(buf, client);
	else if (mode == MODEUSERLIMIT)
		return mode_userlimit(buf, ite, client);
	return 0;
}

int	Channel::changeTopic(std::vector<std::string> buf)
{
	std::string	topic;
	std::vector<std::string>::iterator ite;

	ite = buf.begin();
	topic = buf[2];
	std::advance(ite, 3);
	for (; ite != buf.end(); ite++)
		topic = topic + " " + *ite;
	_topic = topic;
	return 1;
}

int	Channel::changePrefix(std::string user, char c)
{
	std::map<std::string, std::string>::iterator ite = _uprefix.find(user);

	if (ite != _uprefix.end())
	{
		switch(c)
		{
			case '+':
				_uprefix[user] = "+";
				break;
			case '@':
				_uprefix[user] = "@";
				break;
			default:
				_uprefix.erase(ite);
		}
		return 1;
	}
	return 0;
}

int		Channel::invitedUsers(std::string user)
{
	std::vector<std::string>::iterator ite = std::find(_invitedUsers.begin(), _invitedUsers.end(), user);

	if (ite == _invitedUsers.end())
		return (0);
	else
		ite = _invitedUsers.erase(ite);
	return 1;
}

int	Channel::ChangeNickUserList(std::string newNick, Client client)
{
	std::vector<std::string>::iterator ite = std::find(_users.begin(), _users.end(), client.Getters(GETNICK));

	
	if (ite == _users.end())
		return 0;
	else
		*ite = newNick;
	return 1;
}

void	Channel::ChangeNickModsList(std::string newNick, Client client)
{
	for (unsigned long i = 0; i < this->_mods.size(); i++)
	{
		if (!this->_mods[i].compare(client.Getters(GETNICK)))
			this->_mods[i] = newNick;
	}
}

void	Channel::ChangeNickInvitedList(std::string newNick, Client client)
{
	for (unsigned long i = 0; i < this->_invitedUsers.size(); i++)
	{
		if (!this->_invitedUsers[i].compare(client.Getters(GETNICK)))
			this->_invitedUsers[i] = newNick;
	}
}

void Channel::ChangeNickPrefixList(std::string newNick, Client client)
{
    std::string oldNick = client.Getters(GETNICK);

    for (std::map<std::string, std::string>::iterator it = this->_uprefix.begin(); it != this->_uprefix.end(); ++it)
    {
        if (it->first == oldNick)
        {
            std::string oldValue = it->second;

            this->_uprefix.erase(it);

            this->_uprefix[newNick] = oldValue;
        }
    }
}

