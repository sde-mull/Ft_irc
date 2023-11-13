/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerUserAuthentication.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 20:46:28 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/13 10:38:00 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void Server::Client_Authenticate(Client &client, char *buf, int received)
{
	if (!Call_Functions(client, buf, received))
		std::cout << RED "Client not authenticated " << RESET << std::endl;
	PrintClientArgs(client);
	if (client.GettersInt(GETPASS) == 1 && client.Getters(GETNICK) != "\0" && client.Getters(GETUSER) != "\0")
	{
		std::cout << GREEN "CLIENT AUTHENTICATE" << RESET << std::endl;
		Parse::printMessage(client.Getters(GETNICK) + " joined the server", CYAN);
		//Parse::SendCommandIRC(001, client);
		Parse::sendIrcMessage(":localhost 001 " + client.Getters(GETNICK) + " :Welcome to the ft_irc Network ", client.GettersInt(GETCLIENTFD));
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
		if (it != m.end() && k < vec.size() - 1)
		{
			(this->*it->second)(client, vec[k + 1]);
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
		client.SettersInt(SETPASS, 0);
}

void    Server::ft_user(Client &client, std::string str)
{
	client.Setters(SETUSER, str);
}

void     Server::ft_nick(Client &client, std::string str)
{
	if (!Parse::CheckNickRules(str))
	{
		SendMsg(client, "\nBad Nick");
		return ;
	}
	if (!Parse::CheckClientByNick(str))
	{
		Parse::sendIrcMessage(":localhost 433 " + client.Getters(GETNICK) + " " + " :Nickname is already in use", client.GettersInt(GETCLIENTFD));
		//SendMsg(client, "\nNick Already Taken");
		return ;
	}
	Parse::sendIrcMessage(":localhost 001 " + str + "", client.GettersInt(GETCLIENTFD));
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