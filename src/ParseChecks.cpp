/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseChecks.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:55:56 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/21 16:09:28 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"

/*
checkNumbArgs have only one job. This function will check if the number of arguments passed is not different from 2.
./ircserv <port> <password> 
executable  arg1  arg2   ----> 3 args that's why if (argc != 3)
*/
bool Parse::checkNumbArgs(int const argc)
{
	if (argc != 3)
	{
		std::cerr << B_RED "Error:\n" B_YELLOW "Usage: ./ircserv <port> <password>\n" \
				"<port>:" B_WHITE " The port number that the server will be listening to for incoming IRC connections\n" \
				B_YELLOW "<password>:" B_WHITE " The connection password" RESET << std::endl;
		return (false);
	}
	return (true);
}

/*
checkClientByNick wll search inside the vector of clients by nick.
Returns false in case it finds an equal nick
Returns true in case it doesn't find an equal nick
*/
bool  Parse::CheckClientByNick(std::string nick)
{
	for (unsigned long i = 0; i < _clients.size(); i++)
	{
		if (!_clients[i].Getters(GETNICK).compare(nick))
			return (true);
	}
	return (false);
}

/*
CheckNickRules will check if the nickname chosen is respecting the nickname rules.
*/
bool Parse::CheckNickRules(std::string str)
{
	if (str[0] == '#' || str[0] == '&' || str[0] == '$' || str[0] == ':')
		return (false);
	for (unsigned long i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ' || str[i] == ',' || str[i] == '*' || str[i] == '?'\
		|| str[i] == '!' || str[i] == '@' || str[i] == '.')
			return (false);
	}
	return (true);
}

bool Parse::CheckPrivMessageArguments(Client client, int size, std::string str)
{
	if (size < 3)
	{
		Parse::sendIrcMessage(":localhost 412 " + client.Getters(GETNICK) + " :No text to send", client.GettersInt(GETCLIENTFD));
		Parse::sendIrcMessage("USAGE:\n/msg <nick> <message>\n/msg <channel> <message>\n/PRIVMSG <nick> <message>\n/PRIVMSG <channel> <message>", \
		client.GettersInt(GETCLIENTFD));
		return (Parse::printErrorMessage(client.Getters(GETNICK) + " didn't send a message. Command used: " + str , false));
	}

	return (true);
}
