NAME := test.out

SRC := main.cpp

OBJ := $(SRC:.cpp=.o)

IDIRS := Iterator Misc

INCL := $(foreach d, $(IDIRS), -I $d) -I .

CXX = clang++

CXXFLAGS = -Wall -Werror -Wextra $(INCL)

ifdef TEST
	CXXFLAGS += -D TEST_THEIRS=1
endif

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

### TESTS ###

run:
	./$(NAME)

test:
	$(MAKE) re run TEST=1
