#include "graph.hpp"

int main()
{
	std::string f;
//	std::cin >> f;
	f = "input.txt";
	Graph m(f);
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

	Ribs r;
	dfs(m.get_start_pos(), m, r);
	get_transverse(m, r);

	std::cout << r << std::endl;
	return 0;
}

