#pragma once
#include <memory>
#include "../Headers/Node.hpp"
#include <queue>

namespace TreeType
{
	enum RootDir
	{
		ROOT, // 0
		LEFT, // 1
		RIGHT, // 2
		NONE
	};

	enum Branch_Side
	{
		ROOT_BRANCH,
		LEFT_BRANCH,
		RIGHT_BRANCH
	};

	class BinaryTree
	{
	public:
		BinaryTree(int data);
		~BinaryTree();
		
		// Tree Operations
		std::shared_ptr<BinaryTree> InsertNode(std::shared_ptr<BinaryTree> root, std::shared_ptr<BinaryTree> ref_root, int value, int ref_level);
		std::shared_ptr<BinaryTree> DeleteNode(std::shared_ptr<BinaryTree> root, int key);
		void UpdatePositions(std::shared_ptr<BinaryTree> root);

		// Drawing/Updating Utility FunctionsA
		void CheckLevelNodeDistances(std::shared_ptr<BinaryTree> root);

		// Might Not Need This Overlapping Function...
		void CheckForOverlappingNodes(std::shared_ptr<BinaryTree> check_node, std::shared_ptr<BinaryTree> reference_root);
		void PrintNodeDetails(std::shared_ptr<BinaryTree> root);

		// Might Not Need These Functions.....
		void ShiftLeftTree(std::shared_ptr<BinaryTree> root);
		void ShiftRightTree(std::shared_ptr<BinaryTree> root);
		void ShiftConnectionLinesRight(std::shared_ptr<BinaryTree> root);
		void ShiftConnectionLinesLeft(std::shared_ptr<BinaryTree> root);

		// Root has a Parent, Left & Right Node and an Object to Draw
		std::shared_ptr<BinaryTree> parent;
		std::shared_ptr<BinaryTree> left_node;
		std::shared_ptr<BinaryTree> right_node;
		std::shared_ptr<Object::Node> nodeObject;
		RootDir dir;
		Branch_Side branch;
		int level;
	};
}
