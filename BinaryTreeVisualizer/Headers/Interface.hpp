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
		static void WalkTree(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> parent_node);
		static void CreateChildrenNodes(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> parent_node);
		static void DrawNodes(std::shared_ptr<TreeType::BinaryTree> root);
		static void DrawLines(std::shared_ptr<TreeType::BinaryTree> root);
		static void Display(std::shared_ptr<TreeType::BinaryTree> root);
		static bool Animate();
		static bool CheckOverlappingNodes(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> check_node);

	private:
		static sf::Font m_font;
		static sf::Clock m_clock;
		static sf::Time m_time;
		static float duration;
		static int current_frame;
		static float animate_time;
		static sf::RenderWindow* ref_window;
		static sf::Vector2f LEFT_OFFSET;
		static sf::Vector2f RIGHT_OFFSET;
		
		// Test/Debug
		static std::shared_ptr<TreeType::BinaryTree> ref_root;
	};
}