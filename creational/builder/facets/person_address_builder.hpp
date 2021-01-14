#pragma once

#include <string>
#include <iostream>
#include "person_builder.hpp"


class PersonAddressBuilder : public PersonBuilder
{
public:
	explicit PersonAddressBuilder(Person& p)
		:	PersonBuilder(p)
	{}

	decltype(auto) at(std::string address)
	{
		person_reference.street_address = std::move(address);
		return *this;
	}

	decltype(auto) with_postcode(std::string pcode)
	{
		person_reference.post_code = std::move(pcode);
		return *this;
	}

	decltype(auto) in(std::string city)
	{
		person_reference.city = std::move(city);
		return *this;
	}
};
