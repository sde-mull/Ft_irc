/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:06:55 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/11/09 17:07:27 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Lincludes.hpp"

class Channel
{
	private:
			std::vector<std::string>	_users;
			std::vector<std::string>	_mods;
			std::string					_name;
			std::string 				_topic;
			// std::string 				_password;
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
};

#endif