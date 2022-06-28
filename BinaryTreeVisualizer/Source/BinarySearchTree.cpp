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

	BinaryTree::~BinaryTree() 
	{

	}

	std::shared_ptr<BinaryTree> BinaryTree::InsertNode(std::shared_ptr<BinaryTree> root, int value, int ref_level)
	{
		//Insert into First node if Root is null
		if (!root) 
		{ 
			std::shared_ptr<BinaryTree> temp = std::make_shared<BinaryTree>(value); 
			temp->nodeObject->CreateObject(temp->nodeObject, NULL, RootDir::ROOT);
			return temp;
		}
		
		// Level of node
		ref_level++;

		// If Value > root.Value : Insert Right
		if (value > root->nodeObject->data) 
		{ 
			root->right_node = InsertNode(root->right_node, value, ref_level); 
			root->right_node->dir = RootDir::RIGHT; 
			root->right_node->branch_side = Branch::RIGHT_BRANCH;
			root->right_node->level = ref_level--;
			root->right_node->parent = root;
			root->right_node->nodeObject->CreateObject(root->right_node->nodeObject, root->right_node->parent->nodeObject, RootDir::RIGHT);
		}

		// If Value < root.Value : Insert Left
		if (value < root->nodeObject->data) 
		{ 
			root->left_node = InsertNode(root->left_node, value, ref_level);
			root->left_node->dir = RootDir::LEFT; 
			root->left_node->branch_side = Branch::LEFT_BRANCH;
			root->left_node->level = ref_level--;
			root->left_node->parent = root;
			root->left_node->nodeObject->CreateObject(root->left_node->nodeObject, root->left_node->parent->nodeObject, RootDir::LEFT);
		}

		return root;
	}


	// In Post Order Traversal
	void BinaryTree::UpdatePositions(std::shared_ptr<BinaryTree> root)
	{
		if (!root) { return; }

		root->nodeObject->UpdatePosition(root->nodeObject, root->parent->nodeObject, root->dir);
		UpdatePositions(root->left_node);
		UpdatePositions(root->right_node);

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

		// At this point: Node Has Be found

		// If One Child is Empty
		if (!root->left_node && !root->right_node)
		{
			root.reset();
			return NULL;
		}
		else if (!root->left_node)
		{
			std::shared_ptr<BinaryTree> temp = root->right_node;
			// Update All Positions Underneath this node
			temp->parent = root->parent;
			UpdatePositions(temp);
			root.reset();
			return temp;
		}
		else if (!root->right_node)
		{
			std::shared_ptr<BinaryTree> temp = root->left_node;
			temp->parent = root->parent;
			// Update All Positions Underneath this node
			UpdatePositions(temp);
			root.reset();
			return temp;
		}
		else
		{
			// Find Successor
			std::shared_ptr<TreeType::BinaryTree> parent = root;
			std::shared_ptr<TreeType::BinaryTree> successor = root->right_node;
			
			while(successor->left_node)
			{
				parent = successor;
				successor = successor->left_node;
			}

			if (parent != root)
			{
				parent->left_node = successor->right_node; //null
				if (parent->left_node)
				{
					parent->left_node->parent = parent;
					parent->left_node->dir = TreeType::RootDir::LEFT;
				}
			}
			else
			{
				parent->right_node = successor->right_node;
			}

			root->nodeObject = successor->nodeObject;
			UpdatePositions(root);
			successor.reset();
			return root;
		}
	}
}