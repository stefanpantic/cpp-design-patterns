#pragma once

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>
#include <unordered_map>

class IDatabase
{
public:
	virtual int get_population(const std::string& name) = 0;
};

class SingletonDatabase : public IDatabase
{
	std::unordered_map<std::string, size_t> data;

	SingletonDatabase()
	{
		std::clog << "SingletonDatabase::SingletonDatabase()" << std::endl;

		std::ifstream in("resource.txt");
		std::string name, num;
		while(std::getline(in, name))
		{
			if(std::getline(in, num))
			{
				data[name] = std::stoull(num);
			}
		}
	}

public:

	SingletonDatabase(const SingletonDatabase&) = delete;
	SingletonDatabase(SingletonDatabase&&) = delete;

	SingletonDatabase& operator=(const SingletonDatabase&) = delete;
	SingletonDatabase& operator=(SingletonDatabase&&) = delete;

	static SingletonDatabase& get()
	{
		static SingletonDatabase instance;
		return instance;
	}

	int get_population(const std::string& name) override
	{
		auto elem{data.find(name)};
		if(elem == data.end())
		{
			throw std::runtime_error(name + " not present in database.");
		}

		return elem->second;
	}
};

class DummyDatabase : public IDatabase
{
	std::unordered_map<std::string, int> data;
public:
	DummyDatabase()
	{
		data["alpha"] = 1;
		data["beta"] = 2;
		data["gamma"] = 3;
	}

	int get_population(const std::string& name) override
	{
		return data[name];
	}
};

struct SingletonRecordFinder
{
	int total_population(const std::vector<std::string>& names)
	{
		return std::accumulate(	names.cbegin(), names.cend(), 0,
								[] (const auto& acc, const auto& val)
								{
									return acc + SingletonDatabase::get().get_population(val);
								});
	}
};

struct ConfigurableRecordFinder
{
	IDatabase& db;

	explicit ConfigurableRecordFinder(IDatabase& idb)
		:	db{idb}
	{}

	int total_population(const std::vector<std::string>& names)
	{
		return std::accumulate(	names.cbegin(), names.cend(), 0,
								[this] (const auto& acc, const auto& val)
								{
									return acc + db.get_population(val);
								});
	}
};

