//
// Created by user on 05.02.2021.
//

#ifndef FT_CONTAINERS_COLORS_H
# define FT_CONTAINERS_COLORS_H
# include <iostream>
# define ESC "\033["
# define RED ESC "31m"
# define GREEN ESC "32m"
# define RES ESC "0m"
# define BOLD ESC "0;1m"
# define PRINT(x) { std::cout << "line " << __LINE__ << ": " << x << std::endl; }

#endif //FT_CONTAINERS_COLORS_H
