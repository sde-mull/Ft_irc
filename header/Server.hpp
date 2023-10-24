/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:50 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/24 20:24:51 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Lincludes.hpp"
#include "Parse.hpp"


class Server
{
    private:
        uint16_t            _port;
        std::string         _password;
        int                 _socketFd;
        struct sockaddr_in  *_address;
        int                 _acceptFd;
        
    public:
    //Server Constructors and destructors
        Server();
        Server(uint16_t port, std::string password);
        ~Server();
        Server(Server const &src);
        Server & operator=(Server const &rhs);
    //Server getters
        uint16_t        getPort(void) const;
        std::string     getPassword(void) const;
    
    //Server run
        int             startConnection(void);
        void            createIPv4Address(void);
        int             bound2BeServer(void);
        void            acceptConnection(void);

};

#endif