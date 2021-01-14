#pragma once

#include <string>
#include "person_builder.hpp"


class PersonWorkBuilder : public PersonBuilder
{
public:
	explicit PersonWorkBuilder(Person& p)
		:	PersonBuilder(p)
	{}

	decltype(auto) at(std::string corp)
	{
		person_reference.company_name = std::move(corp);
		return *this;
	}

	decltype(auto) as_a(std::string pos)
	{
		person_reference.position = std::move(pos);
		return *this;
	}

	decltype(auto) earning(int salary)
	{
		person_reference.annual_income = std::move(salary);
		return *this;
	}
};

