#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>
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

struct ICommand
{
	virtual ~ICommand() = default;
	virtual void invoke() const = 0;
	virtual void undo() const = 0;
};

struct Command : public ICommand
{
	std::reference_wrapper<BankAccount> bank_account;
	enum class Action { Deposit, Withdraw, } action;
	int amount;

	explicit Command(BankAccount& ba, Action act, int amount)
		:	bank_account{ba},
			action{std::move(act)},
			amount{amount}
	{}

	void invoke() const override
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

	void undo() const override
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

struct CommandList : public std::vector<std::shared_ptr<ICommand>>, ICommand
{

	CommandList(const std::initializer_list<std::shared_ptr<ICommand>>& il)
		:	std::vector<std::shared_ptr<ICommand>>{il}
	{}

	void invoke() const override
	{
		std::for_each(cbegin(), cend(), [] (const auto& cmd) { cmd->invoke(); });
	}

	void undo() const override
	{
		std::for_each(crbegin(), crend(), [] (const auto& cmd) { cmd->undo(); });
	}
};


int main()
{
	BankAccount ba{1000};
	CommandList commands{
		std::make_shared<Command>(ba, Command::Action::Deposit, 100),
		std::make_shared<Command>(ba, Command::Action::Withdraw, 200),
	};

	std::cout << ba.balance << std::endl;
	commands.invoke();
	std::cout << ba.balance << std::endl;
	commands.undo();
	std::cout << ba.balance << std::endl;

	return 0;
}
