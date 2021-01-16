#pragma once

#include <memory>
#include <string>
#include "window.hpp"
#include "buffer.hpp"
#include "viewport.hpp"


// Facade
class Console
{
	std::vector<std::shared_ptr<Window>> windows;

	Console() = default;

public:
	Console(const Console&)	= delete;
	Console& operator=(const Console&)	= delete;

	static Console& instance()
	{
		static Console inst;
		return inst;
	}

	std::shared_ptr<Window> single(const std::string& title, size_t width, size_t height)
	{
		Size sz{width, height};

		auto win{std::make_shared<Window>(title, sz)};

		auto buffer{std::make_shared<TextBuffer>()};
		win->add_buffer(buffer);

		auto viewport{std::make_shared<Viewport>(buffer, sz)};
		win->add_viewport(viewport);

		instance().windows.push_back(win);

		return win;
	}

	std::shared_ptr<Window> multi(const std::string& title, size_t vp_count, size_t width, size_t height)
	{
		auto win{std::make_shared<Window>(title, Size{width * vp_count, height})};
		for(auto i = 0ull; i < vp_count; ++i)
		{
			auto buffer{std::make_shared<TextBuffer>()};
			win->add_buffer(buffer);
			win->add_viewport(std::make_shared<Viewport>(buffer, Size{width, height}, Point{width * i, 0}));
		}

		return win;
	}
};

