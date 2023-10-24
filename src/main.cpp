/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreis-de <rreis-de@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/24 11:52:09 by rreis-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cinclude.hpp"

// int main(int argc, char **argv)
// {
//     /* if (!Parse::checkNumbArgs(argc) || !Parse::checkArgParam(argv[1], argv[2]))
//         return (1); */
//     /*Se chegou até aqui quer dizer que passou no parse dos argumentos que foram mandados.
//     para a port vir inteiro só temos de fazer um atoi e não justifica uma classe inteira para isso.
//     A classe parse a ideia seria para usar ao longo do código só com static functions(non-member functions)
//     Qualquer parse que se tenha de fazer no código podemos acrescentar nessa classe ou reutilizar alguma que 
//     já foi feita sem ter de criar um novo objeto. Ou seja, uma class utils.
//     */
//     Server ServerB("", 2000);
//     int resultserver = ServerB.bound2BeServer();
//     if (resultserver == 0)
//         std::cout << BLUE "Server Connected" << std::endl;
//     else
//         std::cout << RED "NIET SERVER" << std::endl;
    
//     // Client ClientA("127.0.0.1", 2000);

//     // int resultclient = ClientA.Connect_Socket();

//     // if (resultclient == 0)
//     //     std::cout << GREEN "Connection successfull" << std::endl;
//     // else
//     //     std::cout << RED "No Connection" << std::endl;
    
//     ServerB.Accept();

//     return (0);
// }

int main(int args, char **argv)
{
    Client ClientA("127.0.0.1", 2000);

    int resultclient = ClientA.Connect_Socket();
    if (resultclient == 0)
        std::cout << GREEN "Client Connected" << std::endl;
    else
        std::cout << RED "NIET CLIENT" << std::endl;

    ClientA.Send("GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n");

    ClientA.Receive();

    return (0);
}