/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelRemove.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:24:15 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/22 12:44:06 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

int	Channel::rmUser(std::string user)
{
	std::vector<std::string>::iterator ite = std::find(_users.begin(), _users.end(), user);

	changePrefix(user, '0');
	if (ite == _users.end())
		return 0;
	else
		ite = _users.erase(ite);
	return 1;
}

int		Channel::rmModder(std::string user)
{
	std::vector<std::string>::iterator ite = std::find(_mods.begin(), _mods.end(), user);

	changePrefix(user, '+');
	if (ite == _mods.end())
		return 0;
	else
		ite = _mods.erase(ite);
	return 1;
}

int		Channel::rmInvitedUsers(std::string user)
{
	std::vector<std::string>::iterator ite = std::find(_invitedUsers.begin(), _invitedUsers.end(), user);

	if (ite == _invitedUsers.end())
		return 0;
	else
		ite = _invitedUsers.erase(ite);
	return 1;
}

int		Channel::rmPrefixes(std::string user)
{
	std::map<std::string,std::string>::iterator ite = _uprefix.find(user);

	if (ite == _uprefix.end())
		return 0;
	else
		_uprefix.erase(ite);
	return 1;
}