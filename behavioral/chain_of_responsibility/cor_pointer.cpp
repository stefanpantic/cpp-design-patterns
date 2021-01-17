#include <functional>
#include <iostream>
#include <ostream>
#include <string>
#include <memory>


struct Creature
{
	std::string name;
	int attack, defense;

	explicit Creature(std::string name, int atk, int def)
		:	name{std::move(name)},
			attack{atk},
			defense{def}
	{}

	friend std::ostream& operator<<(std::ostream& out, const Creature& cr)
	{
		return out << "[Creature " << cr.name << ", attack = " << cr.attack << ", defense = " << cr.defense << "]";
	}
};

class CreatureModifier
{
	CreatureModifier* next{nullptr};
protected:
	std::reference_wrapper<Creature> creature;
public:
	explicit CreatureModifier(Creature& cr)
		:	creature{cr}
	{}

	virtual ~CreatureModifier() = default;

	void add(CreatureModifier* cm)
	{
		if(next)
		{
			next->add(std::move(cm));
		}
		else
		{
			next = std::move(cm);
		}
	}

	virtual void handle()
	{
		if(next)
		{
			next->handle();
		}
	}
};

// 1. Double Creature's attack
// 2. Increases defense by 1 unless power is greater than 2
// 3. No bonuses can be applied to this creature
class DoubleAttackModifier : public CreatureModifier
{
public:
	explicit DoubleAttackModifier(Creature& cr)
		:	CreatureModifier{cr}
	{}

	void handle() override
	{
		creature.get().attack *= 2;
		CreatureModifier::handle();
	}
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:
	explicit IncreaseDefenseModifier(Creature& cr)
		:	CreatureModifier{cr}
	{}

	void handle() override
	{
		auto& cr{creature.get()};
		if(cr.attack <= 2)
		{
			++cr.defense;
		}

		CreatureModifier::handle();
	}
};

class NoBonusModifier : public CreatureModifier
{
public:
	explicit NoBonusModifier(Creature& cr)
		:	CreatureModifier{cr}
	{}

	void handle() override
	{}
};

int main()
{
	Creature goblin{"Goblin", 10, 13};
	std::cout << goblin << std::endl;

	CreatureModifier root{goblin};
	DoubleAttackModifier rt1{goblin};
	IncreaseDefenseModifier rt2{goblin};
	root.add(&rt1);
	root.add(&rt2);
	root.handle();

	std::cout << goblin << std::endl;
	return 0;
}

