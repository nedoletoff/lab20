#include "dfs.hpp"

int main()
{
	std::string f;
//	std::cin >> f;
	f = "input.txt";
	Dfs m(f);
	bool* e;
	std::cout << m.get_descendants(1, &e) << std::endl;
	for (size_t i = 0; i < m.get_size(); ++i)
		std::cout << " i - " << e[i];
	std::cout << std::endl;
	std::cout << m.get_ancestors(2, &e) << std::endl;
	for (size_t i = 0; i < m.get_size(); ++i)
		std::cout << " i - " << e[i];
	std::cout << std::endl;
	std::cout << m << std::endl;
	return 0;
}

