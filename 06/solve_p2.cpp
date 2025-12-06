#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	std::vector<std::string> grid;
	char operation = '+';
	unsigned long long res = 0;
	unsigned long long tmp = 0;

	while(std::getline(file, line))
		grid.push_back(line);

	for (int j = 0; j < grid.front().size(); j++)
	{
		char last_char = grid.back()[j];
		if (last_char == '*' || last_char == '+')
		{
			operation = last_char;
			res += tmp;
			tmp = operation == '*' ? 1 : 0;
		}

		std::string col = "";
		for (int i = 0; i < grid.size() - 1; i++)
			col.push_back(grid[i][j]);

		col.erase(std::remove(col.begin(), col.end(), ' '), col.end());

		if (!col.empty() && std::isdigit(col.front()))
		{
			unsigned long long number = std::stoull(col);
			if (operation == '*')
				tmp *= number;
			else
				tmp += number;
		}
	}
	res += tmp;
	std::cout << res << std::endl;
}
