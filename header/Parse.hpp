/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:19:54 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/24 19:13:44 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include "Lincludes.hpp"

class Parse
{
    public:
        //constructors and destructors
        Parse();
        Parse(Parse const &src);
        Parse & operator=(Parse const &rhs);
        ~Parse();

        //Non-member functions
        static  bool    checkArgParam(std::string port, std::string passsword);
        static  bool    checkNumbArgs(int const argc);
        static  int     printErrorMessage(std::string message, int typeError);
};

#endif