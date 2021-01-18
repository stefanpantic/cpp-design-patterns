#pragma once

#include <memory>
#include <string>
#include <functional>
#include <unordered_map>
#include "coffee_factory.hpp"
#include "tea_factory.hpp"


class DrinkFactory
{
	std::unordered_map<std::string, std::unique_ptr<AbstractHotDrinkFactory>> factories;

public:
	DrinkFactory()
	{
		factories["coffee"] = std::make_unique<CoffeeFactory>();
		factories["tea"] = std::make_unique<TeaFactory>();
	}

	std::unique_ptr<HotDrink> make_drink(const std::string& name) const
	{
		auto elem{factories.find(name)};
		if(elem != factories.end())
		{
			return elem->second->make();
		}

		return nullptr;
	}
};

class DrinkWithVolumeFactory
{
	std::unordered_map<std::string, std::function<std::unique_ptr<HotDrink>()>> factories;

public:
	DrinkWithVolumeFactory()
	{
		factories["tea"] = [] () {
			auto tea{std::make_unique<Tea>()};
			tea->prepare(200);
			return tea;
		};

		factories["coffee"] = [] () {
			auto coffee{std::make_unique<Coffee>()};
			coffee->prepare(50);
			return coffee;
		};
	}

	std::unique_ptr<HotDrink> make(const std::string& name) const
	{
		auto elem{factories.find(name)};
		if(elem != factories.end())
		{
			return elem->second();
		}

		return nullptr;
	}
};

