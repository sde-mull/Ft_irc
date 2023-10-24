/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:31:10 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/24 12:52:02 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"

//Constructors and Destructors

Parse::Parse(void)
{
    std::cout << B_GREEN "Parse default contrutor called" RESET << std::endl;
}

Parse::~Parse(void)
{
    std::cout << B_RED "Parse destructor called" RESET << std::endl;
}

Parse::Parse(Parse const &src)
{
    *this = src;
}

Parse & Parse::operator=(Parse const &rhs)
{
    (void)rhs;
    return (*this);
}

//Non-member functions of parse

bool Parse::checkArgParam(std::string port, std::string password)
{
    std::cout << port << std::endl;
    if (port.find_first_not_of("0123456789") != std::string::npos)
    {
        std::cerr << B_RED "Error:\n" B_YELLOW "Port must be an integer" RESET << std::endl;
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
