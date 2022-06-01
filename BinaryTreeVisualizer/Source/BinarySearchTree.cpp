#include "../Headers/BinarySearchTree.hpp"

namespace TreeType
{
	BinaryTree::BinaryTree()
		: data(0), left_node(nullptr), right_node(nullptr)
	{

	}
	
	BinaryTree::BinaryTree(int data)
		: data(data), left_node(nullptr), right_node(nullptr)
	{

	}

	BinaryTree::~BinaryTree() { }

	std::shared_ptr<BinaryTree> BinaryTree::InsertNode(std::shared_ptr<BinaryTree> root, int value)
	{
		//Insert into First node if Root is null
		if (!root) { return std::make_shared<BinaryTree>(value); }

		// If Value > root.Value : Insert Right
		if (value > root->data) { root->right_node = InsertNode(root->right_node, value); }

		// If Value < root.Value : Insert Left
		if (value < root->data) { root->left_node = InsertNode(root->left_node, value); }

		return root;
	}

	void BinaryTree::InOrder(std::shared_ptr<BinaryTree> root)
	{
		if (!root) { return; }
		InOrder(root->left_node);
		std::cout << root->data << std::endl;
		InOrder(root->right_node);
	}

}