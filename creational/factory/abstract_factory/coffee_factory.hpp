#pragma once

#include "abstract_hot_drink_factory.hpp"
#include "hot_drink.hpp"


struct CoffeeFactory : public AbstractHotDrinkFactory
{
	std::unique_ptr<HotDrink> make() override
	{
		return std::make_unique<Coffee>();
	}
};

