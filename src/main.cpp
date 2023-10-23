/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/23 14:44:47 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cinclude.hpp"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    if (argc != 2)
    {
        std::cout << B_RED "Error:\n" B_YELLOW "Usage: ./ircserv <port> <password>\n" \
                "<port>:" B_WHITE " The port number that the server will be listening to for incoming IRC connections\n" \
                B_YELLOW "<password>:" B_WHITE " The connection password" RESET << std::endl;
        return (1);
    }
    Server server;
    Client client;
    return (0);
}