#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>

void std_iterators()
{
	std::vector<std::string> names{"john", "jane", "mads", "mike", "kevin", "chad"};
	decltype(names)::iterator it{names.begin()};
	std::cout << *it << std::endl;
	++it;
	std::cout << *it << std::endl;
	*it = "jill";
	std::cout << *it << std::endl;

	for(;it < names.end(); ++it)
	{
		std::cout << *it << std::endl;
	}

	std::copy(names.crbegin(), names.crend(), std::ostream_iterator<decltype(names)::value_type>(std::cout, " "));

	auto begin{std::begin(names)};
	std::cout << *begin << std::endl;
	auto rbegin{std::rbegin(names)};
	std::cout << *rbegin << std::endl;

	std::cout << std::distance(std::begin(names), std::end(names)) << std::endl;
}

int main()
{
	std_iterators();
	return 0;
}

