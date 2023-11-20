/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelRemove.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:24:15 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/20 02:33:24 by sde-mull         ###   ########.fr       */
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
