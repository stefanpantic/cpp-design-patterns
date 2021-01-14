#include <iostream>
#include <optional>
#include <type_traits>

template <typename T>
struct Maybe;

template <typename T>
Maybe<T> maybe(std::optional<T> ctx);

template <typename T>
struct Maybe
{
	std::optional<T> context;

	explicit Maybe(std::optional<T> ctx = {})
		:	context{std::move(ctx)}
	{}

	template <typename Func>
	decltype(auto) with(Func eval)
	{
		if(!context)
		{
			return Maybe<std::decay_t<decltype(*eval(context))>>();
		}
		else
		{
			return maybe(eval(context));
		}
	}

	template <typename Func>
	decltype(auto) use(Func action)
	{
		if(context)
		{
			action(context);
		}

		return *this;
	}
};

template <typename T>
Maybe<T> maybe(std::optional<T> ctx)
{
	return Maybe<T>(std::move(ctx));
}

struct Address
{
	std::optional<std::string> house_name;

	explicit Address(std::string house_name)
		:	house_name(house_name.empty() ? std::optional<std::string>() : house_name)
	{}
};

struct Person
{
	std::optional<Address> address;

	explicit Person(std::string house_name)
		:	address(std::make_optional<Address>(house_name))
	{}
};

void print_house_name(std::optional<Person> person)
{
	maybe(person)
		.with([] (const auto& e) { return std::optional<Address>(e->address); })
		.with([] (const auto& e) { return std::optional<std::string>(e->house_name); })
		.use([] (const auto& e) { std::cout << *e << std::endl; });
}

int main()
{
	Person p1("WakeField Avenue");
	Person p2("");
	print_house_name(p1);
	print_house_name(p2);
	return 0;
}

