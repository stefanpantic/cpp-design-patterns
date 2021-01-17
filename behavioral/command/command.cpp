#include <algorithm>
#include <iostream>
#include <vector>


struct BankAccount
{
	int balance;
	int overdraft_limit{-500};

	void deposit(int amount)
	{
		balance += amount;
		std::cout << "Deposited $" << amount << ". Balance is now $" << balance << std::endl;
	}

	void withdraw(int amount)
	{
		if(balance - amount >= overdraft_limit)
		{
			balance -= amount;
			std::cout << "Withdrew $" << amount << ". Balance is now $" << balance << std::endl;
		}
		else
		{
			std::cout << "Couldn't withdraw $" << amount << ". Balance is $" << balance << ", and overdraft limit is $" << overdraft_limit << std::endl;
		}
	}
};

struct Command
{
	std::reference_wrapper<BankAccount> bank_account;
	enum class Action { Deposit, Withdraw, } action;
	int amount;

	explicit Command(BankAccount& ba, Action act, int amount)
		:	bank_account{ba},
			action{std::move(act)},
			amount{amount}
	{}

	void invoke() const
	{
		switch(action)
		{
		case Action::Deposit:
			bank_account.get().deposit(amount);
			break;
		case Action::Withdraw:
			bank_account.get().withdraw(amount);
			break;
		default:
			break;
		};
	}

	void undo() const
	{
		switch(action)
		{
		case Action::Withdraw:
			bank_account.get().deposit(amount);
			break;
		case Action::Deposit:
			bank_account.get().withdraw(amount);
			break;
		default:
			break;
		};
	}
};


int main()
{
	BankAccount ba{1000};
	std::vector<Command> commands{
		Command(ba, Command::Action::Deposit, 100),
		Command(ba, Command::Action::Withdraw, 200),
	};

	std::cout << ba.balance << std::endl;
	std::for_each(commands.cbegin(), commands.cend(), [] (const auto& e) { e.invoke(); });
	std::cout << ba.balance << std::endl;
	std::for_each(commands.crbegin(), commands.crend(), [] (const auto& e) { e.undo(); });
	std::cout << ba.balance << std::endl;

	return 0;
}
