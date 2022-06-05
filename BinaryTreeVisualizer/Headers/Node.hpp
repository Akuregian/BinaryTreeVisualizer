#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Headers/Settings.hpp"

namespace Object
{
	class Node
	{
	public:
		Node(int value);
		void CreateNode(sf::Vector2f pos);

		std::shared_ptr<sf::CircleShape> node_object;
		sf::Text text;
		sf::Font font;
		sf::Color color;
		sf::Vector2f position;
		int data;
	};

}
