#pragma once

#include <initializer_list>
#include <string>
#include <vector>
#include "visitor.hpp"



struct Element
{
	virtual ~Element() = default;
	virtual void accept(IElementVisitor&) = 0;
};

struct TextElement : public Element
{
	std::string text;

	explicit TextElement(std::string text)
		:	text{std::move(text)}
	{}
};

struct Paragraph : public TextElement
{
	explicit Paragraph(std::string text)
		:	TextElement{std::move(text)}
	{}

	void accept(IElementVisitor& visitor) override
	{
		visitor.visit(*this);
	}
};

struct ListItem : public TextElement
{
	explicit ListItem(std::string text)
		:	TextElement{std::move(text)}
	{}

	void accept(IElementVisitor& visitor) override
	{
		visitor.visit(*this);
	}
};

struct List : public std::vector<ListItem>, Element
{
	explicit List(const std::initializer_list<ListItem>& il)
		:	std::vector<ListItem>(il)
	{}

	void accept(IElementVisitor& visitor) override
	{
		visitor.visit(*this);
	}
};

