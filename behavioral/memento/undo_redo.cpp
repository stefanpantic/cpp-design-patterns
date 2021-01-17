#include <iostream>
#include <ostream>
#include <memory>
#include <vector>


class BankAccount;

class Memento
{
	friend class BankAccount;

	int balance;
public:
	Memento(const int balance)
		:	balance{balance}
	{}


};

class BankAccount
{
	int balance;
	std::vector<std::shared_ptr<Memento>> changes;
	int current;

public:
	explicit BankAccount(const int balance = 0)
		:	balance{balance}
	{
		changes.emplace_back(std::make_shared<Memento>(balance));
		current = 0;
	}

	std::shared_ptr<Memento> deposit(const int amount)
	{
		balance += amount;
		auto m{std::make_shared<Memento>(balance)};
		if(current + 1ull < changes.size())
		{
			auto distance{std::distance(changes.begin() + current + 1, changes.end())};
			changes.erase(changes.begin() + current + 1, changes.end());
			current -= distance;
		}

		changes.push_back(m);
		++current;
		return m;
	}

	void restore(std::shared_ptr<Memento> m)
	{
		if(m)
		{
			balance = m->balance;
		}

		changes.emplace_back(std::move(m));
		current = (changes.size() - 1);
	}

	std::shared_ptr<Memento> undo()
	{
		if(current > 0)
		{
			--current;
			auto m{changes[current]};
			balance = m->balance; // duplicated some behavior from restore()
			return m;
		}

		return nullptr;
	}

	std::shared_ptr<Memento> redo()
	{
		if(current + 1ull < changes.size())
		{
			++current;
			auto m{changes[current]};
			balance = m->balance;
			return m;
		}

		return nullptr;
	}

	friend std::ostream& operator<<(std::ostream& out, const BankAccount ba)
	{
		return out << "Balance: " << ba.balance;
	}
};

int main()
{
	BankAccount ba{100};
	std::cout << ba << std::endl;
	ba.deposit(50);
	std::cout << ba << std::endl;
	ba.deposit(25);
	std::cout << ba << std::endl;
	ba.deposit(10);
	std::cout << ba << std::endl;
	ba.undo();
	std::cout << ba << std::endl;
	ba.redo();
	std::cout << ba << std::endl;
	ba.undo();
	ba.deposit(0);
	std::cout << ba << std::endl;
	ba.redo();
	std::cout << ba << std::endl;

	return 0;
}

