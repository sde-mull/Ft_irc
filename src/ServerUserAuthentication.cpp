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
		std::cout << RED "Client not authenticated " << RESET << std::endl;
	PrintClientArgs(client);
	if (client.GettersInt(GETPASS) == 1 && client.Getters(GETNICK) != "\0" && client.Getters(GETUSER) != "\0")
	{
		std::cout << GREEN "CLIENT AUTHENTICATE" << RESET << std::endl;
		Parse::printMessage(client.Getters(GETNICK) + " joined the server", CYAN);
		Parse::sendIrcNumeric(1, "001", " :Welcome to the ft_irc Network ", client);
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
	client.Setters(SETNICK, str);
	Parse::sendIrcNumeric(1, "001", "", client);
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