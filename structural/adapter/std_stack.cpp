#include <iostream>
#include <vector>
#include <stack>


int main()
{
	// std::stack<T, Container = std::deque<T>>
	// std::stack needs push_back(...), pop_back(), back(), ::size_type, ::reference, ...
	std::stack<int> stk;
	stk.push(1);
	stk.top();
	stk.pop();

	std::stack<int, std::vector<int>> vec_stk;
	stk.push(1);
	stk.top();
	stk.pop();

	return 0;
}

