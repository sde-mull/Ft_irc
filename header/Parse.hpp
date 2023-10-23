/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:19:54 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/23 22:05:32 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include "Lincludes.hpp"

class Parse
{
    private:
        std::string         _password;  //password as a string
        std::string         _portStr;  //Port coming as a string
        uint16_t            _portNumb; //Another way to say unsigned shor integer
    public:
        //constructors and destructors
        Parse();
        Parse(std::string port, std::string password);
        Parse(Parse const &src);
        Parse & operator=(Parse const &rhs);
        ~Parse();

        //getters
        std::string     getPassword(void) const;
        std::string     getPortStr(void) const;
        uint16_t        getPortNumb(void) const;
        //Setters
        void            setPassword(std::string password);
        void            setPortStr(std::string portStr);
        void            setPortNumb(uint16_t portNumb);
        //Other Member Functions
        bool            checkArgParam(void);
        static  bool    checkNumbArgs(int const argc);
};

#endif