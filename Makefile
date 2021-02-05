NAME := ft_containers.out

SRC := main.cpp

OBJ := $(SRC:.cpp=.o)

IDIRS := Iterator Misc

INCL := $(foreach d, $(IDIRS), -I $d) -I .

CXX = clang++

CXXFLAGS = -Wall -Werror -Wextra $(INCL)

ifdef TEST
	CXXFLAGS += -D TEST_THEIRS
endif

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@
	./$(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

### TESTS ###

list:
	$(CXX) $(CXXFLAGS) -c list.cpp -o list.o
	$(CXX) $(CXXFLAGS) list.o -o $@.out

test:
	$(MAKE) re TEST=1
