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
	std::shared_ptr<Address> work_address;

	explicit Contact(std::string name, std::shared_ptr<Address> address)
		:	name{std::move(name)},
			work_address{address ? std::make_shared<Address>(*address) : nullptr}
	{}

	Contact(const Contact& other)
		:	name{other.name},
			work_address{other.work_address ? std::make_shared<Address>(*other.work_address) : nullptr}
		{}

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


int main()
{
	// Employee prototype
	Contact employee("", std::make_shared<Address>("Wall St.", "New York", 0));

	// Customize John
	auto john{employee};
	john.name = "John Doe";
	john.work_address->suite = 100;
	std::cout << john << std::endl;

	// Customize Jane
	auto jane{employee};
	jane.name = "Jane Doe";
	jane.work_address->suite = 101;
	std::cout << jane << std::endl;

	return 0;
}

