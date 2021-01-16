#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>


struct IBuffer
{
	virtual void render() const = 0;
};

struct TextBuffer : public IBuffer
{
	std::vector<std::string> contents;

	void add_string(std::string str)
	{
		contents.emplace_back(std::move(str));
	}

	void render() const override
	{
		std::cout << "Buffer contents: " << std::endl;
		std::copy(contents.cbegin(), contents.cend(), std::ostream_iterator<decltype(contents)::value_type>(std::cout, "\n"));
	}
};

