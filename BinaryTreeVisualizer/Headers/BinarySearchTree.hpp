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

		std::shared_ptr<BinaryTree> InsertNode(std::shared_ptr<BinaryTree> root, int value);
		void InOrder(std::shared_ptr<BinaryTree> root);

	private:
		std::shared_ptr<BinaryTree> left_node;
		std::shared_ptr<BinaryTree> right_node;
		int data;
	};
}