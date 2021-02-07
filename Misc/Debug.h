//
// Created by user on 05.02.2021.
//

#ifndef FT_CONTAINERS_COLORS_H
# define FT_CONTAINERS_COLORS_H
# include <iostream>
# define RED  "\033[0;31m"
# define GREEN  "\033[0;32m"
# define ORANGE  "\033[0;33m"
# define BLUE  "\033[0;34m"
# define PURPLE  "\033[0;35m"
# define CYAN  "\033[0;36m"
# define LIGHTGRAY  "\033[0;37m"
# define DARKGRAY  "\033[1;30m"
# define LIGHTRED  "\033[1;31m"
# define LIGHTGREEN  "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define LIGHTBLUE  "\033[1;34m"
# define LIGHTPURPLE  "\033[1;35m"
# define LIGHTCYAN  "\033[1;36m"
# define WHITE  "\033[1;37m"
# define GRAY "\033[0;37m"
# define BOLD "\033[1m"
# define RES "\033[0m"
# define PRINT(x) { std::cout << GRAY "line " << __LINE__ << ": " RES << x << std::endl; }

#endif //FT_CONTAINERS_COLORS_H
