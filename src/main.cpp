/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/23 17:23:58 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cinclude.hpp"


int main(int argc, char **argv)
{
    Parse parse(argc, argv[1], argv[2]);
    // Server server;
    // Client client;
    try
    {
        // server.run();
        //parse.checkArgs(argc, argv[1], argv[2]);
        
    }
    catch(const std::exception& e) 
    {
        std::cout << e.what() << std::endl;
    }
    return (0);
}