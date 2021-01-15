#include <iostream>
#include <functional>
#include <string>
#include <utility>

// Decorator
struct Logger
{
	std::string name;
	std::function<void()> func;

	explicit Logger(std::function<void()> func, std::string name = "N/A")
		:	name{std::move(name)},
			func{std::move(func)}
	{}

	void operator()() const
	{
		std::clog << "Entered " << name << std::endl;
		func();
		std::clog << "Exited " << name << std::endl;
	}
};

// Templated decorator
template <typename>
struct BetterLogger;

template <typename R, typename ...Args>
struct BetterLogger<R(Args...)>
{
	std::function<R(Args...)> func;
	std::string name;

	explicit BetterLogger(std::function<R(Args...)> func, std::string name = "N/A")
		:	func{std::move(func)},
			name{std::move(name)}
	{}

	R operator()(Args &&...args) const
	{
		std::clog << "Entered " << name << std::endl;
		auto res{func(std::forward<Args>(args)...)};
		std::clog << "Exited " << name << std::endl;
		return res;
	}
};

template <typename ...Args>
struct BetterLogger<void(Args...)>
{
	std::function<void(Args...)> func;
	std::string name;

	explicit BetterLogger(std::function<void(Args...)> func, std::string name = "N/A")
		:	func{std::move(func)},
			name{std::move(name)}
	{}

	void operator()(Args &&...args) const
	{
		std::clog << "Entered " << name << std::endl;
		func(std::forward<Args>(args)...);
		std::clog << "Exited " << name << std::endl;
	}
};

template <>
struct BetterLogger<void()>
{
	std::function<void()> func;
	std::string name;

	explicit BetterLogger(std::function<void()> func, std::string name = "N/A")
		:	func{std::move(func)},
			name{std::move(name)}
	{}

	void operator()() const
	{
		std::clog << "Entered " << name << std::endl;
		func();
		std::clog << "Exited " << name << std::endl;
	}
};

template<typename R, typename ...Args>
decltype(auto) make_better_logger(R(*func)(Args...), std::string name)
{
	return BetterLogger<R(Args...)>(std::function<R(Args...)>(func), std::move(name));
}

void print_hello()
{
	std::cout << "Hello" << std::endl;
}

int add(int a, int b)
{
	return a + b;
}

int main()
{
	Logger logged_hello(print_hello, "print_hello");
	logged_hello();

	Logger logged_lambda([] () { std::cout << "Lambda hello" << std::endl; }, "<lambda>");
	logged_lambda();

	BetterLogger<void(int)> better_logger([] (int x) { std::cout << x << std::endl; }, "<lambda:closure>");
	better_logger(10);

	auto best_logger{make_better_logger(print_hello, "print_hello")};
	best_logger();

	auto add_logger{make_better_logger(add, "add")};
	std::cout << add_logger(3, 5) << std::endl;

	return 0;
}

