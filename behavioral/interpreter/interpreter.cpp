#include <boost/lexical_cast.hpp>
#include <cctype>
#include <iostream>
#include <iterator>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <memory>


struct Token
{
	enum class Type { Literal, Plus, Minus, LParen, RParen, } type;
	std::string text;

	explicit Token(Type type, std::string text)
		:	type{std::move(type)},
			text{std::move(text)}
	{}

	friend std::ostream& operator<<(std::ostream& out, const Token& t)
	{
		return out << "`" << t.text << "`";
	}
};

std::vector<Token> lex(std::string input)
{
	std::vector<Token> result;
	for(auto i = 0ull; i < std::size(input); ++i)
	{
		if (input[i] == '+')
		{
			result.emplace_back(Token::Type::Plus, std::string(1, input[i]));
		}
		else if (input[i] == '-')
		{
			result.emplace_back(Token::Type::Minus, std::string(1, input[i]));
		}
		else if (input[i] == '(')
		{
			result.emplace_back(Token::Type::LParen, std::string(1, input[i]));
		}
		else if (input[i] == ')')
		{
			result.emplace_back(Token::Type::RParen, std::string(1, input[i]));
		}
		else if (std::isdigit(input[i]))
		{
			std::ostringstream out;
			out << input[i++];
			while(i < std::size(input) && std::isdigit(input[i]))
			{
				out << input[i];
				++i;
			}

			result.emplace_back(Token::Type::Literal, out.str());
			--i;
		}
		else if (input[i] == ' ')
		{
			// Do nothing!
			continue;
		}
		else
		{
			std::ostringstream err_msg;
			err_msg << "Invalid token";
			err_msg << " `" << input[i] << "` ";
			err_msg << " found while lexing!";
			throw std::runtime_error{err_msg.str()};
		}
	}

	return result;
}


struct IElement
{
	virtual int eval() const = 0;
};

struct Literal : public IElement
{
	int val;

	explicit Literal(int value)
		:	val{value}
	{}

	int eval() const override
	{
		return val;
	}
};

struct BinaryOperation : public IElement
{
	std::shared_ptr<IElement> lhs, rhs;
	enum class Type { Plus, Minus, NoOp } type;

	explicit BinaryOperation(std::shared_ptr<IElement> lhs = nullptr, std::shared_ptr<IElement> rhs = nullptr, Type t = Type::NoOp)
		:	lhs{std::move(lhs)},
			rhs{std::move(rhs)},
			type{std::move(t)}
	{}

	int eval() const override
	{
		auto lhs_val{lhs->eval()}, rhs_val{rhs->eval()};
		switch(type)
		{
		case Type::Plus:
			return lhs_val + rhs_val;
		case Type::Minus:
			return lhs_val - rhs_val;
		default:
			throw std::runtime_error{"Unsupported operation!"};
		}
	}
};

std::shared_ptr<IElement> parse(const std::vector<Token>& tokens)
{
	auto result{std::make_shared<BinaryOperation>()};
	for(auto i = 0ull; i < std::size(tokens); ++i)
	{
		switch(tokens[i].type)
		{
		case Token::Type::Literal:
			{
				auto lit{std::make_shared<Literal>(boost::lexical_cast<int>(tokens[i].text))};
				if(result->lhs == nullptr)
				{
					result->lhs = std::move(lit);
				}
				else
				{
					result->rhs = std::move(lit);
				}
			}
			break;
		case Token::Type::Plus:
			result->type = BinaryOperation::Type::Plus;
			break;
		case Token::Type::Minus:
			result->type = BinaryOperation::Type::Minus;
			break;
		case Token::Type::LParen:
			{
				auto j{i};
				while(j < std::size(tokens) && tokens[j].type != Token::Type::RParen)
				{
					++j;
				}

				if(j == std::size(tokens))
				{
					throw std::runtime_error{"Mismatched paranthesis!"};
				}

				auto subexpr{std::vector<Token>(tokens.begin() + (i + 1), tokens.begin() + j)};
				auto elem{parse(subexpr)};
				if(result->lhs == nullptr)
				{
					result->lhs = std::move(elem);
				}
				else
				{
					result->rhs = std::move(elem);
				}

				i = j;
			}
			break;
		default:
			break;
		}
	}

	return result;
}

int main()
{
	std::string input{"(13 - 4) - (12 + 1)"};
	auto res{lex(input)};
	std::copy(res.cbegin(), res.cend(), std::ostream_iterator<decltype(res)::value_type>(std::cout, " "));
	auto tree{parse(res)};
	std::cout << input << " = " << tree->eval() << std::endl;

	return 0;
}

