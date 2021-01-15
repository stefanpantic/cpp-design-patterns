#pragma once

#include <boost/container_hash/extensions.hpp>
#include <boost/container_hash/hash_fwd.hpp>
#include <boost/functional/hash.hpp>
#include <vector>


struct Point
{
	int x, y;

	Point(int x, int y)
		:	x{x}, y{y}
	{}

	friend std::size_t hash_value(const Point& p)
	{
		std::size_t seed{0x1e4493f};
		boost::hash_combine(seed, p.x);
		boost::hash_combine(seed, p.y);
		return seed;
	}
};

struct Line
{
	Point begin, end;

	Line(Point a, Point b)
		:	begin{std::move(a)},
			end{std::move(b)}
	{}

	friend std::size_t hash_value(const Line& p)
	{
		std::size_t seed{0x52e4f07a};
		boost::hash_combine(seed, p.begin);
		boost::hash_combine(seed, p.end);
		return seed;
	}
};

struct VectorObject
{
	virtual std::vector<Line>::iterator begin() = 0;
	virtual std::vector<Line>::iterator end() = 0;
};

class VectorRectangle : public VectorObject
{
	std::vector<Line> m_lines;

public:
	VectorRectangle(int x, int y, int width, int height)
		:	m_lines{
				{{x, y}, {x + width, y}},
				{{x + width, y}, {x + width, y + height}},
				{{x, y}, {x, y + height}},
				{{x, y + height}, {x + width, y + height}},
			}
	{}

	std::vector<Line>::iterator begin() override
	{
		return m_lines.begin();
	}

	std::vector<Line>::iterator end() override
	{
		return m_lines.end();
	}
};


inline std::vector<Point> line_to_points(const Line& line)
{
	std::vector<Point> points;

	auto left{std::min(line.begin.x, line.end.x)};
	auto right{std::max(line.begin.x, line.begin.y)};
	auto bottom{std::min(line.begin.y, line.end.y)};
	auto top{std::max(line.begin.y, line.end.y)};
	auto dx{right - left}, dy{line.end.y - line.begin.y};

	if(dx == 0) // vertical
	{
		for(int y = top; y < bottom; --y)
		{
			points.emplace_back(left, y);
		}
	}
	else if (dy == 0) // horizontal
	{
		for(int x = left; x < right; ++x)
		{
			points.emplace_back(x, top);
		}
	}
	else // TODO: Non-vertical/horizontal line support
	{}

	return points;
}
