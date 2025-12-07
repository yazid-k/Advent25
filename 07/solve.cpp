#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <map>

int get_splits(const std::vector<std::string>& grid, int row, int col, std::set<std::pair<int,int>>& visited)
{
	if (row >= grid.size() || col < 0 || col >= grid[0].size())
		return 0;
	if (grid[row][col] != '^')
		return get_splits(grid, row + 1, col, visited);
	if (visited.count({row, col}))
		return 0;
	visited.insert({row, col});
	int left = get_splits(grid, row + 1, col - 1, visited);
	int right = get_splits(grid, row + 1, col + 1, visited);
	return 1 + left + right;
}

long long get_splits_p2(const std::vector<std::string>& grid, int start_col)
{
	int rows = grid.size();
	int cols = grid[0].size();
	std::map<int, long long> current_row;
	std::map<int, long long> next_row;
	current_row[start_col] = 1;

	for (int row = 1; row < rows; row++)
	{
		next_row.clear();
		for (std::map<int, long long>::iterator it = current_row.begin(); it != current_row.end(); ++it)
		{
			int col = it->first;
			long long paths = it->second;

			if (col < 0 || col >= cols)
				continue;
			if (grid[row][col] != '^')
				next_row[col] += paths;
			else
			{
				if (col - 1 >= 0)
					next_row[col - 1] += paths;
				if (col + 1 < cols)
					next_row[col + 1] += paths;
			}
		}
		current_row = next_row;
	}
	long long total = 0;
	for (std::map<int, long long>::iterator it = current_row.begin(); it != current_row.end(); ++it)
		total += it->second;
	return total;
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	std::vector<std::string> grid;

	while(std::getline(file, line))
		grid.push_back(line);
	size_t pos = grid[0].find('S');
	std::set<std::pair<int,int>> visited;
	std::map<std::pair<int, int>, int> memo;
	std::cout << get_splits(grid, 1, pos, visited) << std::endl;
	std::cout << get_splits_p2(grid, pos) << std::endl;
}
