#include "graph.hpp"

int main()
{
	std::string f;
	f = "input.txt";
	Graph m(f);
	std::cout << m << std::endl;

	Ribs r;
	try
	{
		m.dfs(m.get_start_pos(), r);
	}
	catch (int er)
	{
		if (!er)
			std::cout << "elements doesnt exist" << std::endl;
	}

	std::cout << r;
	return 0;
}

