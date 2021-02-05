//
// Created by Filipp Ewseew on 1/30/21.
//

#include "Vector.hpp"
#include <vector>
#include <list>
//#include "BTree.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <ostream>
#include <iomanip>
#include "Colors.h"

class TesterClass
{
 public:
	int i;
	char j;

 public:
	TesterClass() : i(), j()
	{
	}

	TesterClass(const int &i, const char &j)
	: i(i), j(j)
	{
	}

	friend std::ostream &operator<<(std::ostream &os, const TesterClass &c)
	{
		os << c.i;
		return (os);
	}
};

static float g_perfdiff;

class Logger
{
	int fd, save_fd;
	timeval start, end;
	std::string filename;

	Logger() {};
	Logger(const Logger &copy) { (void)copy; };
	Logger &operator =(const Logger &copy) { (void)copy; return *this; };

	float getMsDiff()
	{
		float ms = (end.tv_sec * 1000000 + end.tv_usec) / 1000.0 - \
		(start.tv_sec * 1000000 + start.tv_usec) / 1000.0;

		return ms / 1000;
	}

 public:

	Logger(std::string const & filename) : filename(filename)
	{
		save_fd = dup(STDOUT_FILENO);
		fd = open(filename.c_str(), O_CREAT | O_WRONLY | O_APPEND, 0666);

		close(1);
		dup2(fd, STDOUT_FILENO);
		gettimeofday(&start, NULL);
	}

	~Logger()
	{
		gettimeofday(&end, NULL);
		close(fd);
		dup2(save_fd, STDOUT_FILENO);

		PRINT(filename << ": test finished in " << std::fixed << \
		std::setprecision(2) << getMsDiff() << "s");

		ssize_t performance = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
		if (g_perfdiff == 0)
			g_perfdiff = performance;
		else {
			int diff = (g_perfdiff - performance) / performance * 100;
			PRINT("original is " << diff << "% faster");
		}
	}
};

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
void	vector_bechmark(std::string const &filename)
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

void segvHandler(int sig)
{
	if (sig == SIGSEGV) {
		PRINT("\033[31msigsegv caught\033[0m");
	}
	exit(1);
}

int main(int argc, char **argv)
{
	signal(SIGSEGV, segvHandler);
	std::string my_file("my_vector_1.txt");
	std::string their_file("their_vector_2.txt");
	std::string diff("diff " + my_file + ' ' + their_file);
	std::string leaks = "leaks " + std::string(argv[0] + 2);

	(void)argc;

	unlink(my_file.c_str());
	unlink(their_file.c_str());

	shitty::Vector<TesterClass> mine;
	std::vector< TesterClass > theirs;

	g_perfdiff = 0;
	vector_test<typeof(mine), TesterClass>(mine, my_file);
	vector_test<typeof(theirs), TesterClass>(theirs, their_file);


	g_perfdiff = 0;
	vector_bechmark<typeof(mine)>(my_file);
	vector_bechmark<typeof(theirs)>(their_file);

	system(diff.c_str());
	std::cout << std::endl;
	PRINT("Press enter for leak test...")
	std::cin.ignore();
	system(leaks.c_str());

	return 0;
}
