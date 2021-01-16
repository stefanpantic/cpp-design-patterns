#include <iostream>
#include <ostream>
#include <string>
#include <memory>


struct IBankAccount
{
	virtual ~IBankAccount() = default;
	virtual void deposit(int amount) = 0;
	virtual void withdraw(int amount) = 0;
};

class CurrentAccount : public IBankAccount
{
	int m_balance;

public:
	explicit CurrentAccount(int balance = 0)
		:	m_balance{balance}
	{}

	void deposit(int amount) override
	{
		m_balance += amount;
	}

	void withdraw(int amount) override
	{
		if(m_balance >= amount)
		{
			m_balance -= amount;
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const CurrentAccount& ca)
	{
		return out << "Balance: " << ca.m_balance << std::endl;
	}
};

int main()
{
	auto dumb_ptr{new CurrentAccount(100)};
	dumb_ptr->deposit(100);
	std::cout << *dumb_ptr << std::endl;
	delete dumb_ptr;

	auto smart_ptr{std::make_shared<CurrentAccount>(100)};
	smart_ptr->deposit(100);
	std::cout << *smart_ptr << std::endl;
	CurrentAccount* underlying_ptr{smart_ptr.get()};
	std::cout << *underlying_ptr << std::endl;

	return 0;
}

