/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:50 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/23 16:51:58 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Lincludes.hpp"

class Server
{
    private:

        int                 _socket_fd;
		struct sockaddr_in  *_address;
        int                 _acceptFd;
        
    public:

        Server();
        Server(char *ip, int port);
        ~Server();
        Server(Server const &src);
        Server & operator=(Server const &rhs);

        int     bound2BeServer(void);
        void    Accept(void);
};

#endif