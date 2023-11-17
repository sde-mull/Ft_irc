/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:06:55 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/17 14:22:35 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Lincludes.hpp"
#include "Parse.hpp"

class Channel
{
	private:
			std::vector<std::string>	_users;
			std::map<std::string, std::string> _uprefix;
			std::vector<std::string>	_mods;
			std::string					_name;
			std::string 				_topic;
			std::string 				_password;
			std::string					_superUser;
			std::map<char, int>			_modes;
			std::vector<std::string>	_invitedUsers;
			int							_maxusers;
		
	public:
	
			Channel();
			Channel(std::string	name, std::string CreatingUser);
			~Channel();

			int				getIsMod(std::string user);
			int				getUserAmount(void);
			int				getUserLimit(void);
			int				getIsUser(std::string user);
			std::string		getName(void);
			std::string		getSuperUser(void);
			std::string		getTopic(void);
			std::vector<std::string>	getUsersList();
			int 			CheckInvite(std::string user);
			
			void			addUser(std::string user);
			int				addModder(std::string user);
			int				rmUser(std::string user);
			int				rmModder(std::string user);
			void			displayModes(void);

			int				invitedUsers(std::string user);
			int				inviteUser(std::string user);
			void			setPassword(std::string	pass);
			int				changeTopic(std::vector<std::string> buf);

			//parsing change modes
			int				changeMode(char c, std::vector<std::string> buf);

			int				mode_password(std::vector<std::string> buf, char mode, std::map<char, int>::iterator ite);
			int				mode_addmod(std::vector<std::string> buf, char mode, std::map<char, int>::iterator ite);
			int				mode_userlimit(std::vector<std::string> buf, char mode, std::map<char, int>::iterator ite);
			int				check_pass(std::string pass);

      //idk
			std::string 	getSymbol(void);
			std::map<std::string, std::string> getPrefixs(void);
			std::string 	getPrefix(std::string nick);
			std::string 	getModeString(void);
			int				getMode(char c);
			std::vector<std::string> getUsers();
			std::vector<std::string> getMods();

			
};

#endif