/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:19:54 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/02 14:28:08 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include "Lincludes.hpp"
#include "Client.hpp"

class Client;
class Parse
{
    private:
        static std::vector<Client> _clients;
    public:
        //Non-member functions
        static  bool    checkArgParam(std::string port, std::string passsword);
        static  bool    checkNumbArgs(int const argc);
        static  int     printErrorMessage(std::string message, int typeError);
        static  void    addClient(int id);
        static  Client&  searchClientById(int id);
        static  bool    CheckClientByNick(std::string nick);
        static  bool    CheckNickRules(std::string nick);
};

#endif