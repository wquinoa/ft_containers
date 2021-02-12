//
// Created by Filipp Ewseew on 1/30/21.
//

#include "Vector.hpp"
#include <vector>
#include <list>
//#include "BTree.hpp"
# include "List/List.hpp"
# include "Logger.hpp"
# include "BidirectionalIterator.hpp"
# include <list>

# define RANDOM_SIZE 13
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

/// VISIBILITY  todo vector test

template <typename T>

void vector_test(std::string const &filename)
{
	T tr;
#if (C_LOG == 1)
	Logger log(filename, "base test");
#endif
	(void)filename;
	PRINT("Current capacity is: " << tr.capacity())

	if (fork() == 0)
	{
		PRINT("empty vector.front() " << tr.front())
		PRINT("empty vector.back(): " << tr.back())
		exit(1);
	}
	wait(0);

		/* Reserve basic */
	tr.reserve(0);
	PRINT("Capacity after reserve(0) is " << tr.capacity())

	tr.reserve(4);
	PRINT("Capacity after reserve(4) is " << tr.capacity())

		/* Insertion-removal-access basic */
	std::vector<TEST_TYPE>::iterator it = test_random.begin();
	while (tr.size() < RANDOM_SIZE)
	{
		tr.push_back(*it);
		++it;
	}
	printContainer(tr,  "several push_back()");

	tr.insert(tr.begin() + 5, 10, test_random[0]);
	printContainer(tr, "insert(begin + 5, 10, n)");
	tr.erase(tr.begin() + 5, tr.begin() + 14);
	printContainer(tr, "erase(begin + 5, begin + 14)");

	tr.pop_back();
	printContainer(tr, "pop_back");
	PRINT("current size is: " << tr.size())
	PRINT("vector.at(5) is " << tr.at(5))
	PRINT("vector[2] is " << tr[2])
	try { tr.at(124); }
	catch (std::exception &e) { PRINT("vector.at(124) exception: " << e.what()) };
	PRINT("vector.front() is " << tr.front())
	PRINT("vector.back() is " << tr.back())


	PRINT("Current capacity is: " << tr.capacity())
	tr.resize(2000);
	PRINT("Resize(2000), capacity: " << tr.capacity() << ", size() == " << tr.size())
	printContainer(tr, "Reserve(2000)");
	tr.clear();
	PRINT("clear(), capacity: " << tr.capacity() << ", size() == " << tr.size())
	tr.assign(10, test_random[0]);
	printContainer(tr, "assign(10, 10)");
	tr.erase(tr.begin(), tr.begin() + 10);
	PRINT("erase(begin(), begin() + 10), capacity: " << tr.capacity() << ", size() == " << tr.size())
	printContainer(tr, "erase all");

	tr.assign(10, *(test_random.begin()));
	tr.clear();

	/* Undefined */
	if (fork() == 0)
	{
		PRINT("vector[2021] is " << tr[2021])
		std::cout << "erase 10 elements from size " << tr.size();
		tr.erase(tr.begin() + 5, tr.begin() + 15);
		exit(0);
	}
	wait(0);
}

/// VISIBILITY todo vector speed

template <typename T>
void	vectorBenchmark(std::string const &filename)
{
	T v;
#if (C_LOG == 1)
	Logger log(filename, "benchmark");
#endif
	(void)filename;

	/* Insertion */

	for (int i = 0; i < 319420; ++i)
		v.push_back(i);

	v.assign(35000, 350000);
	/* Deletion */

	while (v.size())
		v.pop_back();

	for (int i = 0; i < 31420; ++i)
		v.push_back(i);
	v.reserve(20);
	v.reserve(50000);
	while (v.size())
		v.erase(v.begin());
}

/// VISIBILITY todo list test

template <class T>
void listTest(std::string const & filename)
{
#if (C_LOG == 1)
	Logger log(filename, "base test");
#endif
	(void) filename;
	T l;

	PRINT( "list Max size is " << l.max_size());
	PRINT("Empty list front: " << l.front());
	PRINT("empty list back: " << l.back());


	for (int i = 0; i < 10; ++i)
		l.push_back(i);
	l.assign(5, 5);
	printContainer(l, "list.push_back()");
	PRINT("current size is: " << l.size());
	l.clear();
	PRINT("Size after list.clear(): " << l.size());


	std::cerr << RED << "DOUBLE FREE ON STD LIST" << RES << std::endl;
	if (fork() == 0)
	{
		PRINT("Erasing from an empty list, size: " << l.size());
		l.erase(l.begin());

		exit(0);
	}
	wait(0);
	PRINT("New elem: " << *l.insert(l.begin(), 21))

	std::vector<TEST_TYPE>::iterator it = test_random.begin();
	while (l.size() < RANDOM_SIZE)
	{
		l.push_back(*it);
		++it;
	}
	printContainer(l, "pushing 13 random elements");
	l.sort();
	printInReverse(l, "sorting 13 random elements");
	//l.reverse();
	//printContainer(l, "list.reverse()");

	//while (l.size())
		//l.pop_back();
	//PRINT("current size is: " << l.size());
	//printContainer(l, "list.pop_back() all");
}

/// VISIBILITY todo lists speed

template <typename T>
void	listBenchmark(std::string const &filename)
{
	T v;
	T v2;
#if (C_LOG == 1)
	Logger log(filename, "benchmark");
#endif
	(void)filename;

	/* Insertion */

	for (int i = 0; i < 619420; ++i)
		v.push_back(619420 + (i % 2) ? i : -i);

	v2.assign(500, 21);
	v2.assign(400, 19);

	typename T::iterator from = v2.begin();
	for (int i = 0; i < 200; ++i)
		from++;

	v.sort();
	v.merge(v2);
	//v.reverse();
	std::cerr << "possible leak " << "\033[31m" << &(*v2.begin()) << "\033[0m" << std::endl;
	//v.splice(from, v2);

	/* Deletion */
	//v.clear();
	//while (v.size() > 222)
		//v.erase(v.begin());
	//v.erase(v.begin(), v.end());

}

void sigsegvHandler(int sig)
{
	if (sig == SIGSEGV) {
		PRINT(RED << "sigsegv caught" << RES);
	}
	exit(1);
}

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

int main(int argc, char **argv)
{
	signal(SIGSEGV, sigsegvHandler);

	randomValues();

#if (TEST_THEIRS == 0)
//	vector_test<typeof(std_v)>(their_file + "vector");
//	vector_test<typeof(ft_v)>(my_file + "vector");
//	doDiff("vector");
//
	listTest<typeof(std_l)>(their_file + "list");
	listTest<typeof(ft_l)>(my_file + "list");
	doDiff("list");

//	std::string leaks = "leaks " + std::string(argv[0] + 2);
//	std::cout << std::endl;
//
//	PRINT("Press enter to run [" << "\033[0;33m" << leaks << "\033[0m" << "]")
//	std::cin.ignore();
//	system(leaks.c_str());

#else

	PRINT("           benchmark          ")
	vectorBenchmark<typeof(std_v)>(their_file + "vector");
	vectorBenchmark<typeof(ft_v)>(my_file + "vector");
	doDiff("vector");

	listBenchmark<typeof(std_l)>(their_file + "list");
	listBenchmark<typeof(ft_l)>(my_file + "list");
	doDiff("list");

#endif
	(void)argc;
	(void)argv;

	return 0;
}
