#include <boost/container_hash/extensions.hpp>
#include <boost/functional/hash.hpp>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <typeindex>


struct GameObject
{
	virtual ~GameObject() = default;
	virtual std::type_index type() const = 0;
};

template<typename T>
struct GameObjectImpl : public GameObject
{
	std::type_index type() const override
	{
		return typeid(T);
	}
};

struct Planet : public GameObjectImpl<Planet>
{};

struct Spaceship : public GameObjectImpl<Spaceship>
{};

struct Asteroid : public GameObjectImpl<Asteroid>
{};

void spaceship_planet()
{
	std::cout << "spaceship lands on planet" << std::endl;
}

void asteroid_planet()
{
	std::cout << "asteroid burns up in atmosphere" << std::endl;
}

void spaceship_asteroid()
{
	std::cout << "asteroid destroys spaceship" << std::endl;
}

template <typename First, typename Second>
using pair_hash = boost::hash<std::pair<First, Second>>;


void collide(GameObject& fst, GameObject& snd)
{
	static std::unordered_map<std::pair<std::type_index, std::type_index>, std::function<void(void)>, pair_hash<std::type_index, std::type_index>> outcomes{
		{{typeid(Spaceship), typeid(Planet)}, spaceship_planet},
		{{typeid(Asteroid), typeid(Planet)}, asteroid_planet},
		{{typeid(Spaceship), typeid(Asteroid)}, spaceship_asteroid},
	};

	auto it{outcomes.find({fst.type(), snd.type()})};
	if(it == outcomes.end())
	{
		it = outcomes.find({snd.type(), fst.type()});
		if(it == outcomes.end())
		{
			std::cout << "objects pass eachother safely" << std::endl;
			return;
		}
	}

	it->second();
}

int main()
{
	Spaceship s;
	Planet p;
	Asteroid a;

	collide(s, p);
	collide(p, a);
	collide(s, a);
	collide(p, p);

	return 0;
}

