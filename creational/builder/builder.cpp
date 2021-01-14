#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <optional>


struct HtmlElement
{
	std::string tag_name;
	std::string contents;
	std::vector<HtmlElement> children;
	static constexpr std::size_t base_indent{0};

	HtmlElement() = default;

	explicit HtmlElement(std::string tag_name, std::string contents)
		:	tag_name{std::move(tag_name)},
		contents{std::move(contents)}
	{}

	std::string str(int indent_size = 0) const
	{
		std::ostringstream out;
		std::string indent_str(indent_size * base_indent, ' ');
		out << "<" << tag_name << ">";

		if(!contents.empty())
		{
			out << std::string(indent_size * (base_indent + 1), ' ') << contents;
		}

		for(const auto& e : children)
		{
			out << e.str(base_indent + 1);
		}

		out << indent_str << "</" << tag_name << ">";
		return out.str();
	}
};

struct HtmlBuilder
{
	HtmlElement root;
	explicit HtmlBuilder(std::string root_name)
		:	root{std::move(root_name), ""}
	{}

	void add_child(std::string child_name, std::string child_text)
	{
		root.children.emplace_back(std::move(child_name), std::move(child_text));
	}

	std::string str() const
	{
		return root.str();
	}
};



int main()
{
	HtmlBuilder ul{"ul"};
	ul.add_child("li", "hello");
	ul.add_child("li", "world");
	std::cout << ul.str() << std::endl;
	return 0;
}
