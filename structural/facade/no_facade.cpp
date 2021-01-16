#include <iostream>
#include <memory>
#include "window.hpp"
#include "buffer.hpp"
#include "viewport.hpp"


int main()
{
	Window window{"Test", Size{1920, 1080}};

	auto buffer{std::make_shared<TextBuffer>()};
	buffer->add_string("one");
	buffer->add_string("two");
	buffer->add_string("three");
	buffer->add_string("four");
	buffer->add_string("five");

	window.add_buffer(buffer);

	auto viewport_a{std::make_shared<Viewport>(buffer, Size{100, 100}, Point{0, 0})};
	window.add_viewport(viewport_a);

	auto viewport_b{std::make_shared<Viewport>(buffer, Size{50, 50}, Point{30, 30})};
	window.add_viewport(viewport_b);

	window.show();
	return 0;
}
