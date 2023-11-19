/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-mull <sde-mull@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:46:01 by sde-mull          #+#    #+#             */
/*   Updated: 2023/10/25 13:24:43 by sde-mull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cinclude.hpp"

void	handlesignal(int sig)
{
	(void)sig;
	std::cout << "signal" << std::endl;
	exit(0);
}

int main(int argc, char **argv)
{
	system("clear"); //It clears the terminal
	if (!Parse::checkNumbArgs(argc) || !Parse::checkArgParam(argv[1], argv[2])) //Checks if it's all right with the password and the port 
		return (1);
	Server server((uint16_t)atoi(argv[1]), argv[2]); // Constructor of the server sending Port and password as arguments to save
	signal(SIGINT, handlesignal); //CTRL-C
	signal(SIGQUIT, handlesignal); //CTRL-'\'
	server.startConnection(); //Starts the connection part of the server and returns at the end of the connection

}