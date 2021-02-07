//
// Created by user on 05.02.2021.
//

#ifndef FT_CONTAINERS_COLORS_H
# define FT_CONTAINERS_COLORS_H
# include <iostream>

# ifndef TEST_THEIRS
#  define TEST_THEIRS 0
# endif

# ifndef PRINT_COLORS
#  define PRINT_COLORS !TEST_THEIRS
# endif

# define SETCOLOR(x)  ( PRINT_COLORS ? x : "" )
# define RED  SETCOLOR("\033[0;31m")
# define LIGHTRED "\033[1;31m"
# define GREEN  SETCOLOR("\033[0;32m")
# define ORANGE  "\033[0;33m"
# define BLUE  SETCOLOR("\033[0;34m")
# define PURPLE  "\033[0;35m"
# define LIGHTPURPLE "\033[1;35m"
# define CYAN  "\033[0;36m"
# define LIGHTGREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define LIGHTBLUE "\033[1;34m"
# define LIGHTCYAN "\033[1;36m"
# define WHITE "\033[1;37m"
# define GRAY SETCOLOR("\033[0;37m")
# define DARKGRAY "\033[1;30m"
# define BOLD SETCOLOR("\033[1m")
# define RES SETCOLOR("\033[0m")
# define PRINT(x) { std::cout << GRAY << "line " << __LINE__ << ": " << RES << x << std::endl; }

#endif //FT_CONTAINERS_COLORS_H
