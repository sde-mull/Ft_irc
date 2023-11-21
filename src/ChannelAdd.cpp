/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelAdd.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:15:20 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/20 18:13:32 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

void	Channel::addUser(std::string user)
{
	_users.push_back(user);
	_uprefix[user] = "+";
}

int	Channel::addModder(std::string user)
{
	std::vector<std::string>::iterator	ite;
	
	for (ite = _mods.begin(); ite != _mods.end(); ite++)
		if (*ite == user)
			return 0;
	_mods.push_back(user);
	_uprefix[user] = "@";
	return 1;
}

int	Channel::inviteUser(std::string user)
{
	std::vector<std::string>::iterator ite = std::find(_invitedUsers.begin(), _invitedUsers.end(), user);
	
	if (ite == _invitedUsers.end())
		_invitedUsers.push_back(user);
	else
		return 0;
	return 1;
}