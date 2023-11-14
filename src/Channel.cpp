/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:42:24 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/14 18:24:57 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void)
{
    std::cout << B_GREEN "Channel default contrutor called" RESET << std::endl;
}

Channel::~Channel(void)
{
    std::cout << B_RED "Channel destructor called" RESET << std::endl;
}

Channel::Channel(std::string name, std::string CreatingUser) : _superUser(CreatingUser), _name(name), _topic("\0")
{
	_users.push_back(CreatingUser);
	_uprefix[CreatingUser] = "@";
	_mods.push_back(CreatingUser);
	_modes.insert(std::make_pair('i', 0));
	_modes.insert(std::make_pair('t', 0));
	_modes.insert(std::make_pair('k', 0));
	_modes.insert(std::make_pair('o', 0));
	_modes.insert(std::make_pair('l', 0));
	_maxusers = -1;
}

int	Channel::mode_password(std::vector<std::string> buf, char mode, std::map<char, int>::iterator ite)
{
	if (buf[3].empty() && getMode(MODEPASSWORD) == 0 && buf[2][0] == '+')
		Parse::printErrorMessage("Error: in order to change password flag a new password is needed.", NOTENOUGHARGS);
	else if (getMode(MODEPASSWORD) == 0 && buf[2][0] == '+')
	{
		ite->second = 1;
		setPassword(buf[3]);
		return 1;
	}
	else if (getMode(MODEPASSWORD) == 1 && buf[2][0] == '-')
	{
		ite->second = 0;
		setPassword("\0");
		return 1;
	}
	else
		return 1;
	return 0;
}

int	Channel::mode_addmod(std::vector<std::string> buf, char mode, std::map<char, int>::iterator ite)
{
	if (buf[3].empty() && buf[2][0] == '+')
		Parse::printErrorMessage("Error: in order to add a new modder you have to provide the client's user.", NOTENOUGHARGS);
	else if (buf[2][0] == '+')
	{
		if (addModder(buf[3]) == 0)
			Parse::printErrorMessage("Error: user was already a moderator.", GENERICERROR);
		else
			return 1;
	}
	else if (buf[2][0] == '-')
	{
		if (rmModder(buf[3]) == 0)
			Parse::printErrorMessage("Error: user isn't a moderator.", GENERICERROR);
		else
			return 1;
	}
	return 0;
}

int	Channel::mode_userlimit(std::vector<std::string> buf, char mode, std::map<char, int>::iterator ite)
{
	if (buf[3].empty() && getMode(MODEUSERLIMIT) == 0 && buf[2][0] == '+')
		Parse::printErrorMessage("Error: you need to specify the new limit.", NOTENOUGHARGS);
	else if (getMode(MODEUSERLIMIT) == 1 && buf[2][0] == '-')
	{
		ite->second = 0;
		_maxusers = -1;
		return 1;
	}
	else if (getMode(MODEUSERLIMIT) && buf[2][0] == '+')
	{
		int	number = std::atoi(buf[3].c_str());
		
		if (number <= 0)
			Parse::printErrorMessage("Error: The user limit must be higher than 0.", GENERICERROR);
		else
		{
			_maxusers = number;
			ite->second = 1;
			return 1;
		}
		return 0;
	}
	else
		return 1;
	return 0;
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

void	Channel::displayModes(void)
{
	std::map<char, int>::iterator ite;
	
	std::cout << "ft display modes" << std::endl;
	for (ite = _modes.begin(); ite != _modes.end(); ite++)
	{
		std::cout << "loop" << std::endl;
		std::cout<< ite->first << " -> " << ite->second << std::endl;
	}
		
}

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

int	Channel::addModder(std::string user)
{
	std::vector<std::string>::iterator	ite;
	
	for (ite = _mods.begin(); ite != _mods.end(); ite++)
		if (*ite == user)
			return 0;
	_mods.push_back(user);
	return 1;
}

void	Channel::setPassword(std::string pass)
{
	if (pass == "\0")
		_password.clear();
	_password = pass;
}

int	Channel::getUserAmount(void)
{
	return _users.size();
}

void	Channel::addUser(std::string user)
{
	_users.push_back(user);
	_uprefix[user] = "%";
}

int	Channel::invitedUsers(std::string user)
{
	std::vector<std::string>::iterator ite = vectorFind(_invitedUsers, user);

	if (ite == _invitedUsers.end())
		return (0);
	else
	{
		ite = _invitedUsers.erase(ite);
		return 1;
	}
}

int	Channel::changeTopic(std::vector<std::string> buf)
{
	std::string	topic;
	std::vector<std::string>::iterator ite;
	
	for (ite = buf.begin(); ite != buf.end(); ite++)
		topic = topic + " " + *ite;
	_topic = topic;
	return 1;
}

int	Channel::inviteUser(std::string user)
{
	std::vector<std::string>::iterator ite = vectorFind(_invitedUsers, user);
	
	if (ite == _invitedUsers.end())
		_invitedUsers.push_back(user);
	else
		return 0;
	return 1;
}

int	Channel::getIsUser(std::string user)
{
	std::vector<std::string>::iterator ite = vectorFind(_users, user);

	if (ite == _users.end())
		return 0;
	else
		return 1;
}

int	Channel::getIsMod(std::string user)
{
	std::vector<std::string>::iterator ite = vectorFind(_mods, user);

	if (ite == _mods.end())
		return 0;
	else
		return 1;
}

int		Channel::rmModder(std::string user)
{
	std::vector<std::string>::iterator ite = vectorFind(_mods, user);

	if (ite == _mods.end())
		return 0;
	else
		ite = _mods.erase(ite);
	return 1;
}

int	Channel::rmUser(std::string user)
{
	std::vector<std::string>::iterator ite = vectorFind(_users, user);

	rmModder(user);
	if (ite == _users.end())
		return 0;
	else
		ite = _users.erase(ite);
	return 1;
}

std::string	Channel::getSuperUser(void)
{
	return _superUser;
}

std::string	Channel::getName(void)
{
	return _name;
}

std::string	Channel::getTopic(void)
{
	return _topic;
}

int	Channel::getUserLimit(void)
{
	return _maxusers;
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
