#pragma once

#include <iostream>
#include <optional>
#include "person.hpp"


class PersonAddressBuilder;
class PersonWorkBuilder;

class PersonBuilder
{
	std::optional<Person> person;
protected:
	Person &person_reference;

	explicit PersonBuilder(Person& p)
		:	person_reference(p)
	{
	}
public:
	PersonBuilder()
		:	person{Person()},
			person_reference{*person}
	{}

	operator Person();

	PersonAddressBuilder lives();
	PersonWorkBuilder works();
};

