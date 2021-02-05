//
// Created by Filipp Ewseew on 1/30/21.
//

#include "Vector.hpp"
#include <vector>
#include <list>
//#include "BTree.hpp"
#include <setjmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

jmp_buf buffer_a;

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

int g_perfdiff;

class Logger
{
	int fd, save_fd;
	timeval start, end;
	std::string filename;

	Logger() {};
	Logger(const Logger &copy) { (void)copy; };
	Logger &operator =(const Logger &copy) { (void)copy; return *this; };
 public:
	Logger(std::string const & filename) : filename(filename)
	{
		save_fd = dup(STDOUT_FILENO);
		fd = open(filename.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0666);

		close(1);
		dup2(fd, STDOUT_FILENO);
		gettimeofday(&start, NULL);
	}

	~Logger()
	{
		gettimeofday(&end, NULL);

		close(fd);
		dup2(save_fd, STDOUT_FILENO);
		PRINT(filename << ": test finished in " << end.tv_sec - start.tv_sec
								  << "." << end.tv_usec - start.tv_usec);

		ssize_t performance = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
		if (g_perfdiff == 0)
			g_perfdiff = performance;
		else
			PRINT("difference in performance is " << performance * 100 / g_perfdiff << "%");
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
#else
	(void)filename;
#endif
	PRINT("Current capacity is: " << tr.capacity())
	int r;
	if (!(r =setjmp(buffer_a))) {
		PRINT("vector.front(): " << tr.front())
		PRINT("vector.back(): " << tr.back())
	}


	for (int i = 0; i < 10; ++i)
		tr.push_back(U(i + 1, i));
	printContainer(tr, "10 * push_back()");

	tr.insert(tr.begin() + 5, 10, U(21, '*'));
	printContainer(tr, "insert(begin + 5, 10, 21)");
	tr.erase(tr.begin() + 5, tr.begin() + 14);
	printContainer(tr, "erase(begin + 5, begin + 14)");

	// causes SIGSEGV on original

//	T backup = tr;
//	if (!(r =setjmp(buffer_a))) {
//		tr.erase(tr.begin() + 5, tr.begin() + 15);
//		printContainer(tr, "erase(begin() + 5, begin + 14)");
//	}
//	tr = backup;

	tr.pop_back();
	printContainer(tr, "pop_back");
	PRINT("current size is: " << tr.size())
	PRINT("vector.at(5) is " << tr.at(5))
	PRINT("vector[2] is " << tr[2])
	try { tr.at(124); }
	catch (std::exception &e) { PRINT("vector.at(124): " << e.what()) };
	try { tr[124]; }
	catch (std::exception &e) { PRINT("vector[124]: " << e.what()) };
	PRINT("vector.front() is " << tr.front())
	PRINT("vector.back() is " << tr.back())

	PRINT("Current capacity is: " << tr.capacity())
}

void segvHandler(int sig)
{
	if (sig == SIGSEGV)
		PRINT("\033[31msigsegv caught\033[0m")
	longjmp(buffer_a, 1);
}

int main()
{
	signal(SIGSEGV, segvHandler);

	unlink("my_vector_1");
	unlink("their_vector_2");


	shitty::Vector<TesterClass> mine;
	vector_test<typeof(mine), TesterClass>(mine, "my_vector_1");
	std::vector< TesterClass > theirs;
	vector_test<typeof(theirs), TesterClass>(theirs, "their_vector_2");

	return 0;
}
