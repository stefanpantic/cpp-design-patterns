/*
 * Open Closed Principle
 */
#include <iostream>
#include <iterator>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>


enum class Color
{
	Red,
	Green,
	Blue,
};

std::string to_string(const Color& color)
{
	switch(color)
	{
		case Color::Red:
			return "Red";
		case Color::Green:
			return "Green";
		case Color::Blue:
			return "Blue";
		default:
			return "Undefined";
	}
}

enum class Size
{
	Small,
	Medium,
	Large,
};

std::string to_string(const Size& size)
{
	switch(size)
	{
		case Size::Small:
			return "Small";
		case Size::Medium:
			return "Medium";
		case Size::Large:
			return "Large";
		default:
			return "Undefined";
	}
}

struct Product
{
	std::string name;
	Color color;
	Size size;

	Product(std::string name, Color color, Size size)
		:	name{std::move(name)},
			color{std::move(color)},
			size{std::move(size)}
	{}

	friend std::ostream& operator<<(std::ostream& out, const Product& product);
};

std::ostream& operator<<(std::ostream& out, const Product& product)
{
	return out << to_string(product.size) << " " << to_string(product.color) << " " << product.name;
}

/* Open for modification not extension */
struct BadProductFilter
{
	using Items = std::vector<Product*>;

	static Items by_color(const Items& items, const Color& color)
	{
		Items ret;
		std::copy_if(items.cbegin(), items.cend(), std::back_inserter(ret), [&color] (const auto* e) { return e->color == color; });
		return ret;
	};

	static Items by_size(const Items& items, const Size& size)
	{
		Items ret;
		std::copy_if(items.cbegin(), items.cend(), std::back_inserter(ret), [&size] (const auto* e) { return e->size == size; });
		return ret;
	};

	static Items by_color_and_size(const Items& items, const Color& color, const Size& size)
	{
		Items ret;
		std::copy_if(items.cbegin(), items.cend(), std::back_inserter(ret),
					[&color, &size] (const auto* e)
					{
						return e->color == color && e->size == size;
					});
		return ret;
	};
};


/* Good way */
template <typename T>
struct ISpecification
{
	virtual ~ISpecification() = default;
	virtual bool is_satisfied(const T*) const = 0;
};

template <typename T>
struct IFilter
{
	virtual ~IFilter() = default;
	virtual std::vector<T*> filter(const std::vector<T*>&, const ISpecification<T>&) const = 0;
};

struct GoodFilter : public IFilter<Product>
{
	using Items = std::vector<Product*>;
	Items filter(const Items& items, const ISpecification<Product>& spec) const override
	{
		Items result;
		std::copy_if(items.cbegin(), items.cend(), std::back_inserter(result),
					[&spec] (const auto& e)
					{
						return spec.is_satisfied(e);
					});
		return result;
	}
};

struct ColorSpecification : public ISpecification<Product>
{
	Color color;

	explicit ColorSpecification(Color color)
		:	color{std::move(color)}
	{}

	bool is_satisfied(const Product* prod) const override
	{
		return prod->color == color;
	}
};

struct SizeSpecification : public ISpecification<Product>
{
	Size size;

	explicit SizeSpecification(Size size)
		:	size{std::move(size)}
	{}

	bool is_satisfied(const Product* prod) const override
	{
		return prod->size == size;
	}
};

template <typename T>
struct CombinedSpecification : public ISpecification<T>
{
	ISpecification<T>& first;
	ISpecification<T>& second;

	explicit CombinedSpecification(ISpecification<T>& first, ISpecification<T>& second)
		:	first{first},
			second{second}
	{}

	bool is_satisfied(const T* item) const override
	{
		return first.is_satisfied(item) && second.is_satisfied(item);
	}
};


int main()
{
	Product apple("Apple", Color::Green, Size::Small);
	Product tree("Tree", Color::Green, Size::Large);
	Product pool("Pool", Color::Blue, Size::Large);

	std::vector<Product*> all_products{&apple, &tree, &pool};

	GoodFilter gf;
	ColorSpecification green_spec(Color::Green);
	auto green_things{gf.filter(all_products, green_spec)};
	for(const auto* e : green_things)
	{
		std::cout << *e << std::endl;
	}

	std::cout << "-=-=-=-=-=-=-=-" << std::endl;

	SizeSpecification large_spec(Size::Large);
	CombinedSpecification large_green_spec(large_spec, green_spec);
	auto large_green_things{gf.filter(all_products, large_green_spec)};
	for(const auto* e : large_green_things)
	{
		std::cout << *e << std::endl;
	}


	return 0;
}
