#pragma once

#include "Server.hpp"

class Channel {
private:
    std::string _name;
    std::string _topic;
    std::string _key;
    bool        _isInviteOnly;
    bool        _isTopicOnly;
    std::vector<std::string>        _invitations;
    std::map<std::string, Client*>  _clients;

public:
    Channel( const std::string& name, const std::string& topic );
    ~Channel();

    /* Methods */
    void addUser( const std::string& nick, Client& client );
    void kickUser( const std::string& nick, const std::string& msg );
    void addInvitation( const std::string& nick );
    void removeInvitation( const std::string& nick );
    void addMsg( const std::string& msg );

    /* Getters */
    bool  isInvited( const std::string& nick ) const;
    bool  isMember( const std::string& nick ) const;
    bool  isOperator( const std::string& nick ) const;
    bool  isInviteOnly( void ) const;
    bool  isTopicOnly( void ) const;
    const std::string& getName( void ) const;
    const std::string& getTopic( void ) const;
    const std::string& getKey( void ) const;

    /* Setters */
    void setName( const std::string& );
    void setInviteMode( bool );
    void setTopicMode( bool );
};
