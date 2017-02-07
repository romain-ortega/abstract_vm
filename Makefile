NAME = abstract_vm

OBJ_DIR = obj
SRC_DIR = src

SRC = main.cpp \
			Syntax.cpp \
			Parser.cpp
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

FLAGS = -Wall -Wextra -Werror -std=c++11 -I $(shell pwd)/inc/
FLAGS_BOOST = -I ~/.brew/include/boost

$(NAME): $(OBJ_DIR) $(OBJ)
	clang++ $(FLAGS) $(FLAGS_BOOST) -o $(NAME) $(OBJ)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	c++ $(FLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
