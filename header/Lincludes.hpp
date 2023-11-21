/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lincludes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoimbra <pcoimbra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:48:09 by sde-mull          #+#    #+#             */
/*   Updated: 2023/11/21 16:04:38 by pcoimbra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINCLUDES_HPP
# define LINCLUDES_HPP

//COLOR MACROS

#define BLACK		"\033[30m"
#define RED			"\033[31m"
#define GREEN		"\033[32m"
#define YELLOW		"\033[33m"
#define BLUE		"\033[34m"
#define MAGENTA		"\033[35m"
#define CYAN		"\033[36m"
#define WHITE		"\033[37m"
#define RESET		"\033[0m"

#define B_BLACK		"\033[1;30m"
#define B_RED		"\033[1;31m"
#define B_GREEN		"\033[1;32m"
#define B_YELLOW	"\033[1;33m"
#define B_BLUE		"\033[1;34m"
#define B_MAGENTA	"\033[1;35m"
#define B_CYAN		"\033[1;36m"
#define B_WHITE		"\033[1;37m"
#define RESET		"\033[0m"

//CLIENT MACROS

#define	GETUSER		    	1
#define	GETNICK		    	2
#define GETCLIENTFD     	3
#define GETAUTH         	4
#define GETPASS         	5

#define SETUSER         	6
#define SETNICK         	7
#define SETCLIENTFD     	8
#define SETAUTH         	9
#define SETPASS         	10

//Parser MACROS

#define	GENERICERROR		-2

#define NOCHANNELERR		-4
#define	NOUSERERR			-5
#define NOTENOUGHPERMSERR	-6
#define	NOTENOUGHARGS		-7
#define	WRONGARGSERR		-8

//Channel modes flags

#define	MODEPASSWORD		'k'
#define	MODEINVITEONLY		'i'
#define	MODETOPIC			't'
#define	MODECHANNELOP		'o'
#define	MODEUSERLIMIT		'l'

#define MAXBUFF             4000

#include <stdio.h>  
#include <cstring>
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h> 
#include <arpa/inet.h>
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h> 
#include <iostream>
#include <stdint.h>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <deque>
#include <list>
#include <algorithm>
#include <signal.h>

char		                        **ft_split(char const *s, char c);

void                                free_2d(char **arr);
char                                *remove_newline(char *str);

#endif