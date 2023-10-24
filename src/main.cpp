/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde.mull@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/24 19:11:24 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cinclude.hpp"

int main(int argc, char **argv)
{
    system("clear");
    if (!Parse::checkNumbArgs(argc) || !Parse::checkArgParam(argv[1], argv[2]))
        return (1);
    Server server((uint16_t)atoi(argv[1]), argv[2]);
    return (server.startConnection());
}