/*
 * Single Responsibility Principle
 */

#include <fstream>
#include <vector>
#include <string>


struct Journal
{
	std::string title;
	std::vector<std::string> entries;

	explicit Journal(std::string title)
		:	title{std::move(title)}
	{}

	void add(std::string entry)
	{
		entries.emplace_back(std::move(entry));
	}
};

struct PersistenceManager
{
	static void save(const Journal& j, const std::string& filename)
	{
		std::ofstream out(filename);
		out << j.title;
		for(const auto& e : j.entries)
		{
			out << e << std::endl;
		}
	}
};

