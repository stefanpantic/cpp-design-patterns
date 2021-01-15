#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include "geometry.hpp"


class LineToPointCachingAdapter
{
	size_t line_hash;
	static std::unordered_map<size_t, std::vector<Point>> cache;

public:
	explicit LineToPointCachingAdapter(const Line& line)
	{
		boost::hash<Line> hashfunc;
		line_hash = hashfunc(line);
		if(cache.find(line_hash) == cache.end())
		{
			cache[line_hash] = line_to_points(line);
		}
	}

	decltype(auto) begin() const
	{
		return cache[line_hash].begin();
	}

	decltype(auto) end() const
	{
		return cache[line_hash].end();
	}
};

/* static */std::unordered_map<size_t, std::vector<Point>> LineToPointCachingAdapter::cache;

class LineToPointAdapter
{
	using Points = std::vector<Point>;
	Points points;

public:
	explicit LineToPointAdapter(const Line& line)
		:	points{line_to_points(line)}
	{}

	decltype(auto) begin() const
	{
		return points.begin();
	}

	decltype(auto) end() const
	{
		return points.end();
	}
};


int main()
{
	std::vector<std::shared_ptr<VectorObject>> rectangles{
		std::make_shared<VectorRectangle>(10, 10, 100, 100),
		std::make_shared<VectorRectangle>(30, 30, 60, 60),
	};

	for(const auto& rect : rectangles)
	{
		for(const auto& pt : *rect)
		{
			LineToPointCachingAdapter adapter{pt};
			for(const auto& e : adapter)
			{
				std::cout << e.x << " " << e.y << std::endl;
			}
		}
	}

	return 0;
}
