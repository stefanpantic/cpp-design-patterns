#include <iostream>
#include <memory>
#include <string>


struct ILogger
{
	virtual ~ILogger() = default;
	virtual void info(const std::string& msg) = 0;
	virtual void warn(const std::string& msg) = 0;
};

struct BankAccount
{
	std::shared_ptr<ILogger> logger;
	std::string name;
	float balance;

	explicit BankAccount(std::shared_ptr<ILogger> logger, std::string name, float balance = 0)
		:	logger{std::move(logger)},
			name{std::move(name)},
			balance{balance}
	{}

	void deposit(const float amount)
	{
		balance += amount;
		logger->info("Deposited " + std::to_string(balance) + ". Balance is now $" + std::to_string(balance));
	}

	void draw(const float amount)
	{
		if(balance >= amount)
		{
			balance -= amount;
			logger->info("Withdrew $" + std::to_string(amount) + ". Balance is now $" + std::to_string(balance));
		}
		else
		{
			logger->warn("Not enough money to withdraw $" + std::to_string(amount) + ". Balance is $" + std::to_string(balance));
		}
	}
};

struct ConsoleLogger : public ILogger
{
	void info(const std::string& msg) override
	{
		std::cout << "[INFO]" << msg << std::endl;
	}

	void warn(const std::string& msg) override
	{
		std::cout << "[WARN]" << msg << std::endl;
	}
};

struct NullLogger : public ILogger
{
	void info(const std::string&) override
	{}

	void warn(const std::string&) override
	{}
};

int main()
{
	auto logger{std::make_shared<ConsoleLogger>()};
	BankAccount ba{logger, "Mark's Account", 100000};
	ba.draw(10000);
	ba.draw(100000);
	ba.draw(1000000);

	auto nulllogger{std::make_shared<NullLogger>()};
	BankAccount nlba{nulllogger, "Mark's Account", 12300};
	nlba.draw(10000);
	nlba.draw(100000);
	nlba.draw(1000000);
	return 0;
}

