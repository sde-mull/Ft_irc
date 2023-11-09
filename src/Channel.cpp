/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:42:24 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/09 17:20:24 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string name, std::string CreatingUser) : _superUser(CreatingUser), _name(name)
{
	_users.push_back(CreatingUser);
	_topic	= "Default topic. Ask an operator to change this.";
	_mods.push_back(CreatingUser);
	_modes.insert(std::make_pair('i', 0));
	_modes.insert(std::make_pair('t', 0));
	_modes.insert(std::make_pair('k', 0));
	_modes.insert(std::make_pair('o', 0));
	_modes.insert(std::make_pair('l', 0));
}

int	Channel::getMode(char c)
{
	std::map<char, int>::iterator ite;

	ite = _modes.find(c);
	if (ite == _modes.end())
		return 0;
	else
	{
		if (ite->second == 1)
			return 1;
		else
			return 0;
	}
	return 0;
}

void	Channel::addUser(std::string user)
{
	_users.push_back(user);
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