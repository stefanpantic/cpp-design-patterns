#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <memory>


enum class OutputFormat
{
	Markdown,
	Html,
};

struct ListPolicy
{
	virtual ~ListPolicy() = default;
	virtual void begin(std::ostringstream& oss) = 0;
	virtual void end(std::ostringstream& oss) = 0;
	virtual void add_list_item(std::ostringstream& oss, const std::string& item) = 0;
};

struct MarkdownListPolicy : public ListPolicy
{
	void begin(std::ostringstream&) override {}
	void end(std::ostringstream&) override {}
	void add_list_item(std::ostringstream& oss, const std::string& item) override
	{
		oss << "* " << item << std::endl;
	}
};

struct HtmlListPolicy : public ListPolicy
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

template <typename FormatPolicy>
class TextProcessor
{
	static_assert(std::is_base_of_v<ListPolicy, FormatPolicy>);

	std::ostringstream m_res;
	FormatPolicy m_strategy;
public:
	template <typename ...Args>
	explicit TextProcessor(Args&& ...args)
		:	m_strategy{std::forward<Args>(args)...}
	{}

	void append_list(const std::vector<std::string>& items)
	{
		m_strategy.begin(m_res);
		for(const auto& item : items)
		{
			m_strategy.add_list_item(m_res, item);
		}
		m_strategy.end(m_res);
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
	TextProcessor<MarkdownListPolicy> md_tf;
	md_tf.append_list({"foo", "bar", "baz"});
	std::cout << md_tf.str() << std::endl;

	TextProcessor<HtmlListPolicy> html_tf;
	html_tf.append_list({"foo", "bar", "baz"});
	std::cout << html_tf.str() << std::endl;

	return 0;
}

