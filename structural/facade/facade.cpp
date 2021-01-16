#include <iostream>
#include <memory>
#include "console.hpp"


int main()
{
	auto& console{Console::instance()};
	auto win{console.single("Console", 1280, 720)};
	win->show();

	auto multi_win{console.multi("Console", 2, 1280, 720)};
	multi_win->show();
	return 0;
}
