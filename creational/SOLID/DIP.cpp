/*
 * Dependency Inversion Principle
 *
 * 1. 	High-level modules (i. e. a reporting module) should not depend on low-level modules (i. e. a ConsoleLogger).
 * 		Both should depend on abstractions (i. e. the reporting module can depend on ILogger).
 *
 * 2.	Abstractons should not depend on details. Details should depend on abstractions.
 * 		Dependencies on interfaces and supertypes is better than dependencies on concrete types.
 */
#include <iostream>
#include <ostream>
#include <memory>
#include "di.hpp"


struct ILogger
{
	virtual ~ILogger() = default;
	virtual void log(const std::string& s) = 0;
};

struct ConsoleLogger : public ILogger
{
	void log(const std::string& s) override
	{
		std::clog << s << std::endl;
	}
};

struct Engine
{
	float volume;
	size_t hp;

	explicit Engine(float vol = 2.0, size_t hp = 220)
		:	volume{vol},
			hp{hp}
	{}

	friend std::ostream& operator<<(std::ostream& out, const Engine& eng);
};

std::ostream& operator<<(std::ostream& out, const Engine& eng)
{
	return out << "[engine volume = " << eng.volume << ", engine_hp = " << eng.hp << "]";
}

struct Car
{
	std::shared_ptr<Engine> engine;
	std::shared_ptr<ILogger> logger;

	explicit Car(std::shared_ptr<Engine> engine, std::shared_ptr<ILogger> logg)
		:	engine(std::move(engine)),
			logger(std::move(logg))
	{
		logger->log("car is created");
	}

	friend std::ostream& operator<<(std::ostream& out, const Car& car);
};

std::ostream& operator<<(std::ostream& out, const Car& car)
{
	return out << "[car with engine = " << *car.engine << "]";
}


int main()
{
	//auto eng{std::make_shared<Engine>()};
	//auto car{std::make_shared<Car>(eng)};
	//std::cout << *car << std::endl;
	
	auto injector{boost::di::make_injector(
		boost::di::bind<ILogger>.to<ConsoleLogger>(),
		boost::di::bind<Engine>.to(std::make_shared<Engine>(2.0, 220ul))
	)};
	auto car{injector.create<std::shared_ptr<Car>>()};
	std::cout << *car << std::endl;

	return 0;
}
