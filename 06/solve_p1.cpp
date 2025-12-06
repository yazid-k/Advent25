#include <iostream>
#include <sstream>
#include <fstream>

std::vector<std::string> split(const std::string& str)
{
	std::vector<std::string> tokens;
	std::istringstream iss(str);
	std::string token;

	while (iss >> token)
		tokens.push_back(token);
	return tokens;
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	std::vector<std::vector<std::string>> grid;
	unsigned long long res = 0;

	while(std::getline(file, line))
		grid.push_back(split(line));
	for (int j = 0; j < grid[0].size(); j++)
	{
		unsigned long long tmp = std::stoull(grid.front()[j]);
		bool is_product = grid.back()[j] == "*";
		for (int i = 1; i < grid.size() - 1; i++)
		{
			unsigned long long num = std::stoull(grid[i][j]);
			if (is_product)
				tmp *= num;
			else
				tmp += num;
		}
		res += tmp;
	}
	std::cout << res << std::endl;
}
