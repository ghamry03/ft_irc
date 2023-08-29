#include "Channel.hpp"

Channel::Channel( const std::string& name, const std::string& topic ) :
    _name( name ), _topic( topic ), _key( "" ), _isInviteOnly( false ), _isTopicOnly( true ), _isKeyOnly( false ) {}

Channel::~Channel() {}

/* PRIVATE Methods */

void Channel::_sendNames( AClient* client ) {
    client->addMsg( RPL_NAMREPLY( client->getNick() + " = " + _name , names(*this)) );
    client->addMsg( RPL_ENDOFNAMES( client->getNick() + " " + _name ) );
}

/* PUBLIC Methods */
void Channel::addUser( AClient* client ) {
    std::string nick = client->getNick();
    // TODO: get origin from client member function created by @niño
    std::string joinMsg( client->getOrigin() + " JOIN " + _name + "\r\n" );
    client->addMsg( joinMsg );
    if ( !_operators.size() ) {
        _operators.insert( std::make_pair( "@" + nick, client ) );
        client->addMsg( ":0.0.0.0 MODE " + _name + " +t\r\n" );
    }
    else {
        client->addMsg( RPL_TOPIC( client->getNick() + " " + _name , _topic ) );
        client->addMsg( RPL_TOPICWHOTIME( client->getNick() + " " + _name + " dan!~d@localhost 1547691506" ) ); // TODO: use time and get origin and stor in the channel at creation time
        addMsg( client->getNick() , joinMsg);
        _clients.insert( std::make_pair( nick , client ) );
    }
    _sendNames( client );
}

void Channel::promoteClient( std::string& nick ) {
     std::map<std::string, AClient*>::iterator it = _clients.find( nick );
    if ( it != _clients.end() ) {
        _operators.insert( std::make_pair( "@" + it->second->getNick(), it->second ) );
        _clients.erase( it );
    }
}

void Channel::demoteClient( std::string& nick ) {
     std::map<std::string, AClient*>::iterator it = _operators.find( nick);
    if ( it != _operators.end() ) {
        _clients.insert( std::make_pair( it->second->getNick(), it->second ) );
        _operators.erase( it );
    }
}

void Channel::kickUser( const std::string& nick, const std::string& msg ) {
    std::map<std::string, AClient*>::iterator it;

    it = _clients.find( nick );
    if ( it != _clients.end() ) {
	it->second->addMsg( msg );
	_clients.erase( it );
    }

    it = _operators.find( "@" + nick );
    if ( it != _operators.end() ) {
	it->second->addMsg( msg );
	_clients.erase( it );
    }
}

void Channel::addInvitation( const std::string& nick ) {
    if ( !isInvited( nick ) )
	_invitations.push_back( nick );
}

void Channel::removeInvitation( const std::string& nick ) {
    std::vector<std::string>::iterator begin = _invitations.begin();
    std::vector<std::string>::iterator end = _invitations.end();
    for ( std::vector<std::string>::iterator it = begin; it != end; it++ )
        if ( *it == nick )
            _invitations.erase( it );
}

void Channel::addMsg( const std::string& cli , const std::string& msg ) {
    std::map<std::string, AClient*>::iterator it;

    for ( it = _operators.begin(); it != _operators.end(); it++ )
        if ( "@" + cli != it->first )
            it->second->addMsg( msg );
    for ( it = _clients.begin(); it != _clients.end(); it++ )
        if (cli != it->second->getNick())
	        it->second->addMsg( msg );
}

bool  Channel::isInvited( const std::string& nick ) const {
    std::vector<std::string>::const_iterator begin = _invitations.begin();
    std::vector<std::string>::const_iterator end = _invitations.end();
    for ( std::vector<std::string>::const_iterator it = begin; it != end; it++ )
        if ( *it == nick )
            return ( true );
    return ( false );
}

bool  Channel::isMember( const std::string& nick ) const {
    if ( _clients.find( nick ) == _clients.end() )
	return( false );
    return ( true );
}

bool  Channel::isOperator( const std::string& nick ) const {
    if ( _operators.find( "@" + nick ) == _operators.end() )
	return ( false );
    return ( true );
}

bool  Channel::isInviteOnly( void ) const { return ( _isInviteOnly ); }

bool  Channel::isTopicOnly( void ) const { return ( _isTopicOnly ); }

bool  Channel::isKeyOnly( void ) const { return ( _isKeyOnly ); }

const std::string& Channel::getName( void ) const { return ( _name ); }

const std::string& Channel::getTopic( void ) const { return ( _topic ); }

const std::string& Channel::getKey( void ) const { return ( _key ); }

void Channel::setName( const std::string& name ) { _name = name; }

void Channel::setKey( const std::string& key ) { _key = key; }

void Channel::setInviteMode( bool state ) { _isInviteOnly = state; }

void Channel::setTopicMode( bool state ) { _isTopicOnly = state; }

void Channel::setKeyMode( bool state ) { _isKeyOnly = state; }

std::string names(const Channel& chan) {
    std::string aggNames;

    for (std::map<std::string , AClient*>::const_iterator it = chan._operators.begin(); it != chan._operators.end(); it++) {
        aggNames += it->first + " ";
        std::cout << "NICKKKKK [" << it->first << "]" << std::endl;
    }
    for (std::map<std::string , AClient*>::const_iterator it = chan._clients.begin(); it != chan._clients.end(); it++)
        aggNames += it->first + " ";
    aggNames.erase(aggNames.end() - 1);
    return( aggNames );
}
