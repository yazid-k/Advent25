#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using Range = std::pair<unsigned long long, unsigned long long>;

bool in_range(unsigned long long num, const Range& range)
{
	return num >= range.first && num <= range.second;
}

std::vector<Range> merge_ranges(std::vector<Range> ranges)
{
	if (ranges.empty())
		return {};

	std::sort(ranges.begin(), ranges.end());

	std::vector<Range> merged;
	merged.push_back(ranges[0]);

	for (size_t i = 1; i < ranges.size(); i++)
	{
		Range& last = merged.back();
		const Range& current = ranges[i];

		if (current.first <= last.second)
			last.second = std::max(last.second, current.second);
		else
			merged.push_back(current);
	}
	return merged;
}

unsigned long long count_total(const std::vector<Range>& ranges)
{
	unsigned long long total = 0;
	for (const auto& range : ranges)
		total += range.second - range.first + 1;
	return total;
}

int main()
{
	std::ifstream file("input.txt");
	std::string line;
	std::vector<Range> ranges;
	int res = 0;

	while (std::getline(file, line))
	{
		size_t dash = line.find('-');

		if (dash != std::string::npos)
		{
			unsigned long long left = std::stoull(line.substr(0, dash));
			unsigned long long right = std::stoull(line.substr(dash + 1));
			ranges.push_back({left, right});
		}
		else if (!line.empty())
		{
			unsigned long long num = std::stoull(line);
			for (const auto& range : ranges)
			{
				if (in_range(num, range))
				{
					res++;
					break;
				}
			}
		}
	}

	std::vector<Range> merged = merge_ranges(ranges);

	std::cout << res << std::endl;
	std::cout << count_total(merged) << std::endl;
}
