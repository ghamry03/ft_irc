#pragma once

#include "Server.hpp"
#include <deque>

class Server;
class Channel {
    friend std::string names(const Channel& chan);
private:
    std::string _name;
    std::string _topic;
    std::string _key;
    std::string _topicAuthor;
    Server&     _ircServ;
    time_t      _topicSetTime;
    bool        _isInviteOnly;
    bool        _isTopicOnly;
    bool        _isKeyOnly;
    std::vector<std::string>        _invitations;
    std::map<std::string, AClient*>  _clients;
    std::map<std::string, AClient*>  _operators;

    /* PRIVATE Methods */
    void _sendNames( AClient* client );

public:
    Channel( Server& ircServ, const std::string& name, const std::string& topic );
    ~Channel();

    /* PUBLIC Methods */
    void addUser( AClient* client );
    void removeUser( const std::string& nick );
    void promoteClient( std::string& nick );
    void demoteClient( std::string& nick );
    void kickUser( const std::string& nick, const std::string& msg );
    void addInvitation( const std::string& nick );
    void removeInvitation( const std::string& nick );
    void addMsg( const std::string& cli , const std::string& msg );
    void updateUserNick( const std::string& );

    /* Getters */
    bool  isInvited( const std::string& nick ) const;
    bool  isMember( const std::string& nick ) const;
    bool  isOperator( const std::string& nick ) const;
    bool  isInviteOnly( void ) const;
    bool  isTopicOnly( void ) const;
    bool  isKeyOnly( void ) const;
    const std::string& getName( void ) const;
    const std::string& getTopic( void ) const;
    const std::string& getKey( void ) const;
    const std::string getTopicAuthor( void ) const;
    time_t getTopicTime( void ) const;
    const std::string getTopicReply( void ) const;
    size_t getUsersCount( void ) const;

    /* Setters */
    void setName( const std::string& );
    void setKey( const std::string& );
    void setInviteMode( bool );
    void setTopicMode( bool );
    void setTopic( AClient* client, const std::string& topic );
    void setKeyMode( bool );
};
