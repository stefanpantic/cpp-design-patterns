#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "person_builder.hpp"
#include "person_address_builder.hpp"
#include "person_work_builder.hpp"


int main()
{
	Person p(Person::create()
		.lives().at("Beverly Hills, Rodeo Drive").with_postcode("90210").in("Los Angeles")
		.works().at("SoftwareCorp").as_a("Software Engineer").earning(int(10e6)));
	std::cout << p << std::endl;

	return 0;
}

