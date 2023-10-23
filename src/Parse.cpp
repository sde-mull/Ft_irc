/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:31:10 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/23 22:11:00 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse.hpp"

//Constructors and Destructors

Parse::Parse(void) : _password("default"), _portStr("6666"), _portNumb(6666)
{
    std::cout << B_GREEN "Parse default contrutor called" RESET << std::endl;
}

Parse::Parse(std::string port, std::string password) : _portStr(port), _password(password), _portNumb(6666)
{
    std::cout << B_GREEN "Parse parametric contrutor called" RESET << std::endl;
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
    this->_password = rhs.getPassword();
    this->_portNumb = rhs.getPortNumb();
    this->_portStr = rhs.getPortStr();
    return (*this);
}

//Getters

std::string Parse::getPassword(void) const
{
    return (_password);
}

std::string Parse::getPortStr(void) const
{
    return (_portStr);
}

uint16_t Parse::getPortNumb(void) const
{
    return (_portNumb);
}

//Setters

void    Parse::setPassword(std::string password)
{
    this->_password = password;
}

void    Parse::setPortStr(std::string portStr)
{
    this->_portStr = portStr;
}

void    Parse::setPortNumb(uint16_t portNumb)
{
    this->_portNumb = portNumb;
}

//Other functions of parse

bool Parse::checkArgParam(void)
{
    this->_portNumb = atoi(this->_portStr.c_str());
    
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

/*
linha 17 e 22, _port_numb = 6666 como default port, maior parte das ports abaixo de 1024 estao ocupadas por isso convem ficar acima desse valor
*/ 