#include <iostream>
#include <memory>
#include <vector>
#include "chat_room.hpp"


void ChatRoom::broadcast(const std::string& origin, const std::string& message)
{
	for(auto& p : m_people)
	{
		if(p->m_name != origin)
		{
			p->recieve(origin, message);
		}
	}
}

ChatRoom::PersonReference ChatRoom::join(std::string name)
{
	for(auto& p : m_people)
	{
		p->recieve("Room", p->m_name + " has joined the chat...");
	}

	m_people.emplace_back(std::make_shared<Person>(name));
	m_people.back()->set_hub(*this);
	return m_people.back();
}

void ChatRoom::message(const std::string& origin, const std::string& dest, const std::string& message)
{
	auto it{std::find_if(m_people.begin(), m_people.end(), [&dest] (const auto& p)
			{
				return p->m_name == dest;
			})};

	if(it != m_people.end())
	{
		(*it)->recieve(origin, message);
	};
}

ChatRoom::PersonReference::PersonReference(std::shared_ptr<Person> ptr)
	:	m_ptr{std::move(ptr)}
{}

Person& ChatRoom::PersonReference::operator*()
{
	return *m_ptr;
}

const Person& ChatRoom::PersonReference::operator*() const
{
	return *m_ptr;
}

Person* ChatRoom::PersonReference::operator->()
{
	return m_ptr.get();
}

const Person* ChatRoom::PersonReference::operator->() const
{
	return m_ptr.get();
}

