#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>


enum class OutputFormat
{
	Markdown,
	Html,
};

struct ListStrategy
{
	virtual ~ListStrategy() = default;
	virtual void begin(std::ostringstream& oss) = 0;
	virtual void end(std::ostringstream& oss) = 0;
	virtual void add_list_item(std::ostringstream& oss, const std::string& item) = 0;
};

struct MarkdownListStrategy : public ListStrategy
{
	void begin(std::ostringstream&) override {}
	void end(std::ostringstream&) override {}
	void add_list_item(std::ostringstream& oss, const std::string& item) override
	{
		oss << "* " << item << std::endl;
	}
};

struct HtmlListStrategy : public ListStrategy
{
	void begin(std::ostringstream& oss) override
	{
		oss << "<ul>" << std::endl;
	}

	void end(std::ostringstream& oss) override
	{
		oss << "</ul>" << std::endl;
	}

	void add_list_item(std::ostringstream& oss, const std::string& item) override
	{
		oss << "<li>" << item << "</li>" << std::endl;
	}
};

class TextProcessor
{
	std::ostringstream m_res;
	std::unique_ptr<ListStrategy> m_strategy;
public:
	explicit TextProcessor(OutputFormat of)
	{
		set_output_format(of);
	}

	void append_list(const std::vector<std::string>& items)
	{
		m_strategy->begin(m_res);
		for(const auto& item : items)
		{
			m_strategy->add_list_item(m_res, item);
		}
		m_strategy->end(m_res);
	}

	void set_output_format(OutputFormat of)
	{
		switch(of)
		{
		case OutputFormat::Markdown:
			m_strategy = std::make_unique<MarkdownListStrategy>();
			break;
		case OutputFormat::Html:
			m_strategy = std::make_unique<HtmlListStrategy>();
			break;
		}
	}

	void clear()
	{
		m_res.str("");
		m_res.clear();
	}

	std::string str() const
	{
		return m_res.str();
	}
};


int main()
{
	TextProcessor tf(OutputFormat::Markdown);
	tf.append_list({"foo", "bar", "baz"});
	std::cout << tf.str() << std::endl;
	tf.clear();
	tf.set_output_format(OutputFormat::Html);
	tf.append_list({"foo", "bar", "baz"});
	std::cout << tf.str() << std::endl;

	return 0;
}

