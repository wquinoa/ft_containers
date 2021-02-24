//
// Created by user on 12.02.2021.
//

#ifndef FT_CONTAINERS_TESTHEADER_HPP
#define FT_CONTAINERS_TESTHEADER_HPP

# include <iostream>
# include <string>
# include <sstream>
# include <iomanip>

# include <map>
# include <list>
# include <vector>
# include <stack>
# include <queue>

# include <unistd.h>

# include "Map.hpp"
# include "List.hpp"
# include "Vector.hpp"
# include "Stack.hpp"
# include "Queue.hpp"

# include "Logger.hpp"
# include "BidirectionalIterator.hpp"

# define RANDOM_SIZE 12
# ifndef STRING_TEST
#  define STRING_TEST 0
# endif
#  if (STRING_TEST == 1)
#   define TEST_TYPE std::string
#  else
#   define TEST_TYPE int
#  endif

static std::vector<TEST_TYPE> test_random;
static std::stringstream leak_addr;

typedef std::vector<TEST_TYPE> std_v;
typedef ft::Vector<TEST_TYPE> ft_v;

typedef std::list<TEST_TYPE> std_l;
typedef ft::List<TEST_TYPE> ft_l;

typedef std::map<TEST_TYPE, TEST_TYPE> std_mp;
typedef ft::Map<TEST_TYPE, TEST_TYPE> ft_mp;

typedef std::queue<TEST_TYPE> std_q;
typedef ft::Queue<TEST_TYPE> ft_q;

typedef std::stack<TEST_TYPE> std_st;
typedef ft::Stack<TEST_TYPE> ft_st;


std::string my_file("ft_");
std::string their_file("std_");

void	randomValues()
{
	srand(time(nullptr));

# if (STRING_TEST == 1)
	std::string syllables[10] = {"bin", "cla", "za", "for", "lon", "lo", "sta", "try", "gi", "chu"};

	while (test_random.size() < RANDOM_SIZE)
	{
		typeof(TEST_TYPE) word;
		for (int i = 0; i < 3; i++) {  // words of 3 syllables
			word += syllables[rand() % 10];
		}
		test_random.push_back(word);
	}
#  else
	while (test_random.size() < RANDOM_SIZE)
		test_random.push_back(rand() % RANDOM_SIZE);
# endif
}

void	doDiff(const char *type)
{
	std::string diff("diff " + my_file + type + ' ' + their_file + type);
	PRINT(diff);
	PRINT("\033[0;37m" << " -----------  diff ----------- \n")
	system(diff.c_str());
	PRINT(" -----------  end  ----------- " << "\033[0m")
	unlink((my_file + type).c_str());
	unlink((their_file + type).c_str());
	g_perfdiff = 0;
	(void)type;
}

template <class T1, class T2>
std::ostream &operator<< (std::ostream &os, const ft::pair<T1, T2> p)
{
	os << '{' << p.first << ',' << p.second << '}';
	return os;
}

template <class T1, class T2>
std::ostream &operator<< (std::ostream &os, const std::pair<T1, T2> p)
{
    os << '{' << p.first << ',' << p.second << '}';
    return os;
}

template <typename T>
void printContainer(T &v, const std::string & operationName)
{
	typename T::iterator it;

	PRINT("size is " << v.size());
	std::cout << "container elements after " << operationName << ": " << std::endl;
	for (it = v.begin(); it != v.end(); ++it)
		std::cout << *it << "; ";
	std::cout << "\n" << std::endl;
}

template <typename T>
void printInReverse(T &v, const std::string & operationName)
{
	typename T::reverse_iterator it;

	PRINT("size is " << v.size());
	std::cout << "REVERSE container elements after " << operationName << ": " << std::endl;
	for (it = v.rbegin(); it != v.rend(); ++it)
		std::cout << *it << "; ";
	std::cout << "\n" << std::endl;
}


#endif //FT_CONTAINERS_TESTHEADER_HPP
