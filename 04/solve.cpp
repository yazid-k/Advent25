#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int count_neighbors(const std::vector<std::string>& grid, int i, int j)
{
	int count = 0;
	for(int k = 0; k < 8; k++)
	{
		int ni = i + dx[k];
		int nj = j + dy[k];
		if (ni >= 0 && ni < grid.size() && nj >= 0 && nj < grid[ni].length() && grid[ni][nj] == '@')
			count++;
	}
	return count;
}

int remove_p2(std::vector<std::string> grid, int removed = 0)
{
	std::vector<std::pair<int, int>> coords;

	for(int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].length(); j++)
		{
			if (grid[i][j] == '@' && count_neighbors(grid, i, j) < 4)
				coords.push_back({i, j});
		}
	}

	if (coords.empty())
	{
		for(const auto& row : grid)
			std::cout << row << std::endl;
		return removed;
	}

	for (const auto& coord : coords)
		grid[coord.first][coord.second] = '.';

	return remove_p2(grid, removed + coords.size());
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	std::vector<std::string> grid;

	while (std::getline(file, line))
		grid.push_back(line);

	int res = 0;
	for(int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].length(); j++)
		{
			if (grid[i][j] == '@' && count_neighbors(grid, i, j) < 4)
				res++;
		}
	}

	std::cout << res << std::endl;
	std::cout << remove_p2(grid) << std::endl;
}
