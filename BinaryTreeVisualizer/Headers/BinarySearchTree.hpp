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
		std::shared_ptr<BinaryTree> MinimumValueNode(std::shared_ptr<BinaryTree> root);

		void InOrder(std::shared_ptr<BinaryTree> root);

		std::shared_ptr<BinaryTree> left_node;
		std::shared_ptr<BinaryTree> right_node;
		std::shared_ptr<Object::Node> nodeObject;
		RootDir dir;
		int level;
	};
}
