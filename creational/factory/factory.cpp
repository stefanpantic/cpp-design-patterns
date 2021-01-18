#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>

class PointFactory;

class Point
{
	friend class PointFactory;

	float x, y;

	explicit Point(float a, float b)
		:	x{a}, y{b}
	{}

public:
	friend std::ostream& operator<<(std::ostream& out, const Point& p)
	{
		return out << "(x = " << p.x << ", y = " << p.y << ")";
	}
};

class PointFactory
{
public:
	static Point from_cartesian(float x, float y)
	{
		return Point(x, y);
	}

	static Point from_polar(float r, float theta)
	{
		return Point(r * std::cos(theta), r * std::sin(theta));
	}
};

int main()
{
	auto cart{PointFactory::from_cartesian(1, 1)};
	auto pol{PointFactory::from_polar(1, 1)};

	std::cout << cart << " " << pol << std::endl;

	return 0;
}

