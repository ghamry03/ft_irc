#include "Commands/Join.hpp"

Join::Join( Server& ircServ ) : ICommand( ircServ ) {}

Join::~Join( void ) {

}
static strPair findChanKey( std::vector<std::string> tokens ) {
    std::vector<std::string>::iterator it = tokens.begin();
    strPair keyPair;

    keyPair.first = *it;

    if (tokens.size() == 2)
        keyPair.second = *(++it);
    return ( keyPair );
}

static bool expectedArgs( size_t argNum ) {
    return ( argNum < 3 && argNum > 0 ? true : false );
}

static bool allowedToJoin( Channel *chan , AClient* client , strPair keyPair ) {
    bool allowed = true;

    if ( chan->isInviteOnly() && !chan->isInvited( client->getNick() ) ) {
        allowed = false;
        client->addMsg( ERR_INVITEONLYCHAN( client->getNick() + " " + chan->getName() ) );
    }

    if ( allowed && chan->isKeyOnly() && keyPair.second.compare(chan->getKey()) ){
        allowed = false;
        client->addMsg( ERR_BADCHANNELKEY( client->getNick() + " " + chan->getName() ) );
    }

    return ( allowed );
}

void Join::execute( AClient* client, const std::string & rawCommand ){
    std::vector<std::string> tokens = utils::split(rawCommand , " ");

    if ( expectedArgs( tokens.size() )) {
        strPair keyPair = findChanKey( tokens );
        std::map<const std::string, Channel*>::iterator channel = _ircServ._channels.find( keyPair.first );
        bool errorFound = false;
        if ( channel == (_ircServ._channels).end() ) {
            if ( (keyPair.first.at(0) != '#' && keyPair.first.at(0) != '&') || keyPair.first.find_first_of(" ,") != std::string::npos ) {
                client->addMsg(ERR_BADCHANMASK(client->getIp() , keyPair.first));
                errorFound = true;
            }
            else
                _ircServ._addChannel( keyPair.first , "" );
        }

        if (!errorFound) {
            Channel *chan = _ircServ._channels.find( keyPair.first )->second;
            if ( allowedToJoin(chan, client , keyPair) ) {
                chan->addUser( client );
            }
            client->addChannel( keyPair.first );
        }
    }
}

void Join::clearCmd( void ) {}
