#pragma once

#ifndef REPLIES_HPP
# define REPLIES_HPP

# define RPL_NOTOPIC( ip ,arg ) std::string(":" + ip + " 331 ") + arg + std::string(" :No topic is set\r\n")
# define RPL_TOPIC( arg , topic ) std::string(":0.0.0.0 332 ") + arg + std::string(" :") + topic + std::string("\r\n")
# define RPL_TOPICWHOTIME( arg ) std::string(":0.0.0.0 333 ") + arg + std::string("\r\n")
# define RPL_INVITING( ip, arg ) ( ":" + ip + " 341 " + (std::string)arg + "\r\n" )
# define RPL_NAMREPLY( arg , users ) std::string(":0.0.0.0 353 ") + arg + std::string( " :" ) + users + std::string("\r\n")
# define RPL_ENDOFNAMES( arg ) std::string(":0.0.0.0 366 ") + arg + std::string( " :End of /NAMES list\r\n" )

# define ERR_MULTIPLEPARAMS( ip, arg ) ( ":" + ip + " 400 " + (std::string)arg + " :Could not process multiple invalid parameters\r\n") // -> cutom NUMERIC_REPLY using ERR_UNKNOWNERROR
# define ERR_NOSUCHNICK( ip, arg ) ( ":" + ip + " 401 " + (std::string)arg + " :No such nick\r\n")
# define ERR_NOSUCHCHANNEL( ip, arg ) ( ":" + ip + " 403 " + (std::string)arg + " :No such channel\r\n")
# define ERR_USERNOTINCHANNEL( ip, arg ) ( ":" + ip + " 441 " + (std::string)arg + " :User not on channel\r\n")
# define ERR_ERRONEUSNICKNAME( ip, arg ) (":" + ip + " 432 ") + arg + std::string(" :Erroneous Nickname\r\n")
# define ERR_NOTONCHANNEL( ip, arg ) ( ":" + ip + " 442 " + (std::string)arg + " :You're not on channel\r\n")
# define ERR_USERONCHANNEL( ip, arg ) ( ":" + ip + " 443 " + (std::string)arg + " :is already on channel\r\n")
# define ERR_NICKNAMEINUSE( arg ) std::string(":0.0.0.0 433 nick ") + arg + std::string(" :Nickname is already in use\r\n")
# define ERR_NEEDMOREPARAMS( ip, arg ) ( ":" + ip + " 461 " + (std::string)arg + " :Not enough parameters\r\n")
# define ERR_ALREADYREGISTERED( arg ) std::string(":0.0.0.0 462 ") + arg + std::string(" :You may not reregister\r\n")
# define ERR_PASSWDMISMATCH( arg ) std::string(":0.0.0.0 464 ") + arg + std::string(" :Password incorrect\r\n")
# define ERR_INVITEONLYCHAN( arg ) std::string(":0.0.0.0 473 ") + arg + std::string(" :Cannot join channel (+i) - invite only\r\n")
# define ERR_BADCHANNELKEY( arg ) std::string(":0.0.0.0 475 ") + arg + std::string(" :Cannot join channel (+k) - bad key\r\n")
# define ERR_BADCHANMASK(ip , arg) ( ":" + ip + " 476 " + (std::string)arg + " :Bad channel mask.\r\n")
# define ERR_CHANOPRIVSNEEDED( ip, arg ) ( ":" + ip + " 482 " + (std::string)arg + " :You're not a channel operator\r\n")

# define ERR_UMODEUNKNOWNFLAG( ip, arg ) ( ":" + ip + " 501 " + (std::string)arg + ":Unknown MODE flag\r\n")
# define ERR_INVALIDKEY( ip, arg ) ( ":" + ip + " 525 " + (std::string)arg + ":Key is not well-formed\r\n")

#endif
