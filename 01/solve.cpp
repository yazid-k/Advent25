#include <iostream>
#include <fstream>

int main() {
	std::ifstream file("input.txt");
	int dial = 50;
	int counter_p1 = 0;
	int counter_p2 = 0;
	std::string line;

	while (std::getline(file, line))
	{
		int dir = (line[0] == 'L') ? -1 : 1;
		int offset = dir * std::stoi(line.substr(1));

		counter_p2 += std::abs(offset) / 100;

		if (dial == 0 && offset < 0)
			counter_p2--;

		dial += offset % 100;

		if (dial == 0)
		{
			counter_p1++;
			counter_p2++;
		}
		else
		{
			if (dial > 99)
			{
				dial -= 100;
				counter_p2++;
			}
			else if (dial < 0)
			{
				dial += 100;
				counter_p2++;
			}
			if (dial == 0)
				counter_p1++;
		}
	}

	std::cout << "Part 1: " << counter_p1 << std::endl;
	std::cout << "Part 2: " << counter_p2 << std::endl;

	return 0;
}
