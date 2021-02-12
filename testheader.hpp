//
// Created by user on 12.02.2021.
//

#ifndef FT_CONTAINERS_TESTHEADER_HPP
#define FT_CONTAINERS_TESTHEADER_HPP

#include <map>
#include <vector>
#include <list>

#include "BTree.hpp"
# include "List/List.hpp"
# include "Vector.hpp"

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
std::string my_file("ft_");
std::string their_file("std_");
std::string diff("diff " + my_file + "* " + their_file + "* ");

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
	PRINT(diff);
	PRINT("\033[0;37m" << " -----------  diff ----------- \n")
	system(diff.c_str());
	PRINT(" -----------  end  ----------- " << "\033[0m")
	unlink((my_file + type).c_str());
	unlink((their_file + type).c_str());
	g_perfdiff = 0;
	(void)type;
}

#endif //FT_CONTAINERS_TESTHEADER_HPP
