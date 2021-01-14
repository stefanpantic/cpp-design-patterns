#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>


class NaiveSingletonDatabase
{
	NaiveSingletonDatabase()
	{
		std::clog << "NaiveSingletonDatabase::NaiveSingletonDatabase()" << std::endl;

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

	static NaiveSingletonDatabase* instance;
public:
	std::unordered_map<std::string, size_t> data;

	NaiveSingletonDatabase(const NaiveSingletonDatabase&) = delete;
	NaiveSingletonDatabase(NaiveSingletonDatabase&&) = delete;

	NaiveSingletonDatabase& operator=(const NaiveSingletonDatabase&) = delete;
	NaiveSingletonDatabase& operator=(NaiveSingletonDatabase&&) = delete;

	static NaiveSingletonDatabase* get_instance()
	{
		if(!instance)
		{
			instance = new NaiveSingletonDatabase();
		}

		return instance;
	}

	static void destroy_instance()
	{
		delete instance;
	}
};

