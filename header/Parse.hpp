/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:19:54 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/13 14:09:08 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include "Lincludes.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Client;
class Channel;
class Parse
{
	private:
		static std::vector<Client> _clients;
	public:
		static std::vector<Channel>	_Channels;
	
		//constructors and destructors
		Parse();
		Parse(Parse const &src);
		Parse & operator=(Parse const &rhs);
		~Parse();



		//Handle_cmds.cpp
		static	int		Join_cmd(std::vector<std::string> buf, Client client);
		static	int		Handle_commands(char *buf, Client *client);
		static	int		Kick_cmd(std::vector<std::string> buf, Client client);
		static	int		Mode_cmd(std::vector<std::string> buf, Client client);
		static	int		Invite_cmd(std::vector<std::string> buf, Client client);
		static	int		Topic_cmd(std::vector<std::string> buf, Client client);
		
		//Handle_cmds_utils.cpp
		static	int									try_joining(std::vector<Channel>::iterator ch_it, std::vector<std::string> buffer, Client client);
		static	std::vector<std::string>			Split_spc(char *buf);
		// static	std::vector<std::string>::iterator	vectorFind(std::vector<std::string> vector, std::string needle);
		/* static	int							sendIrcMessage(std::string message, int clientId);
		static	int							try_joining(std::vector<Channel>::iterator ch_it, std::vector<std::string> buffer, Client client);
		static	std::vector<std::string>	Split_spc(char *buf); */
		//Non-member functions
		static  bool                        checkArgParam(std::string port, std::string passsword);
		static  bool                        checkNumbArgs(int const argc);
		static  int                         printErrorMessage(std::string message, int typeError);
		static  void                        printMessage(std::string message, std::string color = WHITE);
		static  void                        addClient(int id);
		static  Client&                     searchClientById(int id);
		static  int                         ReturnClientById(int id);
		static  bool                        CheckClientByNick(std::string nick);
		static  bool                        CheckNickRules(std::string nick);
		static  std::vector<std::string>    ft_split(char *buf, int received);
		static  int                         sendIrcMessage(std::string message, int clientId);
		static  void                        PrintAllClients(void);
		static  void                        RemoveClient(int id);
		static 	std::string					SendCommandIRC(std::string code, Client &client, Channel &channel, std::string str, int i);
		static  void						CreateNumerics(void);

};

#endif