#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>


struct Shape
{
	virtual std::string str() const = 0;
};

struct Circle : public Shape
{
	float radius;

	explicit Circle(float radius)
		:	radius{radius}
	{}

	std::string str() const override
	{
		return "Circle of radius " + std::to_string(radius);
	}
};

struct Square : public Shape
{
	float size;

	explicit Square(float size)
		:	size{size}
	{}

	std::string str() const override
	{
		return "Square of side " + std::to_string(size);
	}
};

enum class Color
{
	Red,
	Green,
	Blue,
};

std::string to_string(const Color& c)
{
	switch(c)
	{
	case Color::Red:
		return "red";
	case Color::Blue:
		return "blue";
	case Color::Green:
		return "green";
	default:
		throw std::runtime_error("Invalid color.");
	}
}

struct ColoredShape : public Shape
{
	std::reference_wrapper<Shape> shape;
	Color color;

	explicit ColoredShape(Shape& shape, Color c)
		:	shape{shape},
			color{c}
	{}

	std::string str() const override
	{
		return shape.get().str() + " has color " + to_string(color);
	}
};

struct TransparentShape : public Shape
{
	std::reference_wrapper<Shape> shape;
	std::uint8_t transparency;

	explicit TransparentShape(Shape& shape, std::uint8_t transparency)
		:	shape{shape},
			transparency{transparency}
	{}

	std::string str() const override
	{
		return shape.get().str() + " with transparency " + std::to_string(transparency / 255.0f * 100) + '%';
	}
};

int main()
{
	Circle c{5};
	std::cout << c.str() << std::endl;

	ColoredShape red_circle{c, Color::Red};
	std::cout << red_circle.str() << std::endl;

	TransparentShape transparent_red_circle{red_circle, 50};
	std::cout << transparent_red_circle.str() << std::endl;

	return 0;
}

