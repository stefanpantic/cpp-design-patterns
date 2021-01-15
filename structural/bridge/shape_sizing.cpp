#include <iostream>


struct Renderer
{
	virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : public Renderer
{
	void render_circle(float x, float y, float radius) override
	{
		std::cout << "Drawing a vector circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
	}
};

struct RasterRenderer : public Renderer
{
	void render_circle(float x, float y, float radius) override
	{
		std::cout << "Rasterizing a circle at (" << x << ", " << y << ") with radius " << radius << std::endl;
	}
};

struct Shape
{
protected:
	// Bridge
	Renderer& renderer;

	explicit Shape(Renderer& r)
		:	renderer{r}
	{}

public:
	virtual void draw() = 0;
	virtual void resize(float factor) = 0;
};

struct Circle : public Shape
{
	float x, y, radius;

	explicit Circle(Renderer& r, float x, float y, float radius)
		:	Shape{r},
			x{x},
			y{y},
			radius{radius}
	{}

	void draw() override
	{
		renderer.render_circle(x, y, radius);
	}

	void resize(float factor) override
	{
		radius *= factor;
	}
};

int main()
{
	RasterRenderer rr;
	Circle raster_circle(rr, 10, 11, 3.4);
	raster_circle.draw();
	raster_circle.resize(2);
	raster_circle.draw();

	return 0;
}

