#include <boost/signals2.hpp>
#include <iostream>
#include <any>

namespace bs2 = boost::signals2;

template <typename T>
class INotifyPropertyChanged
{
public:
	virtual ~INotifyPropertyChanged() = default;
	bs2::signal<void(T&, const std::string&)> property_changed;
};

class Person : public INotifyPropertyChanged<Person>
{
	size_t m_age;

public:
	explicit Person(const size_t age)
		:	m_age{age}
	{}

	int age() const
	{
		return m_age;
	}

	void set_age(size_t age)
	{
		if(m_age != age)
		{
			m_age = age;
			property_changed(*this, "age");
		}
	}
};

int main()
{
	Person p{10};
	p.property_changed.connect([] (auto&, const auto& property_name) {
			std::cout << property_name << " has been changed!" << std::endl;
	});
	p.set_age(20);

	return 0;
}

