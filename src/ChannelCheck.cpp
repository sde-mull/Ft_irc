/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelCheck.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:11:59 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/20 11:17:21 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

int Channel::CheckIsSuperUser(std::string user)
{
	if (user == _superUser)
		return 1;
	return 0;
}

int	Channel::CheckIsMod(std::string user)
{
	std::vector<std::string>::iterator ite = std::find(_mods.begin(), _mods.end(), user);

	if (ite == _mods.end())
		return 0;
	else
		return 1;
}

int	Channel::CheckIsUser(std::string user)
{
	std::vector<std::string>::iterator ite = std::find(_users.begin(), _users.end(), user);

	if (ite == _users.end())
		return 0;
	return 1;
}

int	Channel::CheckInvite(std::string user)
{
	std::vector<std::string>::iterator ite = std::find(_invitedUsers.begin(), _invitedUsers.end(), user);

	if (ite == _invitedUsers.end())
		return (0);
	else
		return 1;
	return 1;
}

int	Channel::check_pass(std::string pass)
{
	if (pass == _password)
		return 1;
	return 0;
}
