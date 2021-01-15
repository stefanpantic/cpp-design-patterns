#include <exception>
#include <functional>
#include <iostream>
#include <ostream>
#include <vector>
#include <memory>


struct Neuron
{
	std::vector<std::reference_wrapper<Neuron>> in, out;
	int id;

	explicit Neuron()
		:	id{0}
	{
		static int ID{1};
		id = ID++;
	}

	template <typename T>
	void connect_to(T& other)
	{
		for(Neuron& target : other)
		{
			connect_to(target);
		}
	}

	Neuron* begin()
	{
		return this;
	}

	Neuron* end()
	{
		return begin() + 1;
	}

	friend std::ostream& operator<<(std::ostream& out, const Neuron& n)
	{
		for(const auto& e : n.in)
		{
			out << "[" << e.get().id << "] --> (" << n.id << ")" << std::endl;
		}

		for(const auto& e : n.out)
		{
			out << "(" << n.id << ") --> [" << e.get().id << "]" << std::endl;
		}

		return out;
	}
};

template <>
void Neuron::connect_to(Neuron& other)
{
	out.emplace_back(other);
	other.in.emplace_back(*this);
}

struct NeuronLayer : public std::vector<Neuron>
{
	NeuronLayer(int count)
		:	std::vector<Neuron>(count)
	{}

	template <typename T>
	void connect_to(T& other)
	{
		for(Neuron& from : *this)
		{
			for(Neuron& to : other)
			{
				from.connect_to(to);
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& out, const NeuronLayer& nl)
	{
		for(const auto& e : nl)
		{
			out << e << std::endl;
		}

		return out;
	}
};


int main()
{
	Neuron n1, n2;
	n1.connect_to(n2);
	n2.connect_to(n1);
	std::cout << n1.in.size() << " " << n1.out.size() << std::endl;
	std::cout << n2.in.size() << " " << n2.out.size() << std::endl;
	std::cout << n1 << n2 << std::endl;

	NeuronLayer nl{14};
	nl.connect_to(n1);
	std::cout << nl << std::endl;

	return 0;
}

