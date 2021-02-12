//
// Created by user on 07.02.2021.
//

#ifndef FT_CONTAINERS_TESTS_HPP
# define FT_CONTAINERS_TESTS_HPP

typedef std::vector<TEST_TYPE> std_v;
typedef ft::Vector<TEST_TYPE> ft_v;
typedef std::list<TEST_TYPE> std_l;
typedef ft::List<TEST_TYPE> ft_l;
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
	PRINT("\033[0;37m" << " ------- diff ------- \n")
	system(diff.c_str());
	PRINT(" ------- end  ------- " << "\033[0m")
	usleep(1000);
	unlink((my_file + type).c_str());
	unlink((their_file + type).c_str());
	g_perfdiff = 0;
	(void)type;
}

#endif //FT_CONTAINERS_TESTS_HPP
