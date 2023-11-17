/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:19:54 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/17 01:11:00 by sde-mull         ###   ########.fr       */
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
	
		//Handle_cmds.cpp
		static  int 								Nick_cmd(std::vector<std::string> buf, Client client);
		static	int									Join_cmd(std::vector<std::string> buf, Client client);
		static	int									Handle_commands(char *buf, Client *client);
		static	int									Kick_cmd(std::vector<std::string> buf, Client client);
		static	int									Mode_cmd(std::vector<std::string> buf, Client client);
		static	int									Invite_cmd(std::vector<std::string> buf, Client client);
		static	int									Topic_cmd(std::vector<std::string> buf, Client client);
		
		static	int									try_joining(std::vector<Channel>::iterator ch_it, std::vector<std::string> buffer, Client client);
		static	std::vector<std::string>			Split_spc(char *buf);
		static  bool                        		checkArgParam(std::string port, std::string passsword);
		static  bool                        		checkNumbArgs(int const argc);
		static  int                         		printErrorMessage(std::string message, int typeError);
		static  void                        		printMessage(std::string message, std::string color = WHITE);
		static  void                        		addClient(int id);
		static  Client&                     		searchClientById(int id);
		static  int                         		ReturnClientById(int id);
		static  bool                        		CheckClientByNick(std::string nick);
		static  bool                        		CheckNickRules(std::string nick);
		static  std::vector<std::string>    		ft_split(char *buf, int received);
		static  int                         		sendIrcMessage(std::string message, int clientId);
		static	int									sendIrcNumeric(int i, std::string code, std::string str, Client client, Channel *channel = NULL);
		static  void                        		PrintAllClients(void);
		static  void                        		RemoveClient(int id);
		static 	std::string							SendCommandIRC(int i, std::string code, std::string str, Client client, Channel *channel = NULL);
		static  void								CreateNumerics(void);
		static  std::string							PrefixString(Client client, Channel channel);
		static int 									BroadcastChannel(int i, std::string code, std::string str, Client client, Channel *channel);
		static Client* 								ReturnClientByNick(std::string nick);
		static int 									Who_cmd(std::vector<std::string> buf, Client client);
		static int 									BroadcastWho(Client client, Channel *channel);
		static bool 								CheckPrivMessageArguments(Client client, int size, std::string str);
		static std::vector<int>						ReturnMessageTargets(std::string &target, Client client);
		static int									SearchTargetMessageId(std::string target, Client client);
		static int									SearchClientByNick(std::string target);
		static void									GetAllIdInChannel(std::string target, Client client, std::vector<int> &returnTargets, int flag = 0);
		static Channel*								ReturnChannelByName(std::string name);
		static void									GetOpsAndMembersTarget(std::string &target, Client client, std::vector<int> &returnTargets);
};

#endif