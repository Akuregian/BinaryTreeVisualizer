#include "../Headers/BinarySearchTree.hpp"

namespace TreeType
{

	BinaryTree::BinaryTree(int data)
		: left_node(nullptr),
		  right_node(nullptr),
		  dir(RootDir::ROOT),
		  nodeObject(std::make_shared<Object::Node>(data)),
		  level(0),
		  branch_side(Branch::ROOT_BRANCH),
		  parent(nullptr)
	{

	}

	BinaryTree::~BinaryTree() { }

	std::shared_ptr<BinaryTree> BinaryTree::InsertNode(std::shared_ptr<BinaryTree> root, int value, int ref_level)
	{
		//Insert into First node if Root is null
		if (!root) {  return std::make_shared<BinaryTree>(value); }
		ref_level++;

		// If Value > root.Value : Insert Right
		if (value > root->nodeObject->data) 
		{ 
			root->right_node = InsertNode(root->right_node, value, ref_level); 
			root->right_node->dir = RootDir::RIGHT; 
			root->right_node->branch_side = Branch::RIGHT_BRANCH;
			root->right_node->level = ref_level--;
			root->right_node->parent = root;
		}

		// If Value < root.Value : Insert Left
		if (value < root->nodeObject->data) 
		{ 
			root->left_node = InsertNode(root->left_node, value, ref_level);
			root->left_node->dir = RootDir::LEFT; 
			root->left_node->branch_side = Branch::LEFT_BRANCH;
			root->left_node->level = ref_level--;
			root->left_node->parent = root;
		}

		return root;
	}

	// Delete a Node
	std::shared_ptr<BinaryTree> BinaryTree::DeleteNode(std::shared_ptr<BinaryTree> root, int key)
	{
		if (!root) { return root; };

		// Recursive Call To Find Node to be deleted
		if (root->nodeObject->data > key) 
		{ 
			root->left_node = DeleteNode(root->left_node, key); 
			return root;
		}
		else if (root->nodeObject->data < key) 
		{ 
			root->right_node = DeleteNode(root->right_node, key); 
			return root;
		}

		// If One Child is Empty
		if (!root->left_node)
		{
			std::shared_ptr<BinaryTree> temp = root->right_node;
			root.reset();
			return temp;
		}
		else if (!root->right_node)
		{
			std::shared_ptr<BinaryTree> temp = root->left_node;
			root.reset();
			return temp;
		}
		else
		{
			// Find Successor
			std::shared_ptr<TreeType::BinaryTree> successor_Parent = root;
			std::shared_ptr<TreeType::BinaryTree> successor = root->right_node;

			while(successor->left_node)
			{
				successor_Parent = successor;
				successor = successor->left_node;
			}

			if (successor_Parent != root)
				successor_Parent->left_node = successor->right_node;
			else
				successor_Parent->right_node = successor->right_node;

			root->nodeObject = successor->nodeObject;
			successor.reset();
			return root;
		}
	}

}