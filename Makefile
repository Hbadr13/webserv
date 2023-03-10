NAME 		= webserv
SRC_FILE 	= main.cpp src/webserv.cpp src/webserv_util.cpp   src/request/Prasing_Request.cpp\
			src/Configfile/Configuration.cpp \
			src/Configfile/Configuration_util.cpp\
			src/Configfile/Location.cpp src/response/Response.cpp\
			src/response/run_cgi.cpp
OBJ_FILE	= $(SRC_FILE:.cpp=.o)
CC			= c++
CFLAG		=  -std=c++98 #-Wall -Wextra -Werror
HEADERS		= src/webserv.hpp src/request/Prasing_Request.hpp \
				src/Configfile/Configuration.hpp
RM			= rm -f

all 	: $(NAME)

%.o 	: %.cpp $(HEADERS)
		@$(CC) $(CFLAG) -c $< -o $@

$(NAME) : $(OBJ_FILE) $(HEADERS)
		@$(CC) $(CFLAG) $(OBJ_FILE)  -o $(NAME)
		@mv *.o OBJ
		@mv src/*.o OBJ
		@mv src/*/*.o OBJ

clean 	:
		@$(RM) OBJ/*.o

fclean : clean
		@$(RM) $(NAME)
		
re : fclean all
