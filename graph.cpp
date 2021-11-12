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

size_t Graph::get_ancestors(size_t p, bool** mas)
{
	size_t count = 0;
	*mas = new bool[size];
	for (size_t i = 0; i < size; ++i)
		{
			mas[0][i] = matrix[i][p-1];
			if (matrix[i][p-1])
				++count;
		}
				
	return count;
}

size_t Graph::get_descendants(size_t p, bool** mas)
{
	size_t count = 0;
	*mas = new bool[size];
	for (size_t i = 0; i < size; ++i)
		{
			mas[0][i] = matrix[p-1][i];
			if (matrix[p-1][i])
				++count;
		}
				
	return count;
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
	return points[p];
}

void Graph::visit(size_t p)
{
	visited++;
	points[p] = true;
}

void dfs(size_t s, Graph& graph, Ribs& ribs)
{
	std::cout << s << std::endl;
	graph.visit(s-1);
	std::cout << graph.is_visited(0)<< std::endl;
	/*
	bool* descendants;
	if (graph.get_descendants(s, &descendants))
	{
		for (size_t i = 0; i < graph.get_size(); ++i)
		{
			if (graph.is_visited(i) && descendants[i])
				ribs.back_r.push_back({i, s});
			if (!graph.is_visited(i) && descendants[i])
			{
				ribs.straight_r.push_back({s, i});
				dfs(i, graph, ribs);
			}
		}
		delete[] descendants;
	}
	*/
}	

void get_transverse(Graph& graph, Ribs& ribs)
{
	bool* descendants;
	bool* ancestors;
	size_t s = graph.get_size();;
	for (size_t i = 0; i < s; ++i)
	{
		if (!graph.get_descendants(i, &descendants))
		{
			graph.get_ancestors(i, &ancestors);
			for (size_t j = i+1; j < s; ++j)
			       if (!ancestors[j])
				       ribs.transverse_r.push_back({i, j});
			delete[] ancestors;
		}
			delete[] descendants;
	}
}


