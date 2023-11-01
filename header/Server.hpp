/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:50 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/01 19:21:58 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Lincludes.hpp"
#include "Parse.hpp"
#include "Client.hpp"


class Server
{
    private:
        uint16_t            _port;
        std::string         _password;
        int                 _socketFd;
        struct sockaddr_in  *_address;
        int                 _acceptFd;
        std::vector<Client> _clients;
        
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
        int             bindAndListen(void);
        int             acceptConnection(void);
    
    //Handling messages
        int      Handle_Message(Client *client);
        int      Check_Client(int fd);
};

#endif