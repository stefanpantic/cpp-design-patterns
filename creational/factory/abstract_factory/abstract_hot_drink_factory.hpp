#pragma once

#include <memory>

class HotDrink;

struct AbstractHotDrinkFactory
{
	virtual std::unique_ptr<HotDrink> make() = 0;
};
