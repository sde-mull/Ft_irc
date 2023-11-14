/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds_utils.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:21:53 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/13 16:41:41 by pcoimbra         ###   ########.fr       */
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
	if (ch_it->getMode(MODEUSERLIMIT) == 1)
	if (ch_it->getMode('i') == 1)
	{
		if (ch_it->invitedUsers(buffer[1]) == 1)
		{
			ch_it->addUser(buffer[1]);
			if (ch_it->getTopic() != "\0")
				Parse::sendIrcMessage(":localhost 332 " + client.Getters(GETNICK) + " " + ch_it->getName() + " :" + ch_it->getTopic(), client.GettersInt(GETCLIENTFD));
			else
				Parse::sendIrcMessage(":localhost 331 " + client.Getters(GETNICK) + " " + ch_it->getName() + " :No topic is set", client.GettersInt(GETCLIENTFD));
			return (1);
		}
		else
			return (printErrorMessage("This channel is invite only and you haven't been invited!", 5));	
	}
	else
	{
		if (ch_it->getTopic() != "\0")
			Parse::sendIrcMessage(":localhost 332 " + client.Getters(GETNICK) + " " + ch_it->getName() + " :" + ch_it->getTopic(), client.GettersInt(GETCLIENTFD));
		else
			Parse::sendIrcMessage(":localhost 331 " + client.Getters(GETNICK) + " " + ch_it->getName() + " :No topic is set", client.GettersInt(GETCLIENTFD));
		ch_it->addUser(buffer[1]);
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

