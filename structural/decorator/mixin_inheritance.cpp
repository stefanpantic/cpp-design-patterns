#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
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

	void resize(double factor)
	{
		radius *= factor;
	}

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
	None
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
		return "none";
	}
}

template <typename T>
struct ColoredShape : public T
{
	static_assert(std::is_base_of_v<Shape, T>, "Template parameter must be a Shape.");

	Color color;

	template <typename ...Args>
	explicit ColoredShape(Color c, Args&& ...args)
		:	T{std::forward<Args>(args)...},
			color{c}
	{}

	std::string str() const override
	{
		return T::str() + " has color " + to_string(color);
	}
};

template <typename T>
struct TransparentShape : public T
{
	static_assert(std::is_base_of_v<Shape, T>, "Template argument must be a Shape.");

	std::uint8_t transparency;

	template <typename ...Args>
	explicit TransparentShape(std::uint8_t transparency, Args&& ...args)
		:	T{std::forward<Args>(args)...},
			transparency{transparency}
	{}

	std::string str() const override
	{
		return T::str() + " with transparency " + std::to_string(transparency / 255.0f * 100) + '%';
	}
};

int main()
{
	ColoredShape<Circle> red_circle(Color::Red, 10.0f);
	std::cout << red_circle.str() << std::endl;

	TransparentShape<ColoredShape<Circle>> red_transparent_circle(50, Color::Red, 10.0f);
	std::cout << red_transparent_circle.str() << std::endl;

	return 0;
}

