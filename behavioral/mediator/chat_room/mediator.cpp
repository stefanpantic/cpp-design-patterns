#include <iostream>
#include "chat_room.hpp"
#include "person.hpp"


int main()
{
	ChatRoom room;
	auto p{room.join("Peter")};
	auto m{room.join("Mark")};
	auto j{room.join("John")};
	p->send("Hi everyone!");
	m->send("Hi everyone!");
	j->send("Hi everyone!");
	j->private_message("Peter", "Yo Pete!");

	return 0;
}

