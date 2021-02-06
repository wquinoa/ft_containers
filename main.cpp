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

template <typename T, class U>
void vector_test(T &tr, std::string const &filename)
{
#ifdef TEST_THEIRS
	Logger log(filename);
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
	for (int i = 0; i < 10; ++i)
		tr.push_back(U(i + 1, i));
	printContainer(tr, "10 * push_back()");

	tr.insert(tr.begin() + 5, 10, U(21, '*'));
	printContainer(tr, "insert(begin + 5, 10, 21)");
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
	tr.assign(10, U(10, '*'));
	printContainer(tr, "assign(10, 10)");
	tr.erase(tr.begin(), tr.begin() + 10);
	PRINT("erase(begin(), begin() + 10), capacity: " << tr.capacity() << ", size() == " << tr.size())
	printContainer(tr, "erase all");

	tr.assign(10, U(10, '*'));
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
	Logger log(filename);
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
	Logger log(filename);
#endif
	(void) filename;
	T l;
	typename T::iterator it;

	PRINT("Empty list front: " << l.front());
	PRINT("empty list back: " << l.back());


	for (int i = 0; i < 10; ++i)
		l.push_back(i);
	l.assign(5, 5);
	//printContainer(l, "list.push_back()");
	PRINT("current size is: " << l.size());
	PRINT( "list Max size is " << l.max_size());
	l.clear();
	PRINT("Size after list.clear():" << l.size());


	if (fork() == 0)
	{
		PRINT("Erasing from an empty list:");
		l.erase(l.begin());
		exit(1);
	}
	wait(0);
	PRINT("New elem: " << *l.insert(l.begin(), 21))

	while (l.size() < 13)
		l.push_front(rand() % 22);
	printContainer(l, "pushing 12 random elements");
	l.sort();
	printInReverse(l, "sorting 12 random elements");


	//while (l.size())
	//	l.pop_back();
	//PRINT("current size is: " << l.size());
	//printContainer(l, "list.pop_back() all");
}

void sigsegvHandler(int sig)
{
	if (sig == SIGSEGV) {
		PRINT(RED << "sigsegv caught" << RES);
	}
	exit(1);
}

int main(int argc, char **argv)
{
	signal(SIGSEGV, sigsegvHandler);
	std::string my_file("my_test_1.txt");
	std::string their_file("std_test_2.txt");
	std::string diff("diff " + my_file + ' ' + their_file);
	std::string leaks = "leaks " + std::string(argv[0] + 2);

	(void)argc;

	srand(time(0));
	unlink(my_file.c_str());
	unlink(their_file.c_str());

	/*
	shitty::Vector<TesterClass> mine;
	std::vector< TesterClass > theirs;

	g_perfdiff = 0;
	vector_test<typeof(mine), TesterClass>(mine, my_file);
	vector_test<typeof(theirs), TesterClass>(theirs, their_file);


	g_perfdiff = 0;
	vectorBenchmark<typeof(mine)>(my_file);
	vectorBenchmark<typeof(theirs)>(their_file);
	 */
	shitty::List<int>	my_l;
	std::list<int>		std_l;

	g_perfdiff = 0;
	listTest<typeof(my_l)>(my_file);
	listTest<typeof(std_l)>(their_file);

#ifdef TEST_THEIRS
	PRINT(RED "diff: " RES)
	system(diff.c_str());
#endif
	std::cout << std::endl;
	PRINT("Press enter to run [" GREEN << leaks << RES "]")
	std::cin.ignore();
	system(leaks.c_str());

	return 0;
}
