/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelGetFunctions.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:35:55 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/19 13:36:08 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

int	Channel::getMode(char c)
{
	std::map<char, int>::iterator ite;

	ite = _modes.find(c);
	if (ite == _modes.end())
		return -1;
	else
		return ite->second;
	return -1;
}

int	Channel::getUserLimit(void)
{
	return _maxusers;
}

int	Channel::getUserAmount(void)
{
	return _users.size();
}

std::string	Channel::getName(void)
{
	return _name;
}

std::string	Channel::getTopic(void)
{
	return _topic;
}

std::string Channel::getSymbol(void)
{
	if (getMode('i') == 0)
		return ("=");
	else
		return ("*");
}

std::string	Channel::getPrefix(std::string nick)
{
	return(_uprefix.find(nick)->second);
}

std::string	Channel::getSuperUser(void)
{
	return _superUser;
}

std::string Channel::getModeString(void)
{
	std::string str;

	std::map<char, int>::iterator it = _modes.begin();
	
	while (it != _modes.end())
	{
		str.push_back(' ');
		if (it->second == 0)
			str.push_back('-');
		else
			str.push_back('+');
		str.push_back(it->first);
		it++;
	}
	return (str);
}

std::vector<std::string>	Channel::getMods(void)
{
	return (this->_mods);
}

std::vector<std::string> Channel::getUsers(void)
{
	return (_users);
}

std::vector<std::string>	Channel::getUsersList(void)
{
	return (this->_users);
}

std::map<std::string, std::string> Channel::getPrefixs(void)
{
	return(_uprefix);
}



