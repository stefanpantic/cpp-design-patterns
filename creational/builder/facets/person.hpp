#pragma once

#include <iostream>
#include <string>


class PersonBuilder;
class PersonAddressBuilder;
class PersonWorkBuilder;

class Person
{
	friend PersonBuilder;
	friend PersonAddressBuilder;
	friend PersonWorkBuilder;

	// Address
	std::string street_address, post_code, city;

	// Employment
	std::string company_name, position;
	int annual_income;

	Person() = default;

public:
	static PersonBuilder create();

	Person(const Person&) = default;
	Person(Person&&) = default;

	Person& operator=(const Person&) = default;
	Person& operator=(Person&&) = default;

	~Person() = default;

	friend std::ostream& operator<<(std::ostream& out, const Person& p);
};

