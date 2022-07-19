#include "../Headers/BinarySearchTree.hpp"

namespace TreeType
{
	static TreeType::RootDir direction;

	BinaryTree::BinaryTree(int data)
		: left_node(nullptr),
		  right_node(nullptr),
		  branch(Branch_Side::ROOT_BRANCH),
		  dir(RootDir::ROOT),
		  nodeObject(std::make_shared<Object::Node>(data)),
		  level(0),
		  parent(nullptr)
	{

	}

	BinaryTree::~BinaryTree() 
	{
		nodeObject.reset();
		right_node.reset();
		left_node.reset();
		parent.reset();
	}


	void BinaryTree::PrintNodeDetails(std::shared_ptr<BinaryTree> root)
	{

		if (!root) { return; }

		PrintNodeDetails(root->left_node);

		std::cout << "Node Inserted { Data: " << root->nodeObject->data
		<< " , Dir: ";
		std::string dir; 
		switch (root->dir)
		{
			case RootDir::ROOT:  dir = "ROOT";   break;
			case RootDir::LEFT:  dir = "LEFT";   break;
			case RootDir::RIGHT: dir = "RIGHT";  break;
			case RootDir::NONE:  dir = "NONE";   break;
		}
		std::string branch;
		switch (root->branch)
		{
			case Branch_Side::ROOT_BRANCH:  branch = "ROOT_BRANCH";   break;
			case Branch_Side::LEFT_BRANCH:  branch = "LEFT_BRANCH";   break;
			case Branch_Side::RIGHT_BRANCH: branch = "RIGHT_BRANCH";  break;
		}
		std::cout << dir << ", Branch: " << branch <<  " , Level: " << root->level
		<< " , Positions [" << root->nodeObject->position.x << ", " << root->nodeObject->position.y << "]\n";

		PrintNodeDetails(root->right_node);
	}

	// Post Order Traversal
//	void BinaryTree::CheckLevelNodeDistances(std::shared_ptr<BinaryTree> root)
//	{
//		if (!root) { return; }
//
//		// Empty Queue	
//		std::queue<std::shared_ptr<BinaryTree>> Q;
//		
//		// Push Root
//		Q.push(root);
//
//		std::shared_ptr<BinaryTree> next_node;
//		std::shared_ptr<BinaryTree> node;
//
//		// While Q is NOT empty
//		while (!Q.empty())
//		{
//			if (Q.size() >= 2)
//			{
//				next_node = Q.front();
//				std::cout << "Next Node-> " << next_node->nodeObject->data << std::endl;
//				int distance = node->nodeObject->DistanceToChildNode(next_node->nodeObject->position);
//				std::cout << "Distance To Next Node: " << distance << std::endl;
//			}
//
//			// Create a Temp Root to hosue the first Queue
//			node = Q.front();
//
//			std::cout << "Queue Size {" << Q.size() << "} NodeData: " << node->nodeObject->data << std::endl;
//
//			// Pop Off Queue
//			Q.pop();
//
//
//			if (node->left_node)
//			{
//				Q.push(node->left_node);
//			}
//
//			if (node->right_node)
//			{
//				Q.push(node->right_node);
//			}
//		}
//	}

	// In Post Traversal
	void BinaryTree::CheckForOverlappingNodes(std::shared_ptr<BinaryTree> check_node, std::shared_ptr<BinaryTree> reference_root)
	{
		// Reference node is the node thats being overlapped
		// Check_node is the node thats just been inserterd

		if (!reference_root) { return; }

		CheckForOverlappingNodes(check_node, reference_root->left_node);

		CheckForOverlappingNodes(check_node, reference_root->right_node);

		if (check_node->nodeObject->position == reference_root->nodeObject->position && check_node != reference_root)
		{
			std::cout << "Found Overlapping Node-> Ref_Node:" << reference_root->nodeObject->data << " , Check_node: " << check_node->nodeObject->data << "\n ";

			std::shared_ptr<BinaryTree> temp = reference_root;
			std::shared_ptr<BinaryTree> prev = nullptr;

			while (temp->dir != RootDir::ROOT)
			{
				prev = temp;
				temp = temp->parent;
			}

			if (prev->dir == RootDir::LEFT)
			{
				temp->ShiftLeftTree(temp);
				temp->ShiftConnectionLinesLeft(temp);
			}
			else
			{

				temp->ShiftRightTree(temp);
				temp->ShiftConnectionLinesRight(temp);
			}
		}
	}

	std::shared_ptr<BinaryTree> BinaryTree::InsertNode(std::shared_ptr<BinaryTree> root, std::shared_ptr<BinaryTree> ref_root, int value, int ref_level)
	{
		//Inserts a 'blank' node and will be changed if its not the ROOT node
		if (!root) 
		{ 
			std::shared_ptr<BinaryTree> temp = std::make_shared<BinaryTree>(value); 
			temp->nodeObject->CreateObject(temp->nodeObject, NULL, RootDir::ROOT, 0);
			return temp;
		}
		
		// Level of node
		ref_level++;

		// If Value > root.Value : Insert Right
		if (value > root->nodeObject->data)
		{
			root->right_node = InsertNode(root->right_node, ref_root, value, ref_level);
			root->right_node->dir = RootDir::RIGHT;
			root->right_node->level = ref_level--;
			root->right_node->parent = root;
			root->right_node->nodeObject->CreateObject(root->right_node->nodeObject, root->right_node->parent->nodeObject, root->right_node->dir, root->right_node->level);
		//	CheckForOverlappingNodes(root->right_node, ref_root);
		}

		// If Value < root.Value : Insert Left
		if (value < root->nodeObject->data) 
		{ 
			root->left_node = InsertNode(root->left_node, ref_root, value, ref_level);
			root->left_node->dir = RootDir::LEFT; 
			root->left_node->level = ref_level--;
			root->left_node->parent = root;
			root->left_node->nodeObject->CreateObject(root->left_node->nodeObject, root->left_node->parent->nodeObject, root->left_node->dir, root->left_node->level);
		//	CheckForOverlappingNodes(root->left_node, ref_root);
		}
		return root;
	}

	void BinaryTree::ShiftLeftTree(std::shared_ptr<BinaryTree> root)
	{
		if (!root) { return; }

		ShiftLeftTree(root->left_node);

		if (root->dir == RootDir::ROOT) { return; }

		// Shift Right Side Nodes
		root->nodeObject->UpdatePosition(SettingsPanel::LEFT_SHIFT);

		ShiftLeftTree(root->right_node);
	}
	
	void BinaryTree::ShiftRightTree(std::shared_ptr<BinaryTree> root)
	{
		if (!root) { return; }

		ShiftRightTree(root->right_node);

		if (root->dir == RootDir::ROOT) { return; }

		// Shift Right Side Nodes
		root->nodeObject->UpdatePosition(SettingsPanel::RIGHT_SHIFT);

		ShiftRightTree(root->left_node);
	}

	void BinaryTree::ShiftConnectionLinesRight(std::shared_ptr<BinaryTree> root)
	{
		if (!root) { return; }

		ShiftConnectionLinesRight(root->right_node);

		if (root->dir == RootDir::ROOT) { return; }

		// Shift Right Side Nodes
		root->nodeObject->UpdateConnectionLines(root->parent->nodeObject);

		ShiftConnectionLinesRight(root->left_node);
	}

	void BinaryTree::ShiftConnectionLinesLeft(std::shared_ptr<BinaryTree> root)
	{
		if (!root) { return; }

		ShiftConnectionLinesLeft(root->left_node);

		if (root->dir == RootDir::ROOT) { return; }

		// Shift Right Side Nodes
		root->nodeObject->UpdateConnectionLines(root->parent->nodeObject);

		ShiftConnectionLinesLeft(root->right_node);
	}
	
	// In Post Order Traversal
	void BinaryTree::UpdatePositions(std::shared_ptr<BinaryTree> root)
	{
		if (!root) { return; }

		if (!root->parent)
			root->nodeObject->UpdateRelativePositions(root->nodeObject, NULL, root->dir);
		else
			root->nodeObject->UpdateRelativePositions(root->nodeObject, root->parent->nodeObject, root->dir);
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
			return nullptr;
		}
		else if (!root->left_node)
		{
			std::shared_ptr<BinaryTree> temp = root->right_node;
			temp->parent = root->parent;
			temp->dir = root->dir;

			// Update All Positions Underneath this node
			UpdatePositions(temp);

			root.reset();
			return temp;
		}
		else if (!root->right_node)
		{
			std::shared_ptr<BinaryTree> temp = root->left_node;
			temp->parent = root->parent;
			temp->dir = root->dir;

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
				if (parent->dir == RootDir::ROOT)
				{
					successor->dir = RootDir::ROOT;
				}
			}

			root->nodeObject = successor->nodeObject;
			UpdatePositions(root);
			successor.reset();
			return root;
		}
	}
}