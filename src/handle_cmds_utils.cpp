/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds_utils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:21:53 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/14 16:01:32 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

std::vector<std::string>::iterator	vectorFind(std::vector<std::string> vector, std::string needle)
{
	std::vector<std::string>::iterator ite;

	for (ite = vector.begin(); ite != vector.end(); ite++)
		if (*ite == needle)
			return ite;
	return (vector.end());
}

int	Parse::try_joining(std::vector<Channel>::iterator ch_it, std::vector<std::string> buffer, Client client)
{
	if (ch_it->getMode('i') == 1)
	{
		if (ch_it->invitedUsers(buffer[1]) == 1)
		{
			ch_it->addUser(buffer[1]);
			if (ch_it->getTopic() != "\0")
				Parse::sendIrcNumeric(2, "332", " :" + ch_it->getTopic(), client, &(*ch_it));
			else
				Parse::sendIrcNumeric(2, "331", " :No topic is set", client, &(*ch_it));
			return (1);
		}
		else
			Parse::sendIrcNumeric(2, "473", " :Cannot join channel (+i)", client, &(*ch_it));
	}
	else
	{
		ch_it->addUser(client.Getters(GETNICK));
		Parse::sendIrcNumeric(3, "", "", client, &(*ch_it));
		if (ch_it->getTopic() != "\0")
			Parse::sendIrcNumeric(2, "332", " :" + ch_it->getTopic(), client, &(*ch_it));
		else
			Parse::sendIrcNumeric(2, "331", " :No topic is set", client, &(*ch_it));
		Parse::BroadcastChannel(1, "353", PrefixString(client, (*ch_it)), client, &(*ch_it));
		Parse::BroadcastChannel(2, "366", " :End of NAMES list", client, &(*ch_it));
		Parse::sendIrcNumeric(2, "324", ch_it->getModeString(), client, &(*ch_it));
		return (1);
	}
	return (0);
}

std::vector<std::string> Parse::Split_spc(char* buf) {
    int i = 0;
    int j;
    std::vector<std::string> ret;
    std::string buffer;

    while (buf[i]) 
	{
        j = 0;
        while ((buf[i] == ' ' || buf[i] == '\r') && buf[i])
            i++;
        while (buf[i] != ' ' && buf[i]) 
		{
            buffer.push_back(buf[i]);
            i++;
        }

        ret.push_back(buffer);
        buffer.clear();
    }
    return (ret);
}

