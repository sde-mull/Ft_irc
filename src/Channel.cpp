/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:42:24 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/06 17:16:05 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* #include "Channel.hpp"

Channel::Channel(std::string name, std::string CreatingUser) : _superUser(CreatingUser), _name(name)
{
	_users.push_back(CreatingUser);
	_topic	= "Default topic. Ask an operator to change this.";
}

int	Channel::Banneduser(std::string user)
{
	std::vector<std::string>::iterator	ite;

	for (ite = _users.begin(); ite < _users.end(); ite++)
		if (user == *ite)
			return (0);
	return (1);
}

void	Channel::addUser(std::string user)
{
	_users.push_back(user);
} */