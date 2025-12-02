#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::vector<std::string> split(const std::string &s, char delim)
{
	std::vector<std::string> result;
	std::stringstream ss(s);
	std::string item;

	while (getline(ss, item, delim))
		result.push_back(item);
	return result;
}

int count_digits(unsigned long long n)
{
	if (n == 0) return 1;
	int count = 0;
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return count;
}

unsigned long long pow10(int exp)
{
	unsigned long long result = 1;
	for (int i = 0; i < exp; i++)
		result *= 10;
	return result;
}

bool is_duplicate(unsigned long long n)
{
	int digits = count_digits(n);
	if (digits % 2)
		return false;

	unsigned long long divisor = pow10(digits / 2);
	return n / divisor == n % divisor;
}

bool is_invalid(unsigned long long n)
{
	std::string s = std::to_string(n);
	int len = s.length();

	for (int pattern_len = 1; pattern_len <= len / 2; pattern_len++)
	{
		if (len % pattern_len != 0)
			continue;

		std::string pattern = s.substr(0, pattern_len);
		bool matches = true;

		for (size_t pos = pattern_len; pos < s.length(); pos++)
		{
			if (s[pos] != pattern[pos % pattern_len])
			{
				matches = false;
				break;
			}
		}
		if (matches)
			return true;
	}
	return false;
}

unsigned long long get_next_duplicate(unsigned long long n)
{
	int digits = count_digits(n);

	if (digits % 2)
		return pow10(digits);

	unsigned long long divisor = pow10(digits / 2);
	unsigned long long left = n / divisor;
	unsigned long long right = n % divisor;

	if (left < right)
		return (left + 1) * divisor + (left + 1);
	return left * divisor + left;
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	unsigned long long res1, res2 = 0;

	std::getline(file, line);
	std::vector<std::string> ranges = split(line, ',');

	for (const auto& s : ranges)
	{
		size_t dash_pos = s.find('-');
		unsigned long long a2 = std::stoull(s.substr(0, dash_pos));
		unsigned long long a = std::stoull(s.substr(0, dash_pos));
		unsigned long long b = std::stoull(s.substr(dash_pos + 1));

		while (a <= b)
		{
			if (is_duplicate(a))
			{
				res1 += a;
				a++;
			}
			else
				a = get_next_duplicate(a);
		}

		while (a2 <= b)
		{
			res2 += is_invalid(a2) * a2;
			a2++;
		}
	}

	std::cout << res1 << std::endl;
	std::cout << res2 << std::endl;
	return 0;
}
