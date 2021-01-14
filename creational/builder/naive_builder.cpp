#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <memory>


int main()
{
	// <p>Hello</p>

	// Naive
	auto text{"Hello"};
	std::string output;
	output += "<p>";
	output += text;
	output += "</p>";
	std::cout << output << std::endl;

	// printf
	std::printf("<p>%s</p>\n", text);

	// <ul><li>hello</li><li>world</li></ul>
	std::vector<std::string> words{"hello", "world"};
	std::ostringstream oss;
	oss << "<ul>";
	for(const auto& e : words)
	{
		oss << "<li>" << e << "</li>";
	}
	oss << "</ul>";
	std::cout << oss.str() << std::endl;


	return 0;
}
