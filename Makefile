NAME_FT_STACK = test_stack_ft
NAME_FT_VECTOR = test_vector_ft
NAME_FT_MAP = test_map_ft

HEADERS_FILE = includes

HEADERS = \
			includes/map_fct.hpp \
			includes/map.hpp \
			includes/stack.hpp \
			includes/vector_fct.hpp \
			includes/vector.hpp \
			includes/utils.hpp \
			includes/iterator_traits.hpp \
			includes/iterator.hpp \
			includes/iterator_reverse.hpp

SRC_FT_MAP = srcs/main_map.cpp
SRC_FT_STACK = srcs/main_stack.cpp
SRC_FT_VECTOR = srcs/main_vector.cpp

OBJ_FT_MAP = ${SRC_FT_MAP:.cpp=.o}
OBJ_FT_STACK = ${SRC_FT_STACK :.cpp=.o}
OBJ_FT_VECTOR = ${SRC_FT_VECTOR :.cpp=.o}

.PHONY: all clean fclean re 

all:  $(NAME_FT_MAP) $(NAME_FT_STACK)  $(NAME_FT_VECTOR)

$(NAME_FT_MAP): $(OBJ_FT_MAP) $(HEADERS)
	clang++ $(OBJ_FT_MAP) -o $(NAME_FT_MAP)

$(NAME_FT_STACK): $(OBJ_FT_STACK) $(HEADERS)
	clang++ $(OBJ_FT_STACK) -o $(NAME_FT_STACK)

$(NAME_FT_VECTOR): $(OBJ_FT_VECTOR) $(HEADERS)
	clang++ $(OBJ_FT_VECTOR) -o $(NAME_FT_VECTOR)

$(OBJ_FT_MAP): %.o: %.cpp $(HEADERS)
	clang++ -Wall -Wextra -Werror -std=c++98 -I$(HEADERS_FILE) -c $< -o $@

$(OBJ_FT_STACK): %.o: %.cpp $(HEADERS)
	clang++ -Wall -Wextra -Werror -std=c++98 -I$(HEADERS_FILE) -c $< -o $@

$(OBJ_FT_VECTOR): %.o: %.cpp $(HEADERS)
	clang++ -Wall -Wextra -Werror -std=c++98 -I$(HEADERS_FILE) -c $< -o $@

clean:
	rm -f $(OBJ_FT_STACK) $(OBJ_FT_VECTOR) $(OBJ_FT_MAP)

fclean: clean
	rm -f $(NAME_FT_STACK) $(NAME_FT_VECTOR) $(NAME_FT_MAP)

re: fclean all