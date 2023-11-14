/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds_utils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
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
				Parse::sendIrcNumeric(2, "332", " :" + ch_it->getTopic(), client, &(*ch_it));
			else
				Parse::sendIrcNumeric(2, "331", " :No topic is set", client, &(*ch_it));
			return (1);
		}
		else
			return (printErrorMessage("This channel is invite only and you haven't been invited!", 5));	
	}
	else
	{
    ch_it->addUser(client.Getters(GETNICK));
		Parse::sendIrcNumeric(3, "", "", client, &(*ch_it));
		if (ch_it->getTopic() != "\0")
			Parse::sendIrcNumeric(2, "332", " :" + ch_it->getTopic(), client, &(*ch_it));
		else
			Parse::sendIrcNumeric("331", client, (*ch_it), " :No topic is set", 2);
		Parse::sendIrcNumeric(1, "353", " " + ch_it->getSymbol() + " " + \
		ch_it->getName() + " :" + ch_it->getPrefix(client.Getters(GETNICK)) + client.Getters(GETNICK), client, &(*ch_it));
		Parse::sendIrcNumeric(2, "366", " :End of NAMES list", client, &(*ch_it));
		Parse::sendIrcNumeric(2, "324", ch_it->getModeString(), client, &(*ch_it));
		Parse::sendIrcNumeric(2, "315", " :End of WHO list", client, &(*ch_it));
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

