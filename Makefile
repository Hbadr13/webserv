NAME 		= webserv
SRC_FILE 	= main.cpp
OBJ_FILE	= $(SRC_FILE:.cpp=.o)
CC			= c++
CFLAG		= #-Wall -Wextra -Werror -std=c++98
HEADERS		= include/webserv.hpp
RM			= rm -f

all 	: $(NAME)

%.o 	: %.cpp $(HEADERS)
		$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(OBJ_FILE) $(HEADERS)
		$(CC) $(CFLAG) $(OBJ_FILE)  -o $(NAME)

clean 	:
		$(RM) $(OBJ_FILE)

fclean : clean
		$(RM) $(NAME)

re : fclean all