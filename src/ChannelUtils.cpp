/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:25:58 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/20 12:33:36 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

int	Channel::mode_password(std::vector<std::string> buf, char mode, std::map<char, int>::iterator ite, Client client)
{
	if (buf.size() < 4 && buf[2][0] == '+')
		Parse::sendIrcNumeric(1, "461", buf[0] + " :Not enough parameters", client);
	if (buf[3].empty() && getMode(MODEPASSWORD) == 0 && buf[2][0] == '+')
		Parse::sendIrcNumeric(1, "461", buf[0] + " :Not enough parameters", client);
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

int	Channel::mode_addmod(std::vector<std::string> buf, char mode, std::map<char, int>::iterator ite, Client client)
{
	if (buf.size() < 4)
		Parse::sendIrcNumeric(1, "461", buf[0] + " :Not enough parameters", client);
	else if (buf[3].empty() && buf[2][0] == '+')
		Parse::sendIrcNumeric(1, "461", buf[0] + " :Not enough parameters", client);
	else if (buf[2][0] == '+')
	{
		if (addModder(buf[3]) == 0)
			Parse::printErrorMessage(" user was already a moderator.", GENERICERROR);
		else
			return 1;
	}
	else if (buf[2][0] == '-')
	{
		if (rmModder(buf[3]) == 0)
			Parse::printErrorMessage(" user isn't a moderator.", GENERICERROR);
		else
			return 1;
	}
	else
		return 1;
	return 0;
}

int	Channel::mode_userlimit(std::vector<std::string> buf, char mode, std::map<char, int>::iterator ite, Client client)
{
	if (buf.size() < 4 && buf[2][0] == '+')
		Parse::sendIrcNumeric(1, "461", buf[0] + " :Not enough parameters", client);
	else if (buf[3].empty() && getMode(MODEUSERLIMIT) == 0 && buf[2][0] == '+')
		Parse::sendIrcNumeric(1, "461", buf[0] + " :Not enough parameters", client);
	else if (getMode(MODEUSERLIMIT) == 1 && buf[2][0] == '-')
	{
		ite->second = 0;
		_maxusers = -1;
		return 1;
	}
	else if (buf[2][0] == '+')
	{
		if (buf[3].find_first_not_of("0123456789") != -1)
			Parse::sendIrcNumeric(1, "461", buf[0] + " :Not enough parameters", client);
		int	number = std::atoi(buf[3].c_str());
		
		if (number <= 0)
			Parse::sendIrcNumeric(1, "461", buf[0] + " :Not enough parameters", client);
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

void	Channel::displayModes(Client client, std::vector<Channel>::iterator ch_it)
{
	std::string						printModes = ch_it->getModeString();

	Parse::sendIrcNumeric(2, "324", printModes, client, &(*ch_it));
}

void	Channel::displayTopic(Client client, std::vector<Channel>::iterator ch_it)
{
	if (_topic.empty() == false)
		Parse::sendIrcNumeric(2, "332", " " + ch_it->getTopic(), client, &(*ch_it));
	else
		Parse::sendIrcNumeric(2, "331", " :No topic is set", client, &(*ch_it));
}
