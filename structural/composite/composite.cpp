#include <iostream>
#include <memory>

// 2 + (3 + 4)
struct Expression
{
	virtual double eval() = 0;
};

struct LiteralExpression : public Expression
{
	float value;

	explicit LiteralExpression(float val)
		:	value{val}
	{}

	double eval() override
	{
		return value;
	}
};

struct AdditionExpression : public Expression
{
	std::shared_ptr<Expression> lhs, rhs;

	explicit AdditionExpression(std::shared_ptr<Expression> lhs_ptr, std::shared_ptr<Expression> rhs_ptr)
		:	lhs{std::move(lhs_ptr)},
			rhs{std::move(rhs_ptr)}
	{}

	double eval() override
	{
		return lhs->eval() + rhs->eval();
	}
};

int main()
{
	AdditionExpression addition{
		std::make_shared<AdditionExpression>(
				std::make_shared<LiteralExpression>(10.0),
				std::make_shared<LiteralExpression>(23.43)
				),
		std::make_shared<LiteralExpression>(34.43)
	};

	std::cout << addition.eval() << std::endl;

	return 0;
}

