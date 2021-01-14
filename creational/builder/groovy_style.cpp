#include <iostream>
#include <iterator>
#include <vector>
#include <string>
#include <sstream>


struct Tag
{
	friend std::ostream& operator<<(std::ostream& out, const Tag& tag);

protected:
	std::string name;
	std::string text;
	std::vector<Tag> children;
	std::vector<std::pair<std::string, std::string>> attributes;

	explicit Tag(std::string name, std::string text = "")
		:	name{std::move(name)},
			text{std::move(text)}
	{}

	explicit Tag(std::string name, std::vector<Tag> children)
		:	name{std::move(name)},
			children{std::move(children)}
	{}
};

std::ostream& operator<<(std::ostream& out, const Tag& tag)
{
	out << "<" << tag.name;
	for(const auto& [attr, value] : tag.attributes)
	{
		out << " " << attr << "=" << '"' << value << '"';
	}

	if(std::empty(tag.text) && std::empty(tag.children))
	{
		out << "/>";
	}
	else
	{
		out << ">";

		if(!std::empty(tag.text))
		{
			out << tag.text << std::endl;
		}

		for(const auto& child : tag.children)
		{
			out << child;
		}

		out << "</" << tag.name << ">" << std::endl;;
	}

	return out;
}

struct P : public Tag
{
	explicit P(std::string text)
		:	Tag("p", std::move(text))
	{}

	P(std::initializer_list<Tag> children)
		:	Tag("p", std::move(children))
	{}
};

struct IMG : public Tag
{
	explicit IMG(std::string url)
		:	Tag("img")
	{
		attributes.emplace_back("src", url);
	}
};

int main()
{
	std::cout << 
		P {
			IMG{"https://a.com/img.png"}
		}
	<< std::endl;

	return 0;
}
