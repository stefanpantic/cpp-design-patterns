#include "person.hpp"
#include "chat_room.hpp"
#include <iostream>
#include <functional>
#include <optional>
#include <sstream>
#include <string>


Person::Person(std::string name)
		:	m_name{std::move(name)}
{}

void Person::send(const std::string& message)
{
	if(m_hub)
	{
		m_hub->get().broadcast(m_name, message);
	}
}

void Person::recieve(const std::string& origin, const std::string& message)
{
	std::ostringstream out;
	out << "[" << m_name << "'s chat]: "
		<< origin << ": '" << message << "'";

	std::cout << out.str() << std::endl;
	m_chat_log[origin].emplace_back(message);
}

void Person::private_message(const std::string& dest, const std::string& message)
{
	m_hub->get().message(m_name, dest, message);
}

void Person::set_hub(ChatRoom& cr)
{
	m_hub = std::make_optional<std::reference_wrapper<ChatRoom>>(cr);
}

