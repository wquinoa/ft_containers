//
// Created by user on 05.02.2021.
//

#ifndef FT_CONTAINERS_LOGGER_HPP
# define FT_CONTAINERS_LOGGER_HPP
# ifndef C_LOG
#  define C_LOG 0
# endif
# include <fcntl.h>
# include <unistd.h>
# include <sys/time.h>
# include <iostream>
# include <ostream>
# include <iomanip>
# include "Misc/Debug.h"
# include <vector>

static float g_perfdiff;

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

class Logger
{
	int fd, save_fd;
	timeval start, end;
	std::string filename, testname;

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

	Logger(std::string const & filename, const std::string &testname)
	: filename(filename), testname(testname)
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

		PRINT("\033[34m" << filename << ", " << testname << "\033[0m" << " finished in "
		<< std::fixed << std::setprecision(2) << BOLD << getMsDiff() << "s" << RES);

		ssize_t performance = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
		if (g_perfdiff == 0) {
			g_perfdiff = performance;
		}
		else
		{
			int diff = (performance - g_perfdiff) / g_perfdiff * 100;
			PRINT("STD is " << BOLD << std::abs(diff) << RES << "% "
			<< (diff > 0 ? "\033[32mfaster" : "\033[31mslower" ) << "\033[0m"" than FT!");
		}
	}
};

#endif //FT_CONTAINERS_LOGGER_HPP
