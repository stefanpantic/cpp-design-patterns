#include <boost/flyweight.hpp>
#include <boost/flyweight/flyweight_fwd.hpp>
#include <functional>
#include <iostream>
#include <ostream>
#include <vector>


class User
{
	boost::flyweight<std::string> m_first_name, m_last_name;

public:
	explicit User(std::string first_name, std::string last_name)
		:	m_first_name{std::move(first_name)},
			m_last_name{std::move(last_name)}
	{}

	friend std::ostream& operator<<(std::ostream& out, const User& usr)
	{
		return out << "My name is " << usr.m_first_name << " " << usr.m_last_name;
	}
};

int main()
{
	std::vector<User> users{
		User{"John", "Doe"},
		User{"Mark", "Doe"},
		User{"Jane", "Doe"},
		User{"Mike", "Doe"},
		User{"Jill", "Doe"},
	};

	for(const auto& usr : users)
	{
		std::cout << usr << std::endl;
	}

	return 0;
}

