/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:50 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/02 11:49:04 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "Lincludes.hpp"
#include "Parse.hpp"
#include "Client.hpp"

class Server;

typedef void (Server::*function) (Client &client, std::string str);

class Server
{
    private:
        uint16_t            _port;
        std::string         _password;
        int                 _socketFd;
        struct sockaddr_in  *_address;
        int                 _acceptFd;
        std::map<std::string, function> m;
        
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
        int      Handle_Message(Client &client);
        std::vector<std::string>    ft_split(char *buf, int received);
        void    ft_pass(Client &client, std::string str);
        void    ft_nick(Client &client, std::string str);
        void    ft_user(Client &client, std::string str);
};

#endif
