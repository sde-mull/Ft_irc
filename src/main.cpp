/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/23 22:14:38 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cinclude.hpp"

int main(int argc, char **argv)
{
    uint16_t port;
    std::string password;

    if (!Parse::checkNumbArgs(argc))    //non-member function do parse a verificar se tem args suficientes
        return (1);

    Parse parseArgs(argv[1], argv[2]);  //parametric constructor para guardar valores de port e password
    
    if (!parseArgs.checkArgParam())     //realização do parse dos argumentos
        return (2);
    
    password = parseArgs.getPassword(); //buscar o valor da password
    port     = parseArgs.getPortNumb(); //buscar o valor da port em unsigned int

    std::cout << port << std::endl;     //Verificar se foi tudo recebido
    std::cout << password << std::endl;
    
    //podem usar os parametros do parseArgs para ir buscar valores para utilizar no server, tanto a password como a port 
    return (0);
}