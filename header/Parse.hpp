/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:19:54 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/23 17:14:00 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include "Lincludes.hpp"

class	WrongArgsNumb : public std::exception
{
	public:
		virtual const char* what() const throw();
};

class Parse
{
    private:
        std::string         _password;  //password as a string
        std::string         _portStr;  //Port coming as a string
        uint16_t            _portNumb; //Another way to say unsigned shor integer
    public:
        //constructors and destructors
        Parse();
        Parse(int argc, char *password, char *port);
        Parse(Parse const &src);
        Parse & operator=(Parse const &rhs);
        ~Parse();

        //getters
        std::string getPassword(void) const;
        std::string getPortStr(void) const;
        uint16_t    getPortNumb(void) const;
        //Setters
        void        setPassword(std::string password);
        void        setPortStr(std::string portStr);
        void        setPortNumb(uint16_t portNumb);
        //Other Member Functions
        void        checkArgs(int argc, char *password, char *port_str);
};

#endif