/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:06:55 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/11 15:26:03 by sde-mull         ###   ########.fr       */
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
		
	public:
	
			Channel();
			Channel(std::string	name, std::string CreatingUser);
			~Channel();

			std::string	getName(void);
			void		addUser(std::string user);
			int			getMode(char c);
			int			invitedUsers(std::string user);
			int			IsUserMod(std::string user);
			int			SearchForUser(std::string user);
			void		rmUser(std::string user);
			std::string	getSuperUser(void);
			std::string getTopic(void);
			std::string getSymbol(void);
			std::string getPrefix(std::string nick);
			std::string getModeString(void);
};

#endif