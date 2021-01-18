/*
 * Interface segregation principle
 *
 * No client should be forced to depend on functions that it doesn't use
 */
#include <vector>

struct Document;

/* Bad, functions should not be grouped */
struct IBadMachine
{
	using Documents = std::vector<Document*>;
	virtual void print(const Document&) = 0;
	virtual void scan(const Documents&) = 0;
	virtual void fax(const Documents&) = 0;
};

struct MFP : public IBadMachine
{
	void print(const Document&) override
	{}

	void scan(const Documents&) override
	{}

	void fax(const Documents&) override
	{}
};

/* Good, segregate interface */
struct IPrinter
{
	virtual ~IPrinter() = default;
	virtual void print(const std::vector<Document*>&) = 0;
};

struct IScanner
{
	virtual ~IScanner() = default;
	virtual void scan(const std::vector<Document*>&) = 0;
};

struct Printer : public IPrinter
{
	void print(const std::vector<Document*>&) override
	{}
};

struct IMachine : public IPrinter, public IScanner
{};

struct Machine : public IMachine
{
	IPrinter& printer;
	IScanner& scanner;

	explicit Machine(IPrinter& printer, IScanner& scanner)
		:	printer{printer},
			scanner{scanner}
	{}

	void print(const std::vector<Document*>& docs) override
	{
		printer.print(docs);
	}

	void scan(const std::vector<Document*>& docs) override
	{
		scanner.scan(docs);
	}
};

int main()
{
	return 0;
}

