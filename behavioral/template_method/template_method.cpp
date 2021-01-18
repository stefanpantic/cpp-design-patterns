#include <iostream>
#include <string>


class Game
{
protected:
	int m_num_players;
	int m_current_player;

	virtual void start() = 0;
	virtual bool game_over() = 0;
	virtual void play() = 0;
	virtual void end() = 0;
public:
	explicit Game(const int num_players)
		:	m_num_players{num_players},
			m_current_player{0}
	{}

	void run()
	{
		start();
		while(!game_over())
		{
			play();
		}
		end();
	}
};


class Chess : public Game
{
	int m_turns;
protected:
	void start()
	{
		std::cout << "Starting a game of chess with " << m_num_players << " players!" << std::endl;
	}

	bool game_over()
	{
		return !(m_turns > 0);
	}

	void play()
	{
		std::cout << "Player " << m_current_player << " played a move." << std::endl;
		m_current_player = (m_current_player + 1) % 2;
		--m_turns;
	}

	void end()
	{
		std::cout << "Player " << m_current_player << " won!";
	}
public:
	explicit Chess(const int num_players)
		:	Game(num_players),
			m_turns{10}
	{}
};


int main()
{
	Chess c{2};
	c.run();
	return 0;
}

