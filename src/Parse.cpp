/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:31:10 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/14 15:36:31 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"

std::vector<Client> Parse::_clients;

//Non-member functions of parse

// std::vector<std::string>::iterator	vectorFind(std::vector<std::string> vector, std::string needle)
// {
// 	std::vector<std::string>::iterator ite;

// 	for (ite = vector.begin(); ite != vector.end(); ite++)
// 		if (*ite == needle)
// 			return ite;
// 	return (vector.end());
// }

/*
checkArgParam is a function that will check:
-> If the port is a number between 0 and 65535
-> If the port exists
-> If the port isn't different from a number
-> If the password exists 
*/

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
	int index;

	for (int i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].GettersInt(GETCLIENTFD) == id){
			index = i;
			break ;
		}
	}
	return (_clients[index]);
}

/*
checkClientByNick wll search inside the vector of clients by nick.
Returns false in case it finds an equal nick
Returns true in case it doesn't find an equal nick
*/
bool  Parse::CheckClientByNick(std::string nick)
{
	for (int i = 0; i < _clients.size(); i++)
	{
		if (!_clients[i].Getters(GETNICK).compare(nick))
			return (false);
	}
	return (true);
}

/*
CheckNickRules will check if the nickname chosen is respecting the nickname rules.
*/
bool Parse::CheckNickRules(std::string str)
{
	if (str[0] == '#' || str[0] == '&' || str[0] == '$' || str[0] == ':')
		return (false);
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ' || str[i] == ',' || str[i] == '*' || str[i] == '?'\
		|| str[i] == '!' || str[i] == '@' || str[i] == '.')
			return (false);
	}
	return (true);
}

/*
quem fez que explique aqui
*/

std::vector<std::string>    Parse::ft_split(char *buf, int received)
{
	std::string nova;
	std::vector<std::string> vec;
	std::string token;
	
	for (size_t j = 0; j < received; j++)
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
	std::cout << "Sending message: " << message << std::endl;
	if (send(clientId, message.c_str(), message.length(), 0) == -1)
		exit(1);
	return 0;
}

int	Parse::sendIrcNumeric(int i, std::string code, std::string str, Client client, Channel *channel)
{
	std::string message = Parse::SendCommandIRC(i, code, str, client, channel) + "\r\n";
	std::cout << "Sending message: " << message << std::endl;
	if (send(client.GettersInt(GETCLIENTFD), message.c_str(), message.length(), 0) == -1)
		exit(1);
	return 0;
}

void Parse::PrintAllClients(void)
{
	for (int i = 0; i < _clients.size(); i++)
		std::cout << "Client with the id " << _clients[i].GettersInt(GETCLIENTFD) << " is online!" << std::endl;
}

int  Parse::ReturnClientById(int id)
{
	for (int i = 0; i < _clients.size(); i++)
	{
		if (_clients[i].GettersInt(GETCLIENTFD) == id)
			return (i);
	}
	return (-1);
}

void    Parse::RemoveClient(int id)
{
	std::string nick;

	nick = Parse::searchClientById(id).Getters(GETNICK);
	for (int i = 0; i < _clients.size(); i++)
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
	
}


