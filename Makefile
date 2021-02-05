NAME := ft_containers

SRC := main.cpp

OBJ := $(SRC:.cpp=.o)

INCL := -I.

CXX = clang++

CXXFLAGS = -Wall -Werror -Wextra $(INCL)

ifdef TEST
	CXXFLAGS += -D TEST_THEIRS
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./$(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test:
	$(MAKE) re TEST=1
	diff *_1.txt *_2.txt || rm *_1.txt *_2.txt

.PHONY: all, clean fclean re test