/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:31:10 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/02 14:29:24 by sde-mull         ###   ########.fr       */
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
    std::cerr << RED "Error:\n" << message << std::endl;
    return (typeError);
}

void    Parse::addClient(int id)
{
    _clients.push_back(Client(id));
}

Client&  Parse::searchClient(int id)
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
