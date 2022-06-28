#pragma once
#include <memory>
#include "../Headers/Node.hpp"

namespace TreeType
{
	enum RootDir
	{
		ROOT, // 0
		LEFT, // 1
		RIGHT, // 2
		NONE
	};

	class BinaryTree
	{
	public:
		BinaryTree(int data);
		~BinaryTree();
		
		// Tree Operations
		std::shared_ptr<BinaryTree> InsertNode(std::shared_ptr<BinaryTree> root, int value, int ref_level);
		std::shared_ptr<BinaryTree> DeleteNode(std::shared_ptr<BinaryTree> root, int key);
		void UpdatePositions(std::shared_ptr<BinaryTree> root);

		// Root has a Parent, Left & Right Node and an Object to Draw
		std::shared_ptr<BinaryTree> parent;
		std::shared_ptr<BinaryTree> left_node;
		std::shared_ptr<BinaryTree> right_node;
		std::shared_ptr<Object::Node> nodeObject;
		RootDir dir;
		int level;
	};
}
