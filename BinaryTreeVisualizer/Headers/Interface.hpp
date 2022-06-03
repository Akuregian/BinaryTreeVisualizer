#include <imgui.h>
#include <SFML/Graphics.hpp>
#include <stack>
#include "../Headers/BinarySearchTree.hpp"

namespace Interface
{
	struct CircleText
	{
		std::shared_ptr<sf::CircleShape> circle;
		sf::Text text;
	};

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
		SFML();
		// Recurse the Binary tree in PreOrder
		static void PreOrder(std::shared_ptr<TreeType::BinaryTree> root);
		static void CreateNode(std::shared_ptr<TreeType::BinaryTree> root, int data, sf::Vector2f pos, int radius, sf::Color col);
		static void DrawNodes(sf::RenderWindow& window, std::shared_ptr<TreeType::BinaryTree> root);
		static bool Animate(sf::RenderWindow& window);

	private:
		static std::vector<std::shared_ptr<CircleText>> NodesArray;
		static std::stack<std::shared_ptr<Interface::CircleText>> AnimationStack;
		static sf::Font m_font;
		static sf::Clock m_clock;
		static sf::Time m_time;
		static float duration;
		static int current_frame;
		static float animate_time;
	};
}