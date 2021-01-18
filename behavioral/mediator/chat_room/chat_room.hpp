#pragma once

#include <functional>
#include <vector>
#include <memory>
#include "person.hpp"


class ChatRoom
{
	std::vector<std::shared_ptr<Person>> m_people;

	class PersonReference
	{
		std::shared_ptr<Person> m_ptr;
	public:
		PersonReference(std::shared_ptr<Person> ptr);
		Person& operator*();
		const Person& operator*() const;
		Person* operator->();
		const Person* operator->() const;
	};
public:

	void broadcast(const std::string& origin, const std::string& message);
	void message(const std::string& origin, const std::string& dest, const std::string& message);
	PersonReference join(std::string name);
};
