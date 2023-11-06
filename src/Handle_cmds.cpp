/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_cmds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:53:31 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/03 14:39:56 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Channel.hpp"

// int	Privmsg_cmd(std::vector<std::string> buf, Client client)
// {
// 	std::string	message;
// 	std::vector<std::string>::iterator Ite = buf.begin();

// 	std::advance(Ite, 2);
// 	for (Ite; Ite != buf.end(); Ite++)
// 		message = message + ' ' + *Ite;

// 	Parse::sendIrcMessage(message, client.getSocketFd());
// }

// int	Mode_cmd(std::vector<std::string> buf, Client client)
// {
	
// }

// int	Topic_cmd(std::vector<std::string> buf, Client client)
// {
	
// }

// int	Invite_cmd(std::vector<std::string> buf, Client client)
// {
	
// }

// int	Kick_cmd(std::vector<std::string> buf, Client client)
// {
	
// }

// int	Parse::Join_cmd(std::vector<std::string> buf, Client client)
// {
// 	std::string						ChannelName = buf[1];
// 	std::vector<Channel>::iterator	ch_it = _Channels.begin();
// 	bool							exist = false;

// 	while (ch_it != _Channels.end())
// 	{
// 		if (ChannelName == ch_it->getName())
// 		{
// 			Parse::try_joining(ch_it, buf, client);
// 			exist = true;
// 		}
// 		ch_it++;
// 	}
// 	if (!exist)
// 		Parse::_Channels.push_back(Channel(ChannelName, client.Getters(GETUSER)));
// }

// int	Parse::Handle_commands(char *buf, Client *client)
// {
// 	std::string					opts[6] = {"JOIN", "KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG"};
// 	int 						(*function[6])(std::vector<std::string> buf, Client client)	= {&Join_cmd, &Kick_cmd, &Invite_cmd, &Topic_cmd, &Mode_cmd, &Privmsg_cmd};
// 	std::vector<std::string>	parsed_buffer = Parse::Split_spc(buf);
	
// 	if (!buf)
// 	{
// 		std::cout << RED << "No buffer in Handle_commands" << std::endl;
// 		return 0;
// 	}
// 	for (int i = 0; i < 5; i++)
// 		if (parsed_buffer[0] == opts[i])
// 			return (function[i](parsed_buffer, *client));
// 	std::string	message;
// 	std::vector<std::string>::iterator Ite = parsed_buffer.begin();

// 	std::advance(Ite, 2);
// 	for (Ite; Ite != parsed_buffer.end(); Ite++)
// 		message = message + ' ' + *Ite;
// 	sendIrcMessage(message, client->getSocketFd());
// }