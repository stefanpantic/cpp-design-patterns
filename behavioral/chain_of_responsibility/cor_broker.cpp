#include <boost/signals2.hpp>
#include <boost/signals2/connection.hpp>
#include <functional>
#include <iostream>
#include <ostream>
#include <string>


struct Query
{
	std::string creature_name;
	enum class Argument { Attack, Defense, } argument;
	int result;

	explicit Query(std::string creature_name, const Argument arg, const int result)
		:	creature_name{std::move(creature_name)},
			argument{std::move(arg)},
			result{result}
		{}
};

struct Game
{
	boost::signals2::signal<void(Query&)> queries;
};

class Creature
{
	std::reference_wrapper<Game> m_game;
	int m_attack, m_defense;

public:
	std::string name;

	explicit Creature(Game& game, std::string name, int atk, int def)
		:	m_game{game},
			m_attack{atk},
			m_defense{def},
			name{std::move(name)}
	{}

	int attack() const
	{
		Query q{name, Query::Argument::Attack, m_attack};
		m_game.get().queries(q);
		return q.result;
	}

	int defense() const
	{
		Query q{name, Query::Argument::Defense, m_defense};
		m_game.get().queries(q);
		return q.result;
	}

	friend std::ostream& operator<<(std::ostream& out, const Creature& cr)
	{
		return out << "[Creature " << cr.name << ", attack = " << cr.attack() << ", defense = " << cr.defense() << "]";
	}
};


class CreatureModifier
{
	std::reference_wrapper<Game> m_game;
	std::reference_wrapper<Creature> m_creature;

public:
	explicit CreatureModifier(Game& game, Creature& creature)
		:	m_game{game},
			m_creature{creature}
	{}

	virtual ~CreatureModifier() = default;
};

class DoubleAttackModifier : public CreatureModifier
{
	boost::signals2::connection conn;
public:
	explicit DoubleAttackModifier(Game& game, Creature& cr)
		:	CreatureModifier{game, cr}
	{
		conn = game.queries.connect([&] (auto& q)
		{
			if(q.creature_name == cr.name && q.argument == Query::Argument::Attack)
			{
				q.result *= 2;
			}
		});
	}

	~DoubleAttackModifier()
	{
		conn.disconnect();
	}
};


int main()
{
	Game g{};
	Creature goblin{g, "Goblin", 2, 2};
	std::cout << goblin << std::endl;

	{
		DoubleAttackModifier dam{g, goblin};
		std::cout << goblin << std::endl;
	}

	std::cout << goblin << std::endl;
	return 0;
}

