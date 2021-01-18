#pragma once

#include <iostream>


struct HotDrink
{
	virtual void prepare(float volume) = 0;
};

struct Tea : public HotDrink
{
	void prepare(float volume) override
	{
		std::cout << volume << "ml of Tea" << std::endl;
	}
};

struct Coffee : public HotDrink
{
	void prepare(float volume) override
	{
		std::cout << volume << "ml of Coffee" << std::endl;
	}
};

