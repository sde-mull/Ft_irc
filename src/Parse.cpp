/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:31:10 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/02 17:27:09 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"

std::vector<Client> Parse::_clients;

//Non-member functions of parse

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

int Parse::printErrorMessage(std::string message, int typeError)
{
    if (typeError)
        std::cerr << RED "Error: " << message << RESET << std::endl;
    return (typeError);
}

void    Parse::addClient(int id)
{
    _clients.push_back(Client(id));
}

Client&  Parse::searchClientById(int id)
{
    int index;

    for (int i = 0; i < _clients.size(); i++)
    {
        if (_clients[i].getSocketFd() == id){
            index = i;
            break ;
        }
    }
    return (_clients[index]);
}

bool  Parse::CheckClientByNick(std::string nick)
{
    for (int i = 0; i < _clients.size(); i++)
    {
        if (!_clients[i].getNick().compare(nick))
            return (false);
    }
    return (true);
}

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

void    Parse::PrintClientArgs(Client &client)
{
    if (client.f_pass)
        std::cout << "You have set the correct password " << GREEN "✔" RESET << std::endl;
    else
        std::cout << "You have not set the correct passoword " << RED "✘" RESET << std::endl;
    std::cout << "This is your Nick: ";
    if (client.getNick() != "\0")
        std::cout << GREEN << client.getNick() << " ✔" << RESET << std::endl;
    else
        std::cout << RED "✘" RESET << std::endl;
    std::cout << "This is your User: ";
    if (client.getUser() != "\0")
        std::cout << GREEN << client.getUser() << " ✔" << RESET << std::endl;
    else
        std::cout << RED "✘" RESET << std::endl;
}

std::vector<std::string>    Parse::ft_split(char *buf, int received)
{
    std::string nova;
    for (size_t j = 0; j < received; j++)
    {
        if (buf[j] == '\n')
            nova += ' ';
        if (buf[j] != '\n' && buf[j] != '\r')
            nova += buf[j];
    }
    std::istringstream ss(nova);
    std::vector<std::string> vec;
    std::string token;
    while (std::getline(ss, token, ' '))
        vec.push_back(token);
    return (vec);
}