#include <cmath>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>


class Point
{
	float x, y;

	explicit Point(float a, float b)
		:	x{a}, y{b}
	{}

public:
	static Point from_cartesian(float x, float y)
	{
		return Point(x, y);
	}

	static Point from_polar(float r, float theta)
	{
		return Point(r * std::cos(theta), r * std::sin(theta));
	}

	friend std::ostream& operator<<(std::ostream& out, const Point& p)
	{
		return out << "(x = " << p.x << ", y = " << p.y << ")";
	}
};



int main()
{
	auto cart{Point::from_cartesian(1, 1)};
	auto pol{Point::from_polar(1, 1)};

	std::cout << cart << " " << pol << std::endl;

	return 0;
}

