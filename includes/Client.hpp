#pragma once

#include "Server.hpp"
#include "AClient.hpp"
#include <queue>
#include <unistd.h>

class Client : public AClient {
private:

public:
    Client( const AClient& );
    ~Client( void );

    /* Methods */
    /* Getters */
    /* Setters */
};
