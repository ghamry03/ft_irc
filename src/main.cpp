/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 18:23:28 by kamin             #+#    #+#             */
/*   Updated: 2023/09/01 14:12:48 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <cstdlib>
#include <iostream>
#include <sstream>

bool validParams( int ac, char **av ) {
    bool valid_params = true;

    if ( ac != 3 ) {
        std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
        std::cout << "where 1 <= <port> <= 65535" << std::endl;
        valid_params = false;
    }
    ( void )av;
    // TODO: check valid port range
    return ( valid_params );
}
Server* serv;

static void sigHandler(int sigNum) {
    serv->exit(sigNum);
}

bool IRCserver( int port, std::string const & pass ) {
    Server ircserver = Server( port, pass );
    serv = &ircserver;
    try {
        ircserver.init();
    } catch ( std::exception const & e ) {
        std::cerr << "[" << e.what() << "]" << std::endl;
    }
    ircserver.run();

    return ( true );
}

int main( int ac, char **av ) {
    struct sigaction sigIntHandler;

   sigIntHandler.sa_handler = sigHandler;
   sigemptyset(&sigIntHandler.sa_mask);
   sigIntHandler.sa_flags = 0;

    if (sigaction(SIGINT, &sigIntHandler, NULL) == -1)
        std::cout << "problem with handler" << std::endl; 
        
    if ( validParams( ac, av )) {
        IRCserver( atoi( av[1] ) , av[2] );
    }
    return ( 0 );
}