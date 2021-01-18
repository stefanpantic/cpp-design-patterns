#pragma once

#include <string>
#include <unordered_map>
#include <optional>
#include <functional>


class ChatRoom;

class Person
{
	std::string m_name;
	std::optional<std::reference_wrapper<ChatRoom>> m_hub;
	std::unordered_map<std::string, std::vector<std::string>> m_chat_log;

	friend class ChatRoom;
	void set_hub(ChatRoom& cr);
public:
	Person(std::string name);

	Person(const Person&) = delete;
	Person(Person&&) = default;

	Person& operator=(const Person&) = delete;
	Person& operator=(Person&&) = default;

	void send(const std::string& message);
	void recieve(const std::string& origin, const std::string& message);
	void private_message(const std::string& dest, const std::string& message);
	const std::string& name() const;
};

