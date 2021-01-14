#include "person.hpp"
#include "person_builder.hpp"
#include <fstream>
#include <ostream>

/* static */PersonBuilder Person::create()
{
	return PersonBuilder();
}

/* friend */std::ostream& operator<<(std::ostream& out, const Person& p)
{
	return out
		<< "address = " << p.street_address << " "
		<< "postal code = " << p.post_code << " "
		<< "city = " << p.city << " "
		<< "company name = " << p.company_name << " "
		<< "position = " << p.position << " "
		<< "earns = " << p.annual_income << " ";
}

