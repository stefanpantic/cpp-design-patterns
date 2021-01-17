#include <bits/c++config.h>
#include <iostream>
#include <memory>

template <typename T>
class BinaryTree;

template <typename T>
struct Node
{
	using pointer = Node<T>*;

	T value;
	pointer left, right, parent;
	BinaryTree<T>* tree_ptr;

	explicit Node(const T& value, pointer left_ptr = nullptr, pointer right_ptr = nullptr)
		:	value{value},
			left{std::move(left_ptr)},
			right{std::move(right_ptr)}
	{
		if(left)
		{
			left->parent = this;
		}

		if(right)
		{
			right->parent = this;
		}
	}

	~Node()
	{
		if(left)
		{
			delete left;
			left = nullptr;
		}

		if(right)
		{
			delete right;
			right = nullptr;
		}
	}

	void set_tree(BinaryTree<T>* tree)
	{
		tree_ptr = tree;
		if(left)
		{
			left->set_tree(tree);
		}

		if(right)
		{
			right->set_tree(tree);
		}
	}
};

template <typename T>
class BinaryTree
{
	using NodePtr = typename Node<T>::pointer;
	NodePtr root;

public:
	template <typename U>
	struct BinaryTreeIterator
	{
		Node<U>* current;

		BinaryTreeIterator(NodePtr ptr)
			:	current{ptr}
		{}

		U& operator*()
		{
			return current->value;
		}

		bool operator==(const BinaryTreeIterator& other)
		{
			return current == other.current;
		}

		bool operator!=(const BinaryTreeIterator& other)
		{
			return !(*this == other);
		}

		BinaryTreeIterator operator++(int)
		{
			auto res{*this};
			++(*this);
			return res;
		};

		BinaryTreeIterator& operator++()
		{
			if(current->right)
			{
				current = current->right;
				while(current->left)
				{
					current = current->left;
				}
			}
			else
			{
				auto p{current->parent};
				while(p && current == p->right)
				{
					current = p;
					p = current->parent;
				}

				current = current->parent;
			}

			return *this;
		};
	};

	using iterator = BinaryTreeIterator<T>;

	BinaryTree()
		:	root{nullptr}
	{}

	explicit BinaryTree(const T& value)
		:	root{new Node<T>(value)}
	{}

	explicit BinaryTree(decltype(root) root)
		:	root{root}
	{}

	~BinaryTree()
	{
		if(root)
		{
			delete root;
			root = nullptr;
		}
	}

	iterator begin() const
	{
		auto item{root};
		while(item && item->left)
		{
			item = item->left;
		}

		return item;
	}

	iterator end() const
	{
		return nullptr;
	}
};

int main()
{
	BinaryTree<std::string> family{
		new Node<std::string>{"me",
			new Node<std::string>{"mother",
				new Node<std::string>{"mother's mother"},
				new Node<std::string>{"mother's father"}
			},
			new Node<std::string>{"father",
				new Node<std::string>{"father's mother"},
				new Node<std::string>{"father's father"}
			}
		}
	};


	for(const auto& member : family)
	{
		std::cout << member << std::endl;
	}

	return 0;
}

