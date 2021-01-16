#include <boost/bimap.hpp>
#include <functional>
#include <iostream>
#include <ostream>
#include <vector>


class User
{
	using key = std::uint32_t;
	static boost::bimap<key, std::string> name_storage;

	key m_first_name, m_last_name;

	static std::string get_item(key k)
	{
		auto it{name_storage.left.find(k)};
		if(it == name_storage.left.end())
		{
			throw std::runtime_error{"Key " + std::to_string(k) + " not in name storage"};
		}

		return it->second;
	}

	static key add(const std::string& name)
	{
		static key seed{0};

		auto it{name_storage.right.find(name)};
		if(it != name_storage.right.end())
		{
			return it->second;
		}

		auto id{++seed};
		name_storage.insert(decltype(name_storage)::value_type(id, name));
		return id;
	}

public:
	explicit User(const std::string& first_name, const std::string& last_name)
		:	m_first_name{add(first_name)},
			m_last_name{add(last_name)}
	{}

	std::string first_name() const
	{
		return get_item(m_first_name);
	}

	std::string last_name() const
	{
		return get_item(m_last_name);
	}

	friend std::ostream& operator<<(std::ostream& out, const User& usr)
	{
		return out << "My name is " << usr.first_name() << " " << usr.last_name();
	}
};

/* static */boost::bimap<User::key, std::string> User::name_storage;

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

