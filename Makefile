NAME 		= 	webserv
SRC_FILE 	= 	src/Configfile/Configuration_util.cpp\
				src/Configfile/Configuration.cpp \
				src/request/Request.cpp\
				src/response/Content_type.cpp\
				src/Configfile/Location.cpp\
				src/response/Response.cpp\
				src/response/run_cgi.cpp\
				src/Webserv.cpp \
				src/Client.cpp\
				main.cpp

OBJ_FILE	=	$(SRC_FILE:.cpp=.o)

CC			=	c++

CFLAG		=	-Wall -Wextra -Werror -std=c++98

HEADERS		=	src/Configfile/Configuration.hpp\
				src/request/Request.hpp\
				src/Configfile/Location.hpp\
				src/response/Response.hpp\
				src/Webserv.hpp\
				src/Client.hpp

RM			=	rm -f

all:			$(NAME)

%.o:			%.cpp $(HEADERS)
				$(CC) $(CFLAG) -c $< -o $@

$(NAME):		$(OBJ_FILE) $(HEADERS)
				$(CC) $(CFLAG) $(OBJ_FILE)  -o $(NAME)

clean:
				$(RM) $(OBJ_FILE)

fclean:		clean
				$(RM) $(NAME)

re: fclean all
