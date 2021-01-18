#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <sstream>
#include "model.hpp"
#include "visitor.hpp"


struct HtmlVisitor : public IElementVisitor
{
	std::ostringstream oss;

	void visit(Paragraph& elem)
	{
		oss << "<p>" << elem.text << "</p>" << std::endl;
	}

	void visit(ListItem& elem)
	{
		oss << "<li>" << elem.text << "</li>" << std::endl;
	}

	void visit(List& elem)
	{
		oss << "<ul>" << std::endl;
		for(auto& li : elem)
		{
			li.accept(*this);
		}
		oss << "</ul>" << std::endl;
	}

	std::string str() const
	{
		return oss.str();
	}
};


int main()
{
	Paragraph p{"Here are some colors:"};
	ListItem red{"red"}, green{"green"}, blue{"blue"};
	List colors{red, green, blue};

	std::vector<Element*> document{std::addressof(p), std::addressof(colors)};
	HtmlVisitor visitor;
	std::for_each(document.cbegin(), document.cend(), [&visitor] (auto* ptr)
			{
				ptr->accept(visitor);
			});

	std::cout << visitor.str() << std::endl;

	return 0;
}

