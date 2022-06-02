#include <imgui.h>
#include <SFML/Graphics.hpp>
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
			void NodeWindow();

			int InsertValue;
			int DeleteValue;

			// Binary Tree
			std::shared_ptr<TreeType::BinaryTree> Root;
	};

	class SFML : public ImGUI
	{
	public:
		SFML();
		// Recurse the Binary tree in PreOrder
		void PreOrder(std::shared_ptr<TreeType::BinaryTree> root);
		void CreateNode(std::shared_ptr<TreeType::BinaryTree> root, int data, sf::Vector2f pos, int radius, sf::Color col);
		void DrawNodes(sf::RenderWindow& window, std::shared_ptr<TreeType::BinaryTree> root);

	private:
		std::vector<std::shared_ptr<CircleText>> NodesArray;
		sf::Font m_font;

		// Test
		sf::Vector2f offset;
	};
}