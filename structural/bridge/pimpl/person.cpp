#include "person.hpp"
#include <iostream>
#include <memory>


struct Person::PersonImpl
{
	void greet()
	{
		std::cout << "hi!" << std::endl;
	}
};

Person::Person()
	:	pimpl{new PersonImpl}
{}

Person::~Person() = default;

void Person::greet()
{
	pimpl->greet();
}

