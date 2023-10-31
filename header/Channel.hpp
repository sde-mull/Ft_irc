/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:06:55 by pcoimbra          #+#    #+#             */
/*   Updated: 2023/10/31 17:03:57 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Lincludes.hpp"

class Channel
{
	private:
			std::vector<std::string>	_users;
			std::string					_name;
			std::string 				_topic;
			// std::string 				_password;
			std::string					_superUser;
			std::vector<std::string>	_BanUsers;
		
	public:
	
			Channel();
			Channel(std::string	name, std::string CreatingUser);
			~Channel();

			std::string	getName(void);
			int			Banneduser(std::string user);
			void		addUser(std::string user);

};

#endif