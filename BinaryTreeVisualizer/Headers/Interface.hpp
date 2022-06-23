#pragma once
#include <imgui.h>
#include <stack>
#include "../Headers/BinarySearchTree.hpp"

namespace Interface
{
	class ImGUI
	{
	public:
		ImGUI();
		void NodeWindow(sf::RenderWindow& window);

		// Binary Tree
		std::shared_ptr<TreeType::BinaryTree> Root;

		// Variables
		int InsertValue;
		int DeleteValue;
	};

	class SFML
	{
	public:
		SFML(sf::RenderWindow& window);
		// Recurse the Binary tree in PreOrder
		static void DrawBinaryTree(std::shared_ptr<TreeType::BinaryTree> root);
		static void DrawAllConnections(std::shared_ptr<TreeType::BinaryTree> root);

	private:
		// Annimation
		static sf::Clock m_clock;
		static sf::Time m_time;
		static float duration;
		static int current_frame;
		static float animate_time;

		// Reference window
		static sf::RenderWindow* ref_window;
	};
}
