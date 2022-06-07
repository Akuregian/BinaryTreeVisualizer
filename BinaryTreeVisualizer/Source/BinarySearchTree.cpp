#include "../Headers/BinarySearchTree.hpp"

namespace TreeType
{
	
	BinaryTree::BinaryTree(int data)
		: left_node(nullptr), 
		  right_node(nullptr), 
		  dir(RootDir::ROOT), 
		  nodeObject(std::make_shared<Object::Node>(data)), 
		  level(0)
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
			root->right_node->dir = RIGHT; 
			root->right_node->level = ref_level--;
		}

		// If Value < root.Value : Insert Left
		if (value < root->nodeObject->data) 
		{ 
			root->left_node = InsertNode(root->left_node, value, ref_level);
			root->left_node->dir = LEFT; 
			root->left_node->level = ref_level--;
		}

		
		return root;
	}

	// Delete a Node
	std::shared_ptr<BinaryTree> BinaryTree::DeleteNode(std::shared_ptr<BinaryTree> root, int key)
	{
		if (root == nullptr) { return root; };

		// Find Node to be deleted
		if (key < root->nodeObject->data) { root->left_node = DeleteNode(root->right_node, key); }
		else if (key > root->nodeObject->data) { root->right_node = DeleteNode(root->right_node, key); }
		else {
			// node has no child
			if (root->left_node && root->right_node)
			{
				return nullptr;
			}
			else if (root->left_node)
			{
				std::shared_ptr<BinaryTree> temp = root->right_node;
				root.reset();
				return temp;
			}
			else if (root->right_node)
			{
				std::shared_ptr<BinaryTree> temp = root->left_node;
				root.reset();
				return temp;
			}

			std::shared_ptr<BinaryTree> temp = MinimumValueNode(root->right_node);

			root->nodeObject->data = temp->nodeObject->data;

			root->right_node = DeleteNode(root->right_node, temp->nodeObject->data);
		}

		return root;
	}
	
	void BinaryTree::InOrder(std::shared_ptr<BinaryTree> root)
	{
		if (!root) { return; }
		InOrder(root->left_node);
		std::cout << root->nodeObject->data << std::endl;
		InOrder(root->right_node);
	}

	std::shared_ptr<BinaryTree> BinaryTree::MinimumValueNode(std::shared_ptr<BinaryTree> root)
	{
		while (root != nullptr && root->left_node != nullptr)
		{
			root = root->left_node;
		}
		return root;
	}



}