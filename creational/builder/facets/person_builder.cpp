#include "person_builder.hpp"
#include "person_address_builder.hpp"
#include "person_work_builder.hpp"


PersonBuilder::operator Person()
{
	return std::move(person_reference);
}

PersonAddressBuilder PersonBuilder::lives()
{
	return PersonAddressBuilder(person_reference);
}

PersonWorkBuilder PersonBuilder::works()
{
	return PersonWorkBuilder(person_reference);
}

