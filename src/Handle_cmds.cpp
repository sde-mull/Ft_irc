/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handle_cmds.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:53:31 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/10/30 12:15:19 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/Lincludes.hpp"
#include "../header/Cinclude.hpp"

int	Privmsg_cmd(char *buf, Client client)
{
	std::string	buffer = strdup_aftspc(buf);
	std::string	message = buffer.substr(buffer.find_first_of(' ', 1) + 1, buffer.size());

	sendIrcMessage(message, target_client);
}

int	Mode_cmd(char *buf, Client client)
{
	
}

int	Topic_cmd(char *buf, Client client)
{
	
}

int	Invite_cmd(char *buf, Client client)
{
	
}

int	Kick_cmd(char *buf, Client client)
{
	
}

int	Handle_commands(char *buf, Client client)
{
	if (!buf)
		return 0;
	std::string	opts[5] = {"KICK", "INVITE", "TOPIC", "MODE", "PRIVMSG"};
	int (*function[5])(char *buf, Client client) = {&Kick_cmd, &Invite_cmd, &Topic_cmd, &Mode_cmd, &Privmsg_cmd};
	std::string	buf_treated = strdup_tilspc(buf);

	for (int i = 0; i < 5; i++)
		if (buf_treated == opts[i])
			return (function[i](buf, client));
}