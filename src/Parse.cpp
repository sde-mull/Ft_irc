/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:31:10 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/21 16:21:18 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cinclude.hpp"

std::vector<Client> 	Parse::	_clients;

bool Parse::checkArgParam(std::string port, std::string password)
{
	int portNumb;

	portNumb = atoi(port.c_str());
	if (port.length() == 0 || port.find_first_not_of("0123456789") != std::string::npos || \
		portNumb < 0 || portNumb > 65535)
	{
		std::cerr << B_RED "Error:\n" B_YELLOW "Port must be an integer between 0 and 65535" RESET << std::endl;
		return (false);
	}
	if (password.length() == 0)
	{
		std::cerr << B_RED "Error:\n" B_YELLOW "Server password doesn't exist" RESET << std::endl;
		return (false);
	}
	return (true);
}

/*
printErrorMessage is a function that will just print in the standard error
it takes the error message you want to write
it takes the typeError, this argument is just to say what number you want to return with this error 
typeError 
*/
int Parse::printErrorMessage(std::string message, int typeError)
{
	std::cerr << RED "Error: " << message << RESET << std::endl;
	return (typeError);
}

/*
printMessage will take a message and write it in the standard output
you can choose the color, but even if you don't choose is set to white by default.
You can check how to make a argument default in the definition of this function inside the class parse
*/

void Parse::printMessage(std::string message, std::string color)
{
	std::cout << color << message << RESET << std::endl;
}

/*
addClient will add client to the vector of clients
Everytime the client is added we call the constructor of the client and push_back to the vector
*/

void    Parse::addClient(int id)
{
	_clients.push_back(Client(id));
}


/*
searchClientById will take the id as an argument(the id is the number of the client socket ID to be more specific)
It will search the id inside of the class client for each iteration of the vector clients
once found it will return the reference of the client inside the vector
*/

Client&  Parse::searchClientById(int id)
{
	unsigned long index = 0;

	for (unsigned long i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].GettersInt(GETCLIENTFD) == id){
			index = i;
			break ;
		}
	}
	return (_clients[index]);
}

/*
quem fez que explique aqui
*/

std::vector<std::string>    Parse::ft_split(char *buf, int received)
{
	std::string nova;
	std::vector<std::string> vec;
	std::string token;
	
	if (buf == NULL)
		return (vec);
	for (int j = 0; j < received; j++)
	{
		if (buf[j] == '\n')
			nova += ' ';
		if (buf[j] != '\n' && buf[j] != '\r')
			nova += buf[j];
	}
	std::istringstream ss(nova);
	while (std::getline(ss, token, ' '))
		vec.push_back(token);
	return (vec);
}

/*
sendIRCMessage is a function that will send a message back to the client using the clientId
*/
int	Parse::sendIrcMessage(std::string message, int clientId)
{
	message = message + "\r\n";
	// std::cout << "Sending message: " << message << std::endl;
	if (send(clientId, message.c_str(), message.length(), 0) == -1)
		exit(1);
	return 0;
}

int	Parse::sendIrcNumeric(int i, std::string code, std::string str, Client client, Channel *channel)
{
	std::string message = Parse::SendCommandIRC(i, code, str, client, channel) + "\r\n";
	// std::cout << "Sending message: " << message << std::endl;
	if (send(client.GettersInt(GETCLIENTFD), message.c_str(), message.length(), 0) == -1)
		exit(1);
	return 0;
}

std::string Parse::PrefixString(Channel channel)
{
	std::string str = " " + channel.getSymbol() + " " + channel.getName() + " :";
	std::map<std::string, std::string> prefixs = channel.getPrefixs();
	std::map<std::string, std::string>::iterator it = prefixs.begin();
	while (it != prefixs.end())
	{
		str += it->second + it->first;
		it++;
		if (it != prefixs.end())
			str += " ";
	}
	return (str);
}

int Parse::BroadcastChannel(int i, std::string code, std::string str, Channel *channel)
{
	std::vector<std::string> users = (*channel).getUsers();
	for(unsigned long j = 0; j < users.size(); j++)
		Parse::sendIrcNumeric(i, code, str, *(Parse::ReturnClientByNick(users[j])), channel);
	return (0);
}

int Parse::BroadcastWho(Client client, Channel *channel)
{
	std::vector<std::string> users = (*channel).getUsers();
	Client *client_tmp = NULL;
	std::string flag = "";
	for(unsigned long j = 0; j < users.size(); j++)
	{
		client_tmp = (Parse::ReturnClientByNick(users[j]));
		flag = " H" + channel->getPrefix(users[j]) + " :1 ";
		Parse::sendIrcMessage(":localhost 352 " + client.Getters(GETNICK) + " " + channel->getName() + " localhost ft_irc " + client_tmp->Getters(GETNICK) + flag + client_tmp->Getters(GETUSER), client.GettersInt(GETCLIENTFD));
	}
	return (0);
}

void Parse::PrintAllClients(void)
{
	for (unsigned long i = 0; i < _clients.size(); i++)
		std::cout << "Client with the id " << _clients[i].GettersInt(GETCLIENTFD) << " is online!" << std::endl;
}

int  Parse::ReturnClientById(int id)
{
	for (unsigned long i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].GettersInt(GETCLIENTFD) == id)
			return (i);
	}
	return (-1);
}

Client* Parse::ReturnClientByNick(std::string nick)
{
	for (unsigned long i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].Getters(GETNICK) == nick)
			return (&(_clients[i]));
	}
	return (NULL);
}

void    Parse::RemoveClient(int id)
{
	std::string nick;

	nick = Parse::searchClientById(id).Getters(GETNICK);
	_clients.erase(_clients.begin() + Parse::ReturnClientById(id));

	if (nick.length() == 0)
		std::cout << CYAN "Anonymous user";
	else
		std::cout << CYAN << nick;
	Parse::printMessage(" was disconnected", RED);
}

std::string	Parse::SendCommandIRC(int i, std::string code, std::string str, Client client, Channel *channel)
{
	std::string msg;

	switch(i)
	{
		case (1):
			return (":localhost " + code + " " + client.Getters(GETNICK) + str);
		case (2) :
			return (":localhost " + code + " " + client.Getters(GETNICK) + " " + channel->getName() + str);
		case (3) :
			return (":" + client.Getters(GETNICK) + "!" + client.Getters(GETUSER) + "@localhost JOIN " + channel->getName());
	}
	return ("");
}

std::vector<int>				Parse::ReturnMessageTargets(std::string &target, Client client)
{
	std::vector<int> returnTargets;

	if (target[0] == '@' || target[0] == '+')
	{
		if (target[1])
			Parse::GetOpsAndMembersTarget(target, client, returnTargets);
	}
	else if (target[0] == '#')
		Parse::GetAllIdInChannel(target, client, returnTargets);
	else
	{
		int id = Parse::SearchTargetMessageId(target, client);
		if (id > 0)
			returnTargets.push_back(id);
	}
	return (returnTargets);
}

int Parse::SearchTargetMessageId(std::string target, Client client)
{
	int id = Parse::SearchClientByNick(target);
	if (id == -1)
		sendIrcMessage(":localhost 401 " + client.Getters(GETNICK) + " " + target + " :no such nick", client.GettersInt(GETCLIENTFD));
	return (id);
	
}

int		Parse::SearchClientByNick(std::string target)
{
	for (unsigned long i = 0; i < _clients.size(); i++)
	{
		if (!_clients[i].Getters(GETNICK).compare(target))
			return (_clients[i].GettersInt(GETCLIENTFD));
	}
	return (-1);
}

void		Parse::GetAllIdInChannel(std::string target, Client client, std::vector<int> &returnTargets, int flag)
{
	Channel *targetChannel = Parse::ReturnChannelByName(target);
	std::vector<std::string> ChannelUsers;

	if (targetChannel == NULL)
	{
		Parse::sendIrcMessage(":localhost 403 " + client.Getters(GETNICK) + " " + target + " :No such channel", client.GettersInt(GETCLIENTFD));
		return ;
	}
	if (flag)
		ChannelUsers = targetChannel->getMods();
	else
		ChannelUsers = targetChannel->getUsersList();
	std::vector<std::string>::iterator it;
	
	it = std::find(ChannelUsers.begin(), ChannelUsers.end(), client.Getters(GETNICK));
	if (it == ChannelUsers.end())
	{
		Parse::sendIrcMessage(":localhost 404 " + client.Getters(GETNICK) + " " + target + " :You are not in the channel to send the message", client.GettersInt(GETCLIENTFD));
		return ;
	}
	for (unsigned long i = 0; i < ChannelUsers.size(); i++)
	{
		if (client.Getters(GETNICK).compare(ChannelUsers[i]))
			returnTargets.push_back(Parse::SearchClientByNick(ChannelUsers[i]));
	}
}

Channel*		Parse::ReturnChannelByName(std::string name)
{
	for (unsigned long i = 0; i < _Channels.size(); i++)
	{
		if (!_Channels[i].getName().compare(name))
			return (&(_Channels[i]));
	}
	return (NULL);
}

void		Parse::GetOpsAndMembersTarget(std::string &target, Client client, std::vector<int> &returnTargets)
{
	int flag = (target[0] == '@' && target[1] != '+');
	target.erase(target.begin() + target.find_first_of("@+"));
	if (target[0] == '@' || target[0] == '+')
		target.erase(0, 1);
	if (target.size() == 0)
		return ;
	if (flag)
		Parse::GetAllIdInChannel(target, client, returnTargets);
	else
		Parse::GetAllIdInChannel(target, client, returnTargets);
}

std::vector<std::string>    Parse::Hander_ft_split(char *buf, int received)
{
	std::string nova;
	std::vector<std::string> vec;
	std::string token;
	
	if (!buf)
		return (vec);
	for (int j = 0; j < received; j++)
	{
		if (buf[j] == '\n')
			nova += ' ';
		if (buf[j] != '\n' && buf[j] != '\r')
			nova += buf[j];
	}

	nova.erase(nova.begin() + nova.find_last_of(' '));

	std::istringstream ss(nova);
	while (std::getline(ss, token, ' '))
		vec.push_back(token);
	return (vec);
}

void			Parse::RemoveChannel(std::string ChannelName)
{
	Parse::printMessage("Channel: " + ChannelName + "\nThis channel seems to be empty, deleting channel...\n", YELLOW);
	int index = Parse::ReturnIndexChannel(ChannelName);
	if (index == -1){
		Parse::printMessage("Channel: " + ChannelName + "\nThis channel is not in the channels list\n", RED);
	}
	_Channels.erase(_Channels.begin() + index);
	Parse::printMessage("Channel: " + ChannelName + "\nThis channel was deleted sucessfully!\n", GREEN);
}

int			Parse::ReturnIndexChannel(std::string ChannelName)
{
	for (unsigned long i = 0; i < _Channels.size(); i++)
	{
		if (!_Channels[i].getName().compare(ChannelName))
			return (i);
	}
	return (-1);
}
