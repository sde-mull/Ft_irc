/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:25:43 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/10/31 16:54:58 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

std::string	Channel::getName(void)
{
	return _name;
}

Channel::Channel(std::string name, std::string superuser) : _superUser(superuser), _name(name)
{
	_users.push_back(superuser);
}