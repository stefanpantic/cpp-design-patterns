#include <iostream>
#include <memory>


struct Image
{
	virtual ~Image() = default;
	virtual void draw() const = 0;
};

struct Bitmap : public Image
{
	explicit Bitmap(const std::string& filename)
	{
		std::cout << "Loading bitmap from " << filename << std::endl;
	}

	void draw() const override
	{
		std::cout << "Drawing bitmap..." << std::endl;
	}
};

struct LazyBitmap : public Image
{
	explicit LazyBitmap(std::string filename)
		:	filename{std::move(filename)}
	{}

	void draw() const override
	{
		if(bmp)
		{
			bmp = std::make_unique<Bitmap>(filename);
		}

		bmp->draw();
	}
private:
	mutable std::unique_ptr<Bitmap> bmp;
	std::string filename;
};

void draw_image(const Image& img)
{
	std::cout << "About to draw Image..." << std::endl;
	img.draw();
	std::cout << "Drew Image..." << std::endl;
}

void virtual_proxy()
{
	LazyBitmap b{"file.png"};
	draw_image(b);
}

int main()
{
	virtual_proxy();
	return 0;
}

