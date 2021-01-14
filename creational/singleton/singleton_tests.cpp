#include <iostream>
#include "singleton.hpp"
#include "naive_singleton.hpp"

//NaiveSingletonDatabase* NaiveSingletonDatabase::instance;

int main()
{
	//auto* nsd{NaiveSingletonDatabase::get_instance()};
	//NaiveSingletonDatabase::destroy_instance();

	auto& sd{SingletonDatabase::get()};
	std::cout << sd.get_population("Tokyo") << std::endl;

	return 0;
}
