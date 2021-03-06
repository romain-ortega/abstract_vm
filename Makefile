NAME = abstract_vm

OBJ_DIR = obj
SRC_DIR = src

SRC = main.cpp \
			Parser.cpp \
			Exceptions.cpp \
			Expression.cpp \
			CallStack.cpp \
			Factory.cpp
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))

FLAGS = -Wall -Wextra -Werror -std=c++11 -O2 -pedantic -I $(shell pwd)/inc/ -I ~/.brew/include
BOOST = -L ~/.brew/lib/ -lboost_program_options

$(NAME): $(OBJ_DIR) $(OBJ)
	clang++ $(FLAGS) $(BOOST) -o $(NAME) $(OBJ)

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
