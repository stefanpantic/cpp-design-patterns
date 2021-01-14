#include <boost/serialization/access.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <iostream>
#include <functional>
#include <memory>
#include <ostream>
#include <sstream>

// One way to do a deep copy is to define a clone member function
//template <typename T>
//struct ICloneable
//{
//	virtual T clone() = 0;
//};

struct Address
{
	std::string street, city;
	int suite;

	explicit Address(std::string str = "", std::string ct = "", int st = 0)
		:	street{std::move(str)},
			city{std::move(ct)},
			suite{st}
	{}

	friend std::ostream& operator<<(std::ostream& out, const Address& addr)
	{
		return out << addr.street << ", " << addr.city << ", " << addr.suite;
	}

private:
	friend class boost::serialization::access;

	template <typename Archive>
	void serialize(Archive& arch, unsigned int)
	{
		arch & street;
		arch & city;
		arch & suite;
	}
};

struct Contact
{
	std::string name;
	Address address;

	friend std::ostream& operator<<(std::ostream& out, const Contact& cont)
	{
		return out << "name = " << cont.name << ", address = " << cont.address;
	}

private:
	friend boost::serialization::access;

	template <typename Archive>
	void serialize(Archive& arch, unsigned int)
	{
		arch & name;
		arch & address;
	}
};


int main()
{
	Contact john;
	john.name = "John Doe";
	john.address = Address("Wall St.", "New York", 100);

	auto clone{[] (Contact c)
	{
		std::stringstream oss;
		boost::archive::text_oarchive oa(oss);
		oa << c;

		auto s{oss.str()};
		std::cerr << "-=-=-=-=-" << std::endl;
		std::cerr << s << std::endl;
		std::cerr << "-=-=-=-=-" << std::endl;
		
		Contact result;
		std::istringstream iss(oss.str());
		boost::archive::text_iarchive ia(iss);
		ia >> result;

		return result;
	}};

	auto jane{clone(john)};
	jane.name = "Jane Doe";
	jane.address.street = "Random St.";

	std::cout << john << std::endl << jane << std::endl;

	return 0;
}

