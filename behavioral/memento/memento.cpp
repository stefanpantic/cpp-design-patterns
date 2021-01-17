#include <iostream>
#include <ostream>

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
public:
	explicit BankAccount(const int balance = 0)
		:	balance{balance}
	{}

	Memento deposit(const int amount)
	{
		balance += amount;
		return balance;
	}

	void restore(const Memento& m)
	{
		balance = m.balance;
	}

	friend std::ostream& operator<<(std::ostream& out, const BankAccount ba)
	{
		return out << "Balance: " << ba.balance << std::endl;
	}
};

int main()
{
	BankAccount ba{1000};
	auto m1{ba.deposit(50)}; // 150
	auto m2{ba.deposit(25)}; // 175
	std::cout << ba << std::endl;
	ba.restore(m1);
	std::cout << ba << std::endl;
	ba.restore(m2);
	std::cout << ba << std::endl;

	return 0;
}

