NAME		=	ircserv

SRCS		=	main.cpp			\
				Server.cpp 			\
				Client.cpp 			\
				utils.cpp			\

SRCS_DIR    =   ./src/

OBJS		=	$(addprefix $(SRCS_DIR), $(SRCS:.cpp=.o))

CXX			=	c++

CXXFLAGS	=	-Wall -Werror -Wextra -std=c++98 -Iincludes

RM			=	rm -f

all			:	$(NAME)

elliot:
	@echo "\033[0;32m"
	@echo " ▄▄▄▄    ▒█████   ███▄    █   ██████  ▒█████   ██▓ ██▀███     ▓█████  ██▓     ██▓     ██▓ ▒█████  ▄▄▄█████▓"
	@echo "▓█████▄ ▒██▒  ██▒ ██ ▀█   █ ▒██    ▒ ▒██▒  ██▒▓██▒▓██ ▒ ██▒   ▓█   ▀ ▓██▒    ▓██▒    ▓██▒▒██▒  ██▒▓  ██▒ ▓▒"
	@echo "▒██▒ ▄██▒██░  ██▒▓██  ▀█ ██▒░ ▓██▄   ▒██░  ██▒▒██▒▓██ ░▄█ ▒   ▒███   ▒██░    ▒██░    ▒██▒▒██░  ██▒▒ ▓██░ ▒░"
	@echo "▒██░█▀  ▒██   ██░▓██▒  ▐▌██▒  ▒   ██▒▒██   ██░░██░▒██▀▀█▄     ▒▓█  ▄ ▒██░    ▒██░    ░██░▒██   ██░░ ▓██▓ ░ "
	@echo "░▓█  ▀█▓░ ████▓▒░▒██░   ▓██░▒██████▒▒░ ████▓▒░░██░░██▓ ▒██▒   ░▒████▒░██████▒░██████▒░██░░ ████▓▒░  ▒██▒ ░ "
	@echo "░▒▓███▀▒░ ▒░▒░▒░ ░ ▒░   ▒ ▒ ▒ ▒▓▒ ▒ ░░ ▒░▒░▒░ ░▓  ░ ▒▓ ░▒▓░   ░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░░▓  ░ ▒░▒░▒░   ▒ ░░   "
	@echo "▒░▒   ░   ░ ▒ ▒░ ░ ░░   ░ ▒░░ ░▒  ░ ░  ░ ▒ ▒░  ▒ ░  ░▒ ░ ▒░    ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░ ▒ ░  ░ ▒ ▒░     ░    "
	@echo " ░    ░ ░ ░ ░ ▒     ░   ░ ░ ░  ░  ░  ░ ░ ░ ▒   ▒ ░  ░░   ░       ░     ░ ░     ░ ░    ▒ ░░ ░ ░ ▒    ░      "
	@echo " ░          ░ ░           ░       ░      ░ ░   ░     ░           ░  ░    ░  ░    ░  ░ ░      ░ ░           "
	@echo "      ░                                                                                                    "
	@echo "\033[0m"

$(NAME)		:	$(OBJS) elliot
				@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)


clean		:
				$(RM) $(OBJS)

fclean		:	clean
				$(RM) $(NAME)

re			:	fclean all
