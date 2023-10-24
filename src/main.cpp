/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/23 22:46:39 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cinclude.hpp"

int main(int argc, char **argv)
{
    if (!Parse::checkNumbArgs(argc) || !Parse::checkArgParam(argv[1], argv[2]))
        return (1);
    /*Se chegou até aqui quer dizer que passou no parse dos argumentos que foram mandados.
    para a port vir inteiro só temos de fazer um atoi e não justifica uma classe inteira para isso.
    A classe parse a ideia seria para usar ao longo do código só com static functions(non-member functions)
    Qualquer parse que se tenha de fazer no código podemos acrescentar nessa classe ou reutilizar alguma que 
    já foi feita sem ter de criar um novo objeto. Ou seja, uma class utils.
    */
    return (0);
}