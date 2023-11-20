/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelChange.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:21:07 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/19 23:23:41 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

void	Channel::setPassword(std::string pass)
{
	if (pass == "\0")
		_password.clear();
	_password = pass;
}

int	Channel::changeMode(char mode, std::vector<std::string> buf)
{
	std::map<char, int>::iterator	ite;
	

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
		return mode_password(buf, mode, ite);
	else if (mode == MODECHANNELOP)
		return mode_addmod(buf, mode, ite);
	else if (mode == MODEUSERLIMIT)
		return mode_userlimit(buf, mode, ite);
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

int				Channel::changePrefix(std::string user, char c)
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

int	Channel::invitedUsers(std::string user)
{
	std::vector<std::string>::iterator ite = std::find(_invitedUsers.begin(), _invitedUsers.end(), user);

	if (ite == _invitedUsers.end())
		return (0);
	else
		ite = _invitedUsers.erase(ite);
	return 1;
}