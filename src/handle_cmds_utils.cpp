/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds_utils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:21:53 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/14 17:16:24 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"



int	Parse::try_joining(std::vector<Channel>::iterator ch_it, std::vector<std::string> buffer, Client client)
{
	// if (ch_it->getMode(MODEUSERLIMIT) == 1)
	if (ch_it->getMode('i') == 1)
	{
		if (ch_it->invitedUsers(client.Getters(GETNICK)) == 1)
		{
			ch_it->addUser(client.Getters(GETNICK));
			if (ch_it->getTopic() != "\0")
				Parse::sendIrcNumeric("332", client, (*ch_it), " :" + ch_it->getTopic(), 2);
			else
				Parse::sendIrcNumeric("331", client, (*ch_it), " :No topic is set", 2);
			return (1);
		}
		else
			return (printErrorMessage("This channel is invite only and you haven't been invited!", 5));	
	}
	else
	{
		if (ch_it->getTopic() != "\0")
			Parse::sendIrcNumeric("332", client, (*ch_it), " :" + ch_it->getTopic(), 2);
		else
			Parse::sendIrcNumeric("331", client, (*ch_it), " :No topic is set", 2);
		ch_it->addUser(client.Getters(GETNICK));
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

