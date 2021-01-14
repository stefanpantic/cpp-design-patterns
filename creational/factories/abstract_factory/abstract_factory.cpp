#include <iostream>
#include <map>
#include <memory>
#include <type_traits>
#include "hot_drink.hpp"
#include "drink_factory.hpp"

template<typename Drink>
std::unique_ptr<Drink> make_drink()
{
	static_assert(std::is_base_of_v<HotDrink, Drink>);

	auto drink{std::make_unique<Drink>()};
	if constexpr (std::is_same_v<Tea, Drink>)
	{
		drink->prepare(200);
	}
	else if constexpr (std::is_same_v<Coffee, Drink>)
	{
		drink->prepare(50);
	}

	return drink;
}

int main()
{
	auto tea{make_drink<Tea>()};

	DrinkFactory df;
	df.make_drink("coffee")->prepare(100);
	
	DrinkWithVolumeFactory dwv;
	dwv.make("tea");

	return 0;
}

