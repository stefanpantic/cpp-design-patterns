#include <boost/signals2.hpp>
#include <iostream>
#include <memory>

namespace signals = boost::signals2;

struct IEvent
{
	virtual ~IEvent() = default;
	virtual void print() const = 0;
};

struct Player;

struct PlayerScored : public IEvent
{
	std::string name;
	int goals_scored;

	explicit PlayerScored(std::string name, int goals_scored)
		:	name{std::move(name)},
			goals_scored{goals_scored}
	{}

	void print() const override
	{
		std::cout << name << " just scored their " << goals_scored << " goal!" << std::endl;
	}
};

struct Game // event broker
{
	signals::signal<void(IEvent*)> events; // Observer
};

struct Player
{
	std::string name;
	int goals_scored;
	Game& game;

	explicit Player(std::string name, Game& game)
		:	name{std::move(name)},
			goals_scored{0},
			game{game}
	{}

	void score()
	{
		++goals_scored;
		PlayerScored ps{name, goals_scored};
		game.events(std::addressof(ps));
	}
};

struct Coach
{
	explicit Coach(Game& game)
	{
		game.events.connect([] (IEvent* e)
		{
			auto x{dynamic_cast<PlayerScored*>(e)};
			if(x && x->goals_scored < 3)
			{
				std::cout << "RRRREEESI! " << x->name << std::endl;
			}
		});
	}
};

int main()
{
	Game g;
	Player p{"Marcus", g};
	Coach c{g};
	p.score();
	p.score();
	p.score();
	p.score();

	return 0;
}

