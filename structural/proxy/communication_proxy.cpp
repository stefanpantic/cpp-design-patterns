#include <iostream>
#include <string>

struct IPingable
{
	virtual ~IPingable() = default;
	virtual std::string ping(const std::string& msg) = 0;
};

struct Pong : public IPingable
{
	std::string ping(const std::string& msg) override
	{
		return msg + " PONG";
	}
};

struct RemotePong : public IPingable
{
	std::string ping(const std::string& msg) override
	{
		std::cout << "Pretend that this is pinging a server..." << std::endl;
		return msg + " PONG";
	}
};

void try_it(IPingable& p)
{
	std::cout << p.ping("PING") << std::endl;
}


int main()
{
	Pong p;
	try_it(p);

	RemotePong rp;
	try_it(rp);

	return 0;
}

