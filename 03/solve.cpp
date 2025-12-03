#include <iostream>
#include <fstream>
#include <string>

int get_max(const std::string& line)
{
	int max1 = 0, max2 = 0;
	int idx1 = -1;

	for (int i = 0; i < line.length() - 1; i++)
	{
		if (line[i] - '0' > max1)
		{
			max1 = line[i] - '0';
			idx1 = i;
		}
	}

	for (int i = idx1 + 1; i < line.length(); i++) {
		if (line[i] - '0' > max2)
			max2 = line[i] - '0';
	}
	return max1 * 10 + max2;
}

unsigned long long get_max_p2(const std::string& line)
{
	std::string remaining = line;
	unsigned long long result = 0;
	unsigned long long multiplier = 100000000000ULL;

	for (int digits_left = 12; digits_left > 0; digits_left--)
	{
		int max_idx = 0;
		char max_digit = remaining[0];
		int search_limit = remaining.length() - digits_left + 1;

		for (int i = 1; i < search_limit; i++)
		{
			if (remaining[i] > max_digit)
			{
				max_digit = remaining[i];
				max_idx = i;
			}
		}

		result += (max_digit - '0') * multiplier;
		multiplier /= 10;
		remaining = remaining.substr(max_idx + 1);
	}
	return result;
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	long long sum_p1 = 0;
	unsigned long long sum_p2 = 0;

	while (std::getline(file, line))
	{
		sum_p1 += get_max(line);
		sum_p2 += get_max_p2(line);
	}

	std::cout << sum_p1 << std::endl;
	std::cout << sum_p2 << std::endl;
	return 0;
}
