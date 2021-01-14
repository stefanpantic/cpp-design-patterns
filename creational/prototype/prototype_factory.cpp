#include <iostream>
#include <ostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>


struct Address
{
	std::string street_address, city;
	int suite;

	explicit Address(std::string street_address, std::string city, int suite)
		:	street_address{std::move(street_address)},
			city{std::move(city)},
			suite{suite}
	{}

	friend std::ostream& operator<<(std::ostream& out, const Address& addr)
	{
		return out << addr.street_address << ", " << addr.city << ", " << addr.suite;
	}
};

struct Contact
{
	std::string name;
	std::unique_ptr<Address> work_address;

	explicit Contact(std::string name, std::unique_ptr<Address> address)
		:	name{std::move(name)},
			work_address{address ? std::make_unique<Address>(*address) : nullptr}
	{}

	Contact(const Contact& other)
		:	name{other.name},
			work_address{other.work_address ? std::make_unique<Address>(*other.work_address) : nullptr}
		{}

	Contact& operator=(const Contact& other)
	{
		name = other.name;
		work_address = other.work_address ? std::make_unique<Address>(*other.work_address) : nullptr;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, const Contact& ct)
	{
		out << ct.name;
		if(ct.work_address)
		{
			out << ", " << *ct.work_address;
		}

		return out;
	}
};

struct EmployeeFactory
{
	// Contact prototypes
	static Contact main_office_proto, aux_office_proto;

	static std::unique_ptr<Contact> make_main_office_employee(std::string name, int suite)
	{
		return make_employee(std::move(name), suite, main_office_proto);
	}

	static std::unique_ptr<Contact> make_aux_office_employee(std::string name, int suite)
	{
		return make_employee(std::move(name), suite, aux_office_proto);
	}

private:
	static std::unique_ptr<Contact> make_employee(std::string name, int suite, Contact& proto)
	{
		auto res{std::make_unique<std::decay_t<decltype(proto)>>(proto)};
		res->name = std::move(name);
		res->work_address->suite = suite;
		return res;
	}
};

/* static */Contact EmployeeFactory::main_office_proto("", std::make_unique<Address>("Wall St.", "New York", 0));
/* static */Contact EmployeeFactory::aux_office_proto("", std::make_unique<Address>("Rodeo Drive", "Los Angeles", 0));

int main()
{
	// Customize John
	auto john{EmployeeFactory::make_main_office_employee("John Doe", 100)};
	std::cout << *john << std::endl;

	// Customize Jane
	auto jane{EmployeeFactory::make_aux_office_employee("Jane Doe", 101)};
	std::cout << *jane << std::endl;

	return 0;
}

