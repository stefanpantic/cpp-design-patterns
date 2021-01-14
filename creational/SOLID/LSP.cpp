/*
 * Objects in a program should be replaceable with instances of their subtypes
 */
#include <iostream>


class Rectangle
{
protected:
	int m_width, m_height;

public:
	explicit Rectangle(int width, int height)
		:	m_width{width},
			m_height{height}
	{}

	virtual ~Rectangle() = default;

	virtual void set_width(int width)
	{
		m_width = width;
	}

	virtual void set_height(int height)
	{
		m_height = height;
	}

	int get_width() const
	{
		return m_width;
	}

	int get_height() const
	{
		return m_height;
	}

	int area() const
	{
		return m_width * m_height;
	}
};

class Square : public Rectangle
{
public:
	explicit Square(int size)
		:	Rectangle(size, size)
	{}

	void set_width(int width) override
	{
		Rectangle::set_width(width);
		Rectangle::set_height(width);
	}

	void set_height(int height) override
	{
		Rectangle::set_width(height);
		Rectangle::set_height(height);
	}

	/* Possible fix */
	// Add a set_size() function
};

void process(Rectangle& r)
{
	auto w{r.get_width()};
	r.set_height(10);

	std::cout << "expect area = " << (w * 10) << ", got area = " << r.area() << std::endl;
}

/* Possible fix */
struct RectangleFactory
{
	static Rectangle create_rectangle(int w, int h);
	static Rectangle create_square(int s);
};

int main()
{
	Rectangle r(5, 5);
	process(r);

	Square s(5);
	process(s);

	return 0;
}
