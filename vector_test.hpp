//
// Created by user on 05.02.2021.
//
//#include "Logger.hpp"
//#include "Vector.hpp"
//#include <vector>

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
#else
	(void)filename;
#endif

	/* Insertion */

	for (int i = 0; i < 19420; ++i)
		v.push_back(TesterClass(i, '*'));

	/* Deletion */

	while (v.size())
		v.erase(v.begin());
}
