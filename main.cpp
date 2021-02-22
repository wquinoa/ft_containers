//
// Created by Filipp Ewseew on 1/30/21.
//

#include "test-related/testheader.hpp"

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

//	if (fork() == 0)
//	{
//		PRINT("empty vector.front() " << tr.front())
//		PRINT("empty vector.back(): " << tr.back())
//		exit(1);
//	}
//	wait(0);

		/* Reserve basic */
	tr.reserve(0);
	PRINT("Capacity after reserve(0) is " << tr.capacity())

	tr.reserve(4);
	PRINT("Capacity after reserve(4) is " << tr.capacity())

		/* Insertion-removal-access basic */
	for  (int i = 0; i < 12; ++i)
		tr.push_back(i);

	printContainer(tr,  "several push_back()");

	tr.insert(tr.begin() + 5, 10, 8);
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
	tr.assign(10, 9);
	printContainer(tr, "assign(10, 10)");
	tr.erase(tr.begin(), tr.begin() + 10);
	PRINT("erase(begin(), begin() + 10), capacity: " << tr.capacity())
	printContainer(tr, "erase all");

	tr.assign(10, 5555);
	tr.clear();

	/* Undefined */
//	if (fork() == 0)
//	{
//		PRINT("vector[2021] is " << tr[2021])
//		std::cout << "erase 10 elements from size " << tr.size();
//		tr.erase(tr.begin() + 5, tr.begin() + 15);
//		exit(0);
//	}
//	wait(0);

	for (int i = 0; i < 200; ++i)
	    tr.push_back(i);
//
//	T v1(tr);
//	assert(tr == v1);
}

/// VISIBILITY todo vector speed

template <class T>
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

	for (int i = 0; i < 10; ++i)
	{
		l.push_back(++i);
	}
	printContainer(l, "pushing 13 random elements");
	l.sort();
	printInReverse(l, "sorting 13 random elements");
	l.reverse();
	printContainer(l, "list.reverse()");

	while (l.size())
		l.pop_back();
	PRINT("current size is: " << l.size());
	printContainer(l, "list.pop_back() all");
}

/// VISIBILITY todo lists speed

template <class T>
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
	v.reverse();

	/* Deletion */
	v.clear();
	while (v.size() > 222)
		v.erase(v.begin());
	v.erase(v.begin(), v.end());

}

///   VISIBILITY todo map test

template <class T>
void 	btreeTest(std::string const & filename)
{
#if (C_LOG == 1)
	Logger log(filename, "base test");
#endif
	T btree;

    int i;
	for ( i = 0; i < 100000; ++i )
		btree.insert( std::make_pair(i, i) );
	printContainer(btree, "inserting 100000 consecutive elements");
	for ( i = 0; i < 50000; ++i )
		btree.erase(i);
	printInReverse(btree, "erasing 50000 consecutive elements");

	PRINT("find(21): " << ((btree.find(21) != btree.end()) ? "found" : "not found"))
    PRINT("find(50021): " << ((btree.find(50021) != btree.end()) ? "found" : "not found"))
    PRINT("btree[21]: " << btree[21])
    PRINT("btree[50021]: " << btree[50021])
    btree.clear();
	assert(btree.empty());

	for (i = 0; i < 10; ++i)
        btree[-1];
    printContainer(btree, "btree.clear(); cycled btree[-1]");
    assert(btree.size() == 1);

    for (i = 0; i < 10; ++i)
        btree.insert(std::make_pair(1, 1));
    printContainer(btree, "cycled btree.insert(1, 1)");
    assert(btree.size() == 2);

    for (i = 0; i < 10; ++i)
        btree.erase(1);
    printContainer(btree, "cycled btree.erase(1)");

    for (i = 0; i < 50000; ++i)
        btree.insert(std::make_pair(i, i));
    assert(btree.lower_bound(50001) == btree.end());
    assert(btree.lower_bound(21000) != btree.end());
    assert(btree.upper_bound(50001) == btree.end());
    assert(btree.upper_bound(21000) != btree.end());
    PRINT("btree.max_size() " << btree.max_size());
    T tree2;

    btree.swap(tree2);
    printContainer(tree2, "btree.swap(tree2)");
    printContainer(btree, "btree.swap(tree2)");
    btree.clear();
    btree.clear();
    btree.clear();
    printContainer(btree, "btree.clear() (empty tree)");
    tree2.clear();
    tree2.clear();
    tree2.clear();
    printContainer(tree2, "tree2.clear() (full tree)");

    for ( i = 0; i < 299999; ++i )
        btree.insert(std::make_pair(i, i));
    assert(btree.size() == 299999);

    tree2 = btree;

    assert(tree2 == btree);
    assert(tree2 >= btree);
    assert(tree2 <= btree);
    tree2.erase(1);
    btree[55555555] = 420;
    assert(btree != tree2);
    assert(btree < tree2);
    assert(tree2 > btree);

    T tree3(tree2);
    assert(tree2 == tree3);
    assert(tree3.equal_range(5).first->first <= 5);
    assert(tree3.equal_range(5).second->first > 5);
    assert(tree3.equal_range(42).first->first <= 42);
    assert(tree3.equal_range(42).second->first > 42);
    assert(tree3.equal_range(9999999).first == tree3.end());

    (void)filename;
}

void sigsegvHandler(int sig)
{
	if (sig == SIGSEGV) PRINT(RED << "sigsegv caught" << RES);
	exit(1);
}

int main(int argc, char **argv)
{
	signal(SIGSEGV, sigsegvHandler);

    btreeTest<typeof(std_mp)>(their_file + "map");
	btreeTest<typeof(my_mp)>(my_file + "map");
	doDiff("map");

	std::string leaks = "leaks " + std::string(argv[0] + 2);
	std::cout << std::endl;

#if (TEST_THEIRS == 0)
	vector_test<typeof(std_v)>(their_file + "vector");
	vector_test<typeof(ft_v)>(my_file + "vector");
	doDiff("vector");

	listTest<typeof(std_l)>(their_file + "list");
	listTest<typeof(ft_l)>(my_file + "list");
	doDiff("list");

#else

	PRINT("           benchmark          ")
	vectorBenchmark<typeof(std_v)>(their_file + "vector");
	vectorBenchmark<typeof(ft_v)>(my_file + "vector");
	doDiff("vector");

	listBenchmark<typeof(std_l)>(their_file + "list");
	listBenchmark<typeof(ft_l)>(my_file + "list");
	doDiff("list");

#endif
//	PRINT("Press enter to run [" << "\033[0;33m" << leaks << "\033[0m" << "]")
//	system(leaks.c_str());
	(void)argc;
	(void)argv;

	return 0;
}
