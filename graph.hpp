#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Graph
{
	private:
		size_t size;
		size_t visited;
		size_t start_pos;
		bool** matrix;
		bool* points;
	public:
		Graph(const std::string file_name);
		Graph(const Graph& a);
		Graph& operator=(const Graph& a);
		~Graph();
		size_t get_ancestors(size_t p, bool** mas);	
		size_t get_descendants(size_t p, bool** mas);
		size_t get_size();
		size_t get_start_pos();
		bool is_visited(size_t p);
		void visit(size_t p);
	friend std::ostream& operator<<(std::ostream& os, const Graph& value)
	{
		os << "start - " << value.start_pos << std::endl;
		os << "size - " << value.size << std::endl;
		os << "  ";
		for (size_t i = 1; i <= value.size; ++i)
			os << i << " ";
		for (size_t i = 1; i <= value.size; ++i)
		{
			os << std::endl;
			os << i << " ";
			for (size_t j = 0; j < value.size; ++j)
				os << value.matrix[i-1][j] << " ";
		}
		return os;
	}
};

struct Pair
{
	size_t first;
	size_t second;

	friend std::ostream& operator<<(std::ostream& os, const Pair& value)
	{
		os << value.first << " -> " << value.second;
		return os;
	}

};

struct Ribs
{
	std::vector<Pair> straight_r;
	std::vector<Pair> back_r;
	std::vector<Pair> transverse_r;

	friend std::ostream& operator<<(std::ostream& os, const Ribs& value)
	{
		os << "straight ribs:" << std::endl;
		for (Pair e : value.straight_r)
			os << e << std::endl;
		os << "back ribs:" << std::endl;
		for (Pair e : value.back_r)
			os << e << std::endl;
		os << "transverse ribs:" << std::endl;
		for (Pair e : value.transverse_r)
			os << e << std::endl;
		return os;
	}

};

void dfs(size_t s, Graph& graph, Ribs& ribs);

void get_transverse(Graph& graph, Ribs& ribs);

