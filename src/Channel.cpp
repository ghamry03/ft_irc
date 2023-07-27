/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kamin <kamin@student.42abudhabi.ae>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:07:23 by kamin             #+#    #+#             */
/*   Updated: 2023/07/25 14:36:20 by kamin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Channel.hpp"
#include "Client.hpp"
#include <iostream>
#include <map>
#include <string>

Channel::Channel( string name , string topic , string key , bool inv , bool top )
    : _name( name ) , _topic( topic ) , _key( key ) , _isInviteOnly( inv ) , _topicOpOnly( top ) {}

Channel::~Channel( void ) {}

void	Channel::setName( std::string name ) {
    _name = name;
}

void	Channel::setTopicMode( bool mode ) {
    _topicOpOnly = mode;
}

void	Channel::setInviteMode( bool mode ) {
    _isInviteOnly = mode;
}

const std::string Channel::getName( void ) const {
    return ( _name );
}

const std::string Channel::getTopic( void ) const {
    return ( _topic );
}

// const std::string Channel::getMode( void ) {
//     return ( _mode );
// }

void Channel::addInvitation( std::string nick ) {
    _invitations.push_back( nick );
}

void Channel::_removeInvitation( std::string nick ) {
    StrVector::iterator    nick_pos = std::find(_invitations.begin(), _invitations.end(), nick);
    if ( nick_pos != _invitations.end())
        _invitations.erase(nick_pos);
}

void Channel::addUser( std::string const & nick, Client const & client ) {
    _clients.insert( std::pair<std::string, const Client *>( nick, &client ) );
}

string  Channel::getUsersStr( void ) const {
    std::string  nicks;

    for ( _clients_const_it it = _clients.begin(); it != _clients.end(); ++it ) {
        std::string nick = it->first;
        nicks.append( " " + nick );
    }

    return ( nicks );
}

Channel::StrVector Channel::getNicks( void ) const {
    std::vector< std::string > nicks;

    // TODO: fix it later to make it more efficient
    for ( _clients_const_it it = _clients.begin(); it != _clients.end(); it++ ) {
        std::string nick = it->first;
        nicks.push_back( nick );
    }
    return ( nicks );
}

bool Channel::removeUser( std::string const & nick ) {
    if ( _clients.find( nick ) == _clients.end() )
        return ( false );
    _clients.erase( nick );
    return ( true );
}

const Client *Channel::getClientByNick( const std::string nick) {
    const Client *cli = (_clients.find( nick )->second);
    return (cli);
}

// std::string constructMessage( Client target , std::string const & msg ) {
//     std::string finalMsg = msg + target.getNick() + " :" + 
// }

bool    Channel::sendMessage( Server& t , std::string const & origin , std::string const & msg ) const {
    bool sendRet = false;
    for (_clients_const_it it = _clients.begin(); it != _clients.end(); it++)
    {
        const Client *curr_client = it->second;
        std::string finalMsg = origin + "PRIVMSG " + _name + " :" + msg;
        DEBUG_MSG(finalMsg << std::endl);
        DEBUG_MSG("CLIENT NAME: " << it->first << "\nCLIENT FD: " << curr_client->getClientSocket() << std::endl);
        // if (*split_string(origin , ":").begin() != curr_client.getNick())
        sendRet =  t._sendMessage( *curr_client , finalMsg );
    }
    return ( sendRet );
}