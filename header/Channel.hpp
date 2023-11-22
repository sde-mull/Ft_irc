/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:06:55 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/22 12:39:35 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Lincludes.hpp"
#include "Parse.hpp"

class Channel
{
	private:
			int									_maxusers;
			std::string							_name;
			std::string 						_topic;
			std::string 						_password;
			std::string							_superUser;
			std::vector<std::string>			_mods;
			std::vector<std::string>			_users;
			std::vector<std::string>			_invitedUsers;
			std::map<char, int>					_modes;
			std::map<std::string, std::string>	_uprefix;
		
	public:
	
			Channel();
			Channel(std::string	name, std::string CreatingUser);
			Channel(std::string name, std::string CreatingUser, std::string pass);
			~Channel();

			// Get values functions
			int									getMode(char c);
			int									getUserLimit(void);
			int									getUserAmount(void);
			std::string							getName(void);
			std::string							getTopic(void);
			std::string 						getSymbol(void);
			std::string 						getPrefix(std::string nick);
			std::string							getSuperUser(void);
			std::string 						getModeString(void);
			std::vector<std::string> 			getMods();
			std::vector<std::string> 			getUsers();
			std::vector<std::string>			getUsersList();
			std::map<std::string, std::string>	getPrefixs(void);
					
			//Check functions		
			int 								CheckIsSuperUser(std::string user);
			int									CheckIsMod(std::string user);
			int									CheckIsUser(std::string user);
			int 								CheckInvite(std::string user);
			int									check_pass(std::string pass);	

			//add functions
			void								addUser(std::string user);
			int									addModder(std::string user);
			int									inviteUser(std::string user);

			// Change values functions
			void								setPassword(std::string	pass);
			int									changeMode(std::vector<std::string> buf, Client client);
			int									changeTopic(std::vector<std::string> buf);
			int									changePrefix(std::string user, char opt);
			int									invitedUsers(std::string user);
			int									ChangeNickUserList(std::string newNick, Client client);
			void								ChangeNickModsList(std::string newNick, Client client);
			void								ChangeNickInvitedList(std::string newNick, Client client);
			void								ChangeNickPrefixList(std::string newNick, Client client);

			// Remove functions
			int									rmUser(std::string user);
			int									rmModder(std::string user);
			int									rmInvitedUsers(std::string user);
			int									rmPrefixes(std::string user);
		
			//Display information
			void								displayModes(Client client, std::vector<Channel>::iterator ch_it);
			void								displayTopic(Client client, std::vector<Channel>::iterator ch_it);


			//modes functions
			int									mode_password(std::vector<std::string> buf, std::map<char, int>::iterator ite, Client client);
			int									mode_addmod(std::vector<std::string> buf, Client client);
			int									mode_userlimit(std::vector<std::string> buf, std::map<char, int>::iterator ite, Client client);
};

#endif