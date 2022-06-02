#pragma once
#include <memory>
#include <iostream>

namespace TreeType
{
	class BinaryTree
	{
	public:
		BinaryTree();
		BinaryTree(int data);
		~BinaryTree();
		
		// Tree Operations
		std::shared_ptr<BinaryTree> InsertNode(std::shared_ptr<BinaryTree> root, int value);
		std::shared_ptr<BinaryTree> DeleteNode(std::shared_ptr<BinaryTree> root, int key);
		std::shared_ptr<BinaryTree> MinimumValueNode(std::shared_ptr<BinaryTree> root);

		void InOrder(std::shared_ptr<BinaryTree> root);

		std::shared_ptr<BinaryTree> left_node;
		std::shared_ptr<BinaryTree> right_node;
		int data;
	};
}