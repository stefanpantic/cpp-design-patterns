#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/exception/exception.hpp>
#include <iostream>
#include <vector>
#include <stack>


class StringAdapter
{
	std::string s;

public:
	StringAdapter(std::string str)
		:	s{std::move(str)}
	{}

	StringAdapter to_lower() const
	{
		auto ret{s};
		boost::to_lower(ret);
		return ret;
	}

	std::vector<std::string> split(const std::string& delimiter = " ", bool trim = true)
	{
		std::vector<std::string> res;
		boost::split(res, s, boost::is_any_of(delimiter), trim ? boost::token_compress_on : boost::token_compress_off);
		return res;
	}

	std::string& str()
	{
		return s;
	}

	const std::string& str() const
	{
		return s;
	}
};

int main()
{
	StringAdapter str("Hello World");
	auto splt{str.to_lower().split(" ")};
	for(const auto& s : splt)
	{
		std::cout << s << std::endl;
	}

	return 0;
}

