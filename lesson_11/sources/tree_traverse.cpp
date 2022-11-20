#include <iostream>

struct Node
{
	Node(int v = 0) : value(v), left(nullptr), right(nullptr)
	{}

	int value;

	Node * left;
	Node * right;
};

template < typename T, typename... TP >
Node * traverse(T np, TP... paths)
{
	return (np ->* ... ->* paths); // np ->* paths1 ->* paths2 ...
}

int main(int argc, char ** argv)
{
	auto root = new Node(0);

	root->left = new Node(1);
	root->left->right = new Node(2);

	/*
			 0
			/ \
		   1   nullptr
		  / \
	nullptr  2
			/ \
	 nullptr   nullprt

	*/

	auto left  = &Node::left;
	auto right = &Node::right;

	auto node = traverse(root, left, right);

	std::cout << node->value << std::endl;

	return EXIT_SUCCESS;
}