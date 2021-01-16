#pragma once

#include <memory>
#include <ostream>
#include "buffer.hpp"


struct Size
{
	size_t width, height;

	Size(size_t w, size_t h)
		:	width{w},
			height{h}
	{}

	friend std::ostream& operator<<(std::ostream& out, const Size& sz)
	{
		return out << "[width = " << sz.width << ", height = " << sz.height << "]";
	}
};

struct Point
{
	size_t x, y;

	Point(size_t x_pos, size_t y_pos)
		:	x{x_pos},
			y{y_pos}
	{}

	friend std::ostream& operator<<(std::ostream& out, const Point& pos)
	{
		return out << "[x = " << pos.x << ", y = " << pos.y << "]";
	}
};

struct Viewport
{
	std::shared_ptr<IBuffer> buffer;
	Size size;
	Point position;

	explicit Viewport(std::shared_ptr<IBuffer> buf, Size sz, Point pos = {0, 0})
		:	buffer{std::move(buf)},
			size{std::move(sz)},
			position{std::move(pos)}
	{}

	void update() const
	{
		std::cout << "Rendering buffer in Viewport of size " << size << " on position " << position << std::endl;
		std::cout << "[" << std::endl;
		buffer->render();
		std::cout << "]" << std::endl;
	}
};

