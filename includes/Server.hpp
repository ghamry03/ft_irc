/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:23:20 by kamin             #+#    #+#             */
/*   Updated: 2023/07/22 13:54:57 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <fcntl.h>
#include <string>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <map>
#include <cstring>
#include <vector>
#include <ctime>
#include "Client.hpp"
#include "Replies.hpp"
#include "Channel.hpp"

#ifndef MAX_CLIENTS
#define MAX_CLIENTS 4

std::vector<std::string> split_string( string str , string delim );
std::string    ft_itoa( int num );
// typedef std::vector< Channel > ChanVector;
typedef std::map< std::string, Channel> chan_map;
typedef std::vector< pollfd > PollVector;

#endif


class Server {
    private:
        typedef void ( Server::*cmdFun )( Client const &, std::string const & );
        typedef std::map< std::string const, cmdFun > CmdMap;

        const int                            _port;
        const std::string                    _pass;

        int                                  _listen_socket;
        size_t                               _connectionCount;

        PollVector                           _poll_fds;
        struct sockaddr_in                   _hint;
        std::map<int, Client>                _clientMap;
        // ChanVector                           _channels;
        chan_map                             _channels;
        CmdMap                               _commands;

        int                                 _initServer( void );
        int                                 _acceptConnection( void );
        void                                _runServer( void );
        void                                _parseMessage( Client &new_socket , char *buff );
        std::map<int, Client>::iterator     _getClient( const int fd );
        std::string                         _createMessage( Client client, string command );
        void                                _joinChannel( Client client, string name);
        void                                _broadcastJoin( Client client , Channel chan , string name );
        Client  *_findClientByNick( std::map<int, Client> &clients , string nick ) const;
        void    _pong( Client client);
        // ChanVector::iterator                _findChannel( chan_map & channels , std::string name ) const;

        void                                _privmsg( string full_command , Client client );

        /**              COMMANDS FUN TYPEDEF                **/

        /**              COMMANDS HELPER FUN                 **/
        bool  _addCommandFunction( std::string const & keyValue, cmdFun );
        bool  _initCommandsFunctions( void );
        void  _executeCommand( Client const & client, std::string const & message );

        /**                   COMMANDS FUN                   **/
        void    _joinCommand( Client const & user, std::string const & command );
        void    _kickCommand( Client const & client, std::string const & msg );

        bool    _sendMessage( Client client, std::string const & msg );

    public:
        typedef std::map<string, void (Client::*)( string )>::iterator command_it;
        Server( const int port, const string pass );
        // ~Server();
        int getListenSocket( void ) const;
        size_t    getConnectionCount ( void ) const;
};
