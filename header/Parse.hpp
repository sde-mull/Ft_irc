/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:19:54 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/31 16:49:07 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include "Lincludes.hpp"

class Parse
{
    public:
		static std::vector<Channel>	_Channels;
	
        //constructors and destructors
        Parse();
        Parse(Parse const &src);
        Parse & operator=(Parse const &rhs);
        ~Parse();

        //Non-member functions
        static  bool    	checkArgParam(std::string port, std::string passsword);
        static  bool    	checkNumbArgs(int const argc);
        static  int     	printErrorMessage(std::string message, int typeError);

		//Handle_cmds.cpp
		static	int			Join_cmd(char *buf, Client client);
		static	int			Handle_commands(char *buf, Client *client);

		//Handle_cmds_utils.cpp
		static	int			sendIrcMessage(std::string message, int clientId);
		static	std::string	strdup_tilspc(char *buf);
		static	std::string	strdup_aftspc(char *buf);
		static	int			try_joining(std::vector<Channel>::iterator ch_it, std::string buffer, Client client);
};

#endif