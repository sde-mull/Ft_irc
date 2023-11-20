/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelUtils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 23:25:58 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/19 23:27:16 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

int	Channel::mode_password(std::vector<std::string> buf, char mode, std::map<char, int>::iterator ite)
{
	if (buf.size() < 4 && buf[2][0] == '+')
		Parse::printErrorMessage(" arguments should be: PASS <channel> +-k <client's user>.", NOTENOUGHARGS);
	if (buf[3].empty() && getMode(MODEPASSWORD) == 0 && buf[2][0] == '+')
		Parse::printErrorMessage(" in order to change password flag a new password is needed.", NOTENOUGHARGS);
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
	if (buf.size() < 4)
		Parse::printErrorMessage(" arguments should be: MODE <channel> +-o <client's user>.", NOTENOUGHARGS);
	else if (buf[3].empty() && buf[2][0] == '+')
		Parse::printErrorMessage(" in order to add a new modder you have to provide the client's user.", NOTENOUGHARGS);
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

int	Channel::mode_userlimit(std::vector<std::string> buf, char mode, std::map<char, int>::iterator ite)
{
	if (buf.size() < 4 && buf[2][0] == '+')
		Parse::printErrorMessage(" arguments should be: MODE <channel> +-l <User's limit>.", NOTENOUGHARGS);
	else if (buf[3].empty() && getMode(MODEUSERLIMIT) == 0 && buf[2][0] == '+')
		Parse::printErrorMessage(" you need to specify the new limit.", NOTENOUGHARGS);
	else if (getMode(MODEUSERLIMIT) == 1 && buf[2][0] == '-')
	{
		ite->second = 0;
		_maxusers = -1;
		return 1;
	}
	else if (getMode(MODEUSERLIMIT) && buf[2][0] == '+')
	{
		if (buf[3].find_first_not_of("0123456789") != -1)
			return Parse::printErrorMessage(" User limit must be an integer.", WRONGARGSERR);
		int	number = std::atoi(buf[3].c_str());
		
		if (number <= 0)
			Parse::printErrorMessage(" The user limit must be higher than 0.", GENERICERROR);
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
