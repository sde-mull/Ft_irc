/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:50 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/06 23:41:56 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Lincludes.hpp"
#include "Parse.hpp"
#include "Client.hpp"
#include "Exceptions.hpp"

class Server;

typedef void (Server::*function) (Client &client, std::string str);

class Server
{
    private:
        uint16_t                        _port;
        std::string                     _password;
        int                             _serverSocketFd;
        struct sockaddr_in              *_address;
        int                             _acceptFd;
        std::map<std::string, function> m;
        fd_set                          _currentSockets;
        
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
        void            CreatingSocket(int domain, int type, int protocol);
        void            creatingIPv4Address(void);
        int             bindAndListenServer(void);
        int             acceptConnection(void);
        int             ServerRunning(void);
    
    //Handling messages
        int      Handle_Message(Client &client);
        void    ft_pass(Client &client, std::string str);
        void    ft_nick(Client &client, std::string str);
        void    ft_user(Client &client, std::string str);
        void    Client_Authenticate(Client &client, char *buf, int received);
        int     Call_Functions(Client &client, char *buf, int received);
};

#endif
