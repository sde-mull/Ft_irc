/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:42:24 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/19 23:26:23 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(void){
}

Channel::~Channel(void){
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

Channel::Channel(std::string name, std::string CreatingUser, std::string pass) : _superUser(CreatingUser), _name(name), _topic("\0"), _password(pass)
{
	_users.push_back(CreatingUser);
	_uprefix[CreatingUser] = "@";
	_mods.push_back(CreatingUser);
	_modes.insert(std::make_pair('i', 0));
	_modes.insert(std::make_pair('t', 0));
	_modes.insert(std::make_pair('k', 1));
	_modes.insert(std::make_pair('o', 0));
	_modes.insert(std::make_pair('l', 0));
	_maxusers = -1;
}
