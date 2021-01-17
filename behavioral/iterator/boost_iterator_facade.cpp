#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <algorithm>


template <typename T>
struct Node
{
	T value;
	Node<T>* next;

	explicit Node(const T& value, Node<T>* next = nullptr)
		:	value{value},
			next{next}
	{}
};

template <typename T>
struct ListIterator : boost::iterator_facade<ListIterator<T>, Node<T>, boost::forward_traversal_tag>
{
	Node<T>* current;

	explicit ListIterator(Node<T>* ptr = nullptr)
		:	current{ptr}
	{}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		current = current->next;
	}

	bool equal(const ListIterator& other) const
	{
		return other.current == current;
	}

	Node<T>& dereference() const
	{
		return *current;
	}
};


int main()
{
	Node<int>* alpha{new Node<int>(1)};
	Node<int>* beta{new Node<int>(2, alpha)};
	Node<int>* gamma{new Node<int>(3, beta)};

	std::for_each(ListIterator<int>(gamma), ListIterator<int>(),
			[] (const auto& item)
			{
				std::cout << item.value << std::endl;
			});

	delete alpha;
	delete beta;
	delete gamma;

	return 0;
}

