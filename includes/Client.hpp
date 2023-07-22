/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommohame < ommohame@student.42abudhabi.ae> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:56:23 by kamin             #+#    #+#             */
/*   Updated: 2023/06/10 01:57:26 by ommohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>

class Client
{
private:
    int            _client_socket;
    std::string    _nick;
    std::string    _user;
    std::string    _pass;
    struct sockaddr_in* _pV4Addr;
    std::string    _ip;
    size_t        _msgSent;
    struct addrinfo *_servinfo;
    bool        _isRegistered;


public:
    Client( int listen_socket, struct sockaddr_in hint );
    // ~Client( void );

        /* METHODS */
    void    incMsgSent( void );
    int     joinChannel( std::string chan );

        /* GETTERS */
    int         getClientSocket( void )     const;
    size_t      getMsgSent( void )          const;
    std::string getUser( void )             const;
    std::string getPass( void )             const;
    std::string getNick( void )             const;
    std::string getIp( void )               const;
    bool        getRegisteredStatus( void ) const;

        /* SETTERS */
    void    setPass( std::string newPass );
    void    setNick( std::string newNick );
    void    setUser( std::string newUser );
    void    setAddrInfo( void );
};