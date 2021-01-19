#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <optional>

struct HtmlBuilder;

struct HtmlElement
{
	std::string tag_name;
	std::string contents;
	std::vector<HtmlElement> children;
	static constexpr std::size_t base_indent{1};

	HtmlElement() = default;

	explicit HtmlElement(std::string tag_name, std::string contents)
		:	tag_name{std::move(tag_name)},
		contents{std::move(contents)}
	{}

	std::string str(int indent_size = 0) const
	{
		std::ostringstream out;
		std::string indent_str(indent_size * base_indent, ' ');
		out << indent_str << "<" << tag_name << ">" << std::endl;;

		if(!contents.empty())
		{
			out << std::string(indent_size * (base_indent + 1), ' ') << contents << std::endl;;
		}

		for(const auto& e : children)
		{
			out << e.str(base_indent + 1);
		}

		out << indent_str << "</" << tag_name << ">" << std::endl;;
		return out.str();
	}

	static HtmlBuilder build(std::string name);
	static std::unique_ptr<HtmlBuilder> create(std::string name);
};

struct HtmlBuilder
{
	HtmlElement root;
	explicit HtmlBuilder(std::string root_name)
		:	root{std::move(root_name), ""}
	{}

	HtmlBuilder& add_child(std::string child_name, std::string child_text)
	{
		root.children.emplace_back(std::move(child_name), std::move(child_text));
		return *this;
	}

	operator HtmlElement() { return root; }

	std::string str() const
	{
		return root.str();
	}
};

/* static */HtmlBuilder HtmlElement::build(std::string name)
{
	return HtmlBuilder(std::move(name));
}

/* static */ std::unique_ptr<HtmlBuilder> HtmlElement::create(std::string name)
{
	return std::make_unique<HtmlBuilder>(std::move(name));
}

int main()
{
	HtmlBuilder ul{"ul"};
	ul.add_child("li", "hello").add_child("li", "world");
	std::cout << ul.str() << std::endl;

	HtmlElement elem{HtmlElement::build("ul").add_child("li", "ola")};
	std::cout << elem.str() << std::endl;

	return 0;
}
