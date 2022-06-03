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
		SFML(sf::RenderWindow& window);
		// Recurse the Binary tree in PreOrder
		static void PreOrder(std::shared_ptr<TreeType::BinaryTree> root);
		static void CreateNode(std::shared_ptr<TreeType::BinaryTree> root, sf::Vector2f pos, int radius);
		static void DrawNodes(std::shared_ptr<TreeType::BinaryTree> root);
		static bool Animate();

	private:
		static std::vector<std::shared_ptr<CircleText>> NodesArray;
		static std::stack<std::shared_ptr<Interface::CircleText>> AnimationStack;
		static sf::Font m_font;
		static sf::Clock m_clock;
		static sf::Time m_time;
		static float duration;
		static int current_frame;
		static float animate_time;
		static sf::RenderWindow* ref_window;
	};
}