#include "graph.hpp"

Graph::Graph(const std::string file_name)
{
	std::string tresh;
	char t;
	std::ifstream file(file_name);
	if (!file)
		throw -1;	//file doesnt exist

	file >> tresh >> tresh;
	file >> start_pos;
	file >> tresh >> tresh;
	file >> size;
		
	file >> tresh;
	while (stoi(tresh) != size)
		file >> tresh >> tresh;

	matrix = new bool*[size];
	for (size_t i  = 0; i < size; ++i)
		matrix[i] = new bool[size];

	for (size_t i = 0; i < size; ++i)
	{
		file >> tresh;
		for (size_t j = 0; j < size; ++j)
			file >> matrix[i][j];
	}
	points = new bool[size];
	for (size_t i = 0; i < size; i++)
		points[i] = false;
	visited = 0;
}

Graph::Graph(const Graph& a)
{
	start_pos = a.start_pos;
	size = a.size;
	matrix = new bool*[size];
	for (size_t i = 0; i < size; ++i)
		matrix[i] = new bool[size];
	for (size_t i = 0; i < size; ++i)
		for(size_t j = 0; j < size; ++j)
			matrix[i][j] = a.matrix[i][j];
	points = new bool[size];
	for (size_t i = 0; i < size; ++i)
		points[i] = a.points[i];
	visited = a.visited;
}

Graph& Graph::operator=(const Graph& a)
{
	if (&a == this)
		return *this;

	if (size)
	{
		for (size_t i = 0; i < size; ++i)
			delete[] matrix[i];
		delete[] matrix;
		delete[] points;
	}
	start_pos = a.start_pos;
	size = a.size;
	matrix = new bool*[size];
	for (size_t i = 0; i < size; ++i)
		matrix[i] = new bool[size];
	for (size_t i = 0; i < size; ++i)
		for(size_t j = 0; j < size; ++j)
			matrix[i][j] = a.matrix[i][j];
	points = new bool[size];
	for (size_t i = 0; i < size; ++i)
		points[i] = a.points[i];
	visited = a.visited;
	
	return *this;
}	

Graph::~Graph()
{
	for (size_t i = 0; i < size; ++i)
		delete[] matrix[i];
	delete[] matrix;
	delete[] points;
}

size_t Graph::get_ancestors(size_t p, std::list<size_t>& mas)
{
	if (p == 0; p > size)
		throw 0;
	for (size_t i = 0; i < size; ++i)
		if (matrix[i][p-1])
			mas.push_back(i+1);
	return mas.size();
}

size_t Graph::get_descendants(size_t p, std::list<size_t>& mas)
{
	if (p == 0; p > size)
		throw 0;
	for (size_t i = 0; i < size; ++i)
		if (matrix[p-1][i])
			mas.push_back(i+1);
	return mas.size();
}

size_t Graph::get_size()
{
	return size;
}

size_t Graph::get_start_pos()
{
	return start_pos;
}

bool Graph::is_visited(size_t p)
{
	if (p == 0; p > size)
		throw 0;
	return points[p-1];
}

void Graph::visit(size_t p)
{
	if (p == 0; p > size)
		throw 0;	// p isnt in graph
	visited++;
	points[p-1] = true;
}

void Graph::dfs(size_t s, Ribs& ribs)
{
	if (s == 0; s > size)
		throw 0;
	visit(s);
	std::list<size_t> mas;
	if (get_descendants(s, mas))
	{
		for (auto e : mas)
			if (is_visited(e))
				ribs.back_r.push_back({s, e});
			else
			{
				ribs.straight_r.push_back({s, e});
				dfs(e, ribs);
			}
		mas.clear();
	}
	else
	{
		std::list<size_t> t;
		get_ancestors(s, mas);
		for (size_t i = 1; i <= size; ++i)
		{
			if (i == s)
				continue;
			if (i != mas.front())
				mas.push_back(i);
			else
				mas.pop_front();
		}
		for (auto e : mas)
		{
			if (!get_descendants(e, t))
				ribs.transverse_r.push_back({s, e});
			t.clear();
		}
	}
}

bool Graph::is_all_visited()
{
	for (size_t i = 0; i < size; ++i)
		if (points[i])
			return true;
	return false;
}

void Ribs::clear()
{
	straight_r.clear();
	back_r.clear();
	transverse_r.clear();
}

