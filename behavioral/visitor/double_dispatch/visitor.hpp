#pragma once

struct TextElement;
struct Paragraph;
struct ListItem;
struct List;


struct IElementVisitor
{
	virtual ~IElementVisitor() = default;
	virtual void visit(Paragraph&) = 0;
	virtual void visit(ListItem&) = 0;
	virtual void visit(List&) = 0;
};

