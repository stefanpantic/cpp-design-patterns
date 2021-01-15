#pragma once

#include <memory>


struct Person
{
	struct PersonImpl;
	std::unique_ptr<PersonImpl> pimpl;

	Person();
	~Person();

	void greet();
};

