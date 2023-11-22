NAME		= ircserv
OBJ_PATH	= obj

SRCS		= $(shell find src/ -name '*.cpp')

OBJS		= $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(basename $(SRCS))))
INCLUDES	= header/

CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -I$(INCLUDES) -std=c++98 #-fsanitize=address
RM			= rm -f

all: $(NAME)

$(OBJ_PATH)/%.o:%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I $(INCLUDES) -I /usr/local/include -c -o $@ $<

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@  $^

init:
	@make re
	@./ircserv 3456 pass123

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re r m