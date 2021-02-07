//
// Created by Filipp Ewseew on 1/30/21.
//

#include "Vector.hpp"
#include <vector>
#include <list>
//#include "BTree.hpp"
# include "List.hpp"
# include "Logger.hpp"
# include "BidirectionalIterator.hpp"
# include <list>

# define RANDOM_SIZE 13
# define STRING_TEST 0
#  if (STRING_TEST == true)
#   define TEST_TYPE std::string
#  else
#   define TEST_TYPE int
#  endif

static std::vector<TEST_TYPE> test_random(RANDOM_SIZE);

template <typename T>
void vector_test(std::string const &filename)
{
	T tr;
#ifdef TEST_THEIRS
	Logger log(filename, "vector base test");
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

	tr.insert(tr.begin() + 5, 10, *(test_random.begin()));
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
	tr.assign(10, *(test_random.begin()));
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

template <typename T>
void	vectorBenchmark(std::string const &filename)
{
	T v;
#ifdef TEST_THEIRS
	Logger log(filename, "vector benchmark");
#endif
	(void)filename;

	/* Insertion */

	for (int i = 0; i < 19420; ++i)
		v.push_back(TesterClass(i, '*'));

	/* Deletion */

	while (v.size())
		v.erase(v.begin());
}

template <class T>
void listTest(std::string const & filename)
{
#ifdef TEST_THEIRS
	Logger log(filename, "list base test");
#endif
	(void) filename;
	T l;
	typename T::iterator it;

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



	if (fork() == 0)
	{
		PRINT("Erasing from an empty list, size: " << l.size());
		PRINT(RED "DOUBLE FREE SOON" RES)
		l.erase(l.begin());

		exit(0);
	}
	wait(0);
	PRINT("New elem: " << *l.insert(l.begin(), 21))

	size_t s = 0;
	while (l.size() < 13) {
		l.push_front(22 + (s % 3) * 2 + (((s % 2) * (s % 4) ? 1 : -1)));
		s = l.size();
	}
	printContainer(l, "pushing 13 random elements");
	l.sort();
	printInReverse(l, "sorting 13 random elements");
	l.reverse();
	printContainer(l, "list.reverse()");

	//while (l.size())
	//	l.pop_back();
	//PRINT("current size is: " << l.size());
	//printContainer(l, "list.pop_back() all");
}


template <typename T>
void	listBenchmark(std::string const &filename)
{
	T v;
	T v2;
#ifdef TEST_THEIRS
	Logger log(filename, "list benchark test");
#endif
	(void)filename;

	/* Insertion */

	for (int i = 0; i < 219420; ++i)
		v.push_back(i);

	v2.assign(500, 21);
	v2.assign(400, 19);

	typename T::iterator from = v2.begin();
	for (int i = 0; i < 200; ++i)
		from++;

	v.sort();
	v.reverse();
	v.merge(v2);
	//v.splice(from, v2);

	/* Deletion */

	//while (v.size() > 222)
		//v.erase(v.begin());
	v.erase(v.begin(), v.end());

}

void sigsegvHandler(int sig)
{
	if (sig == SIGSEGV) {
		PRINT(RED << "sigsegv caught" << RES);
	}
	exit(1);
}

# if (STRING_TEST == 1)

void 	generateRandomStrings()
{
	std::string syllables[10] = {"bin", "cla", "za", "for", "lon", "lo", "sta", "try", "gi", "chu"};

	while (test_random.size() < RANDOM_SIZE)
	{
		typeof(TEST_TYPE) word;
		for (int i = 0; i < 3; i++) {  // words of 3 syllables
			word += syllables[rand() % 10];
		}
		test_random.push_back(word);
	}
}
#  else
void	generateRandomNumbers()
{


	srand(time(0));

	if (std::is_integral<TEST_TYPE>::value || std::is_floating_point<TEST_TYPE>::value) {
		while (test_random.size() < RANDOM_SIZE)
			test_random.push_back(rand() % RANDOM_SIZE);
	}
}
# endif

int main(int argc, char **argv)
{
	signal(SIGSEGV, sigsegvHandler);
	std::string my_file("my_test_1.txt");
	std::string their_file("std_test_2.txt");
	std::string diff("diff " + my_file + ' ' + their_file);

# if (STRING_TEST == 1)
	generateRandomStrings();
#  else
	generateRandomNumbers();
# endif
	unlink(my_file.c_str());
	unlink(their_file.c_str());


	shitty::Vector<int> mine;
	std::vector<int> theirs;

	g_perfdiff = 0;
	vector_test<typeof(mine)>(my_file);
	vector_test<typeof(theirs)>(their_file);



	shitty::List<TEST_TYPE>	my_l;
	std::list<TEST_TYPE>	std_l;

	g_perfdiff = 0;
	listTest<typeof(my_l)>(my_file);
	listTest<typeof(std_l)>(their_file);

	g_perfdiff = 0;

	PRINT("Commence list benchmark")
	listBenchmark<typeof(my_l)>(my_file);
	listBenchmark<typeof(std_l)>(their_file);
#ifdef TEST_THEIRS
	PRINT(BLUE "diff: " RES)
	system(diff.c_str());

	//g_perfdiff = 0;
	//vectorBenchmark<typeof(mine)>(my_file);
	//vectorBenchmark<typeof(theirs)>(their_file);

	std::string leaks = "leaks " + std::string(argv[0] + 2);
	std::cout << std::endl;
	PRINT("Press enter to run [" GREEN << leaks << RES "]")
	std::cin.ignore();
	system(leaks.c_str());
#endif
	(void)argc;
	(void)argv;
	return 0;
}
