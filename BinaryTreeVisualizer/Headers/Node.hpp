#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Headers/Settings.hpp"

namespace Object
{
	class Node
	{
	public:
		Node(int value);
		void CreateNode(sf::Vector2f pos, sf::Vector2f parent_pos, int dir); // dir 1 == right dir 2 == left

		std::shared_ptr<sf::CircleShape> node_object;
		sf::Text text;
		sf::Font font;
		sf::Color color;
		sf::Vector2f position;
		std::shared_ptr<sf::RectangleShape> connection;
		int data;
	};

}
