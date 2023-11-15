/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUserAuthentication.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:46:28 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/14 15:18:24 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::Client_Authenticate(Client &client, char *buf, int received)
{
	if (!Call_Functions(client, buf, received))
	{
		std::cout << RED "Client not authenticated " << RESET << std::endl;
		std::string str(buf);
		str.erase(str.begin() + str.find_last_of('\n'));
		Parse::sendIrcNumeric(1, "421", " " + str + " :Unknown command", client);
	}
	PrintClientArgs(client);
	if (client.GettersInt(GETPASS) == 1 && client.Getters(GETNICK) != "\0" && client.Getters(GETUSER) != "\0")
	{
		std::cout << GREEN "CLIENT AUTHENTICATE" << RESET << std::endl;
		Parse::printMessage(client.Getters(GETNICK) + " joined the server", CYAN);
		Parse::sendIrcNumeric(1, "001", " :Welcome to the ft_irc Network ", client);
		Parse::sendIrcNumeric(1, "005", " :CHANNEL_TYPES = #,& \nCHANNEL_MODES = i,t,k,o,l", client);
		client.SettersInt(SETAUTH, 1);
	}
}

int Server::Call_Functions(Client &client, char *buf, int received)
{
	std::vector<std::string> vec = Parse::ft_split(buf, received);
	int f = 0;
	for (int k = 0; k < vec.size(); k++)
	{
		std::map<std::string, function>::iterator it = m.find(std::string(vec[k]));
		if (it != m.end()/*  && k < vec.size() - 1 */)
		{	
			if (k == vec.size() - 1)
				Parse::sendIrcNumeric(1, "461", " " +  (it->first) + " :Not enough parameters", client);
			else	
				(this->*it->second)(client, vec[k + 1]);
			k++;
			f = 1;
		}
	}
	return (f);
}

void    Server::ft_pass(Client &client, std::string str)
{
	if (this->_password == str)
		client.SettersInt(SETPASS, 1);
	else
	{
		client.SettersInt(SETPASS, 0);
		Parse::sendIrcNumeric(1, "464", " :Password incorrect", client);
	}
}

void    Server::ft_user(Client &client, std::string str)
{
	client.Setters(SETUSER, str);
}

void     Server::ft_nick(Client &client, std::string str)
{
	if (!Parse::CheckNickRules(str))
	{
		Parse::sendIrcNumeric(1, "432", ":Erroneus nickname", client);
		return ;
	}
	if (!Parse::CheckClientByNick(str))
	{
		Parse::sendIrcNumeric(1, "433", " :Nickname is already in use", client);
		return ;
	}
	Parse::sendIrcMessage(":" + client.Getters(GETNICK) + " NICK :" + str, client.GettersInt(GETCLIENTFD));
	client.Setters(SETNICK, str);
}

void    Server::SendMsg(Client &client, const char *data)
{
	send(client.GettersInt(GETCLIENTFD), data, strlen(data), 0);
}

void    Server::PrintClientArgs(Client &client)
{
	if (client.GettersInt(GETPASS))
		SendMsg(client, "\nYou have set the correct password ✔\n");
	else
		SendMsg(client, "You have not set the correct password ✘\n");
	SendMsg(client, "This is your Nick: ");
	if (client.Getters(GETNICK) != "\0")
	{
		SendMsg(client, client.Getters(GETNICK).c_str());
		SendMsg(client," ✔\n");
	}  
	else
		SendMsg(client, " ✘\n");
	SendMsg(client, "This is your User: ");
	if (client.Getters(GETUSER) != "\0")
	{
		SendMsg(client, client.Getters(GETUSER).c_str());
		SendMsg(client," ✔\n");
	}
	else
		SendMsg(client, " ✘\n");
}

bool	Server::checkUserAuthentication(Client &client, char *buf, int received)
{
	if (client.GettersInt(GETAUTH) == 1)
		return (true);
	else
		Client_Authenticate(client, buf, received);
	return (false);
}


//--------------------------------------------------------------------
/* 
Sending message: :localhost 001 rreis-de :Welcome to the ft_irc Network 

Sending message: :localhost 005 rreis-de :CHANNEL_TYPES = #,& 
CHANNEL_MODES = i,t,k,o,l

Sending message: :rreis-de!rreis-de@localhost JOIN #girafa

Sending message: :localhost 331 rreis-de #girafa :No topic is set

Sending message: :localhost 353 sde-mull = #girafa :+rreis-de @sde-mull

Sending message: :localhost 353 rreis-de = #girafa :+rreis-de @sde-mull

Sending message: :localhost 366 sde-mull #girafa :End of NAMES list

Sending message: :localhost 366 rreis-de #girafa :End of NAMES list

Sending message: :localhost 324 rreis-de #girafa -i -k -l -o -t

Sending message: :localhost 352 sde-mull #girafa localhost ft_irc sde-mull H@ :1 sde-mull

Sending message: :localhost 352 rreis-de #girafa localhost ft_irc rreis-de H+ :1 rreis-de

Sending message: :localhost 315 rreis-de #girafa :End of WHO list

Sending message: :localhost 352 sde-mull #girafa localhost ft_irc sde-mull H@ :1 sde-mull

Sending message: :localhost 352 rreis-de #girafa localhost ft_irc rreis-de H+ :1 rreis-de

Sending message: :localhost 315 sde-mull #girafa :End of WHO list





//--------------------------------------------------------------------

Sending message: :localhost 001 rreis-de :Welcome to the Darkest Region of the Internet

Sending message: :localhost 005 rreis-de :CHANTYPES=#

Sending message: :localhost 005 rreis-de :CHANMODES=i,t,k,o,l

Sending message: :rreis-de!rreis-de@localhost JOIN #juba

Sending message: :localhost 332 rreis-de #juba :No topic is set

Sending message: :localhost 353 rreis-de = #juba :@god %rreis-de 

Sending message: :localhost 353 rreis-de = #juba :@god %rreis-de 

Sending message: :localhost 366 rreis-de #juba :End of NAMES list

Sending message: :localhost 366 rreis-de #juba :End of NAMES list

Sending message: :localhost 324 #juba #juba: -t -k +o -l -m -b -s 

Sending message: :localhost 352 rreis-de #juba localhost ft_irc god H@ :1 sde-mull

Sending message: :localhost 352 rreis-de #juba localhost ft_irc rreis-de H+ :1 rreis-de

Sending message: :localhost 315 rreis-de #juba :End of WHO list

Sending message: :localhost 352 god #juba localhost ft_irc god H@ :1 sde-mull

Sending message: :localhost 352 god #juba localhost ft_irc rreis-de H+ :1 rreis-de

Sending message: :localhost 315 god #juba :End of WHO list */





