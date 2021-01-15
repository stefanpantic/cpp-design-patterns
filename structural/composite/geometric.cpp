#include <iostream>
#include <memory>
#include <vector>

struct GraphicObject
{
	virtual void draw() = 0;
};

struct Circle : public GraphicObject
{
	void draw() override
	{
		std::cout << "Rendering a circle." << std::endl;
	}
};

class Group : public GraphicObject
{
	std::string name;
	std::vector<std::shared_ptr<GraphicObject>> grouped;

public:
	explicit Group(std::string name, std::vector<std::shared_ptr<GraphicObject>> object_vector = {})
		:	name{std::move(name)},
			grouped{std::move(object_vector)}
	{}

	void push_back(std::shared_ptr<GraphicObject> obj)
	{
		grouped.emplace_back(std::move(obj));
	}

	void draw() override
	{
		std::cout << "Renering group named " << name << ". Contens: " << std::endl;
		for(const auto& e : grouped)
		{
			e->draw();
		}
	}
};


int main()
{
	Group root("root");
	root.push_back(std::make_shared<Circle>());
	root.push_back(std::make_shared<Circle>());

	Group nested("nested");
	nested.push_back(std::make_shared<Circle>());
	nested.push_back(std::make_shared<Circle>());
	nested.push_back(std::make_shared<Circle>());

	root.push_back(std::make_shared<Group>(nested));

	root.draw();

	return 0;
}

