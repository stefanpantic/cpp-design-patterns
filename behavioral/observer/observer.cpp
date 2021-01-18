#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
#include <any>


class Person;
class IPersonListener
{
public:
	virtual ~IPersonListener() = default;
	virtual void person_changed(Person&, const std::string& property, const std::any& value) = 0;
};

class Person
{
	size_t m_age;
	std::vector<IPersonListener*> m_listeners;
	mutable std::recursive_mutex m_mtx;
public:
	explicit Person(size_t age)
		:	m_age{age}
	{}

	int age() const
	{
		return m_age;
	}

	bool can_vote() const
	{
		return m_age >= 18;
	}

	void set_age(size_t age)
	{
		std::lock_guard<decltype(m_mtx)> lock(m_mtx);

		if(age != m_age)
		{
			m_age = age;
			notify("age", age);
		}
	}

	void subscribe(IPersonListener* pl)
	{
		std::lock_guard<decltype(m_mtx)> lock(m_mtx);

		if(std::find(m_listeners.cbegin(), m_listeners.cend(), pl) == m_listeners.cend())
		{
			m_listeners.emplace_back(pl);
		}
	}

	void unsubscribe(IPersonListener* pl)
	{
		std::lock_guard<decltype(m_mtx)> lock(m_mtx);

		auto it{std::find(m_listeners.begin(), m_listeners.end(), pl)};
		if(it != m_listeners.end())
		{
			*it = nullptr;
		}
	}

	void notify(const std::string& property, const std::any& value)
	{
		std::lock_guard<decltype(m_mtx)> lock(m_mtx);

		m_listeners.erase(
			std::remove(std::begin(m_listeners), std::end(m_listeners), nullptr),
			std::end(m_listeners)
		);

		for(auto* listener : m_listeners)
		{
			listener->person_changed(*this, property, value);
		}
	}
};

class ConsoleListener : public IPersonListener
{
public:
	void person_changed(Person&, const std::string& property, const std::any& value) override
	{
		std::cout << "Person's " << property << " has been changed to ";
		if(property == "age")
		{
			std::cout << std::any_cast<size_t>(value);
		}

		std::cout << std::endl;
	}
};

class BadListener : public IPersonListener
{
	void person_changed(Person& p, const std::string&, const std::any&) override
	{
		p.unsubscribe(this);
	}
};

int main()
{
	Person p(10);
	ConsoleListener cr;
	BadListener bl;
	p.subscribe(std::addressof(cr));
	p.set_age(11);
	p.set_age(12);
	p.subscribe(std::addressof(bl));
	p.set_age(13);
	p.unsubscribe(std::addressof(cr));
	p.set_age(17);

	return 0;
}

