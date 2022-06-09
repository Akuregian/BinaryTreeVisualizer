#include "../Headers/Node.hpp"

namespace Object
{
	Node::Node(int value)
		: node(std::make_shared<sf::CircleShape>()),
		  connection(NULL),
	   	  data(value)
	{
		if (!font.loadFromFile("../../../../BinaryTreeVisualizer/Fonts/BodoniFLF-Bold.ttf"))
		{
			std::cout << "Error Loading Font" << std::endl;
		}
	};

	void Node::CreateNode(sf::Vector2f pos, sf::Vector2f parent_pos, int dir, int level)
	{
		// CircleShape Node
		position = pos;
		node->setFillColor(sf::Color::Green);
		node->setPosition(position);
		node->setRadius(SettingsPanel::nRadius);

		// Text Object
		text.setFont(font);
		text.setString(std::to_string(data));
		sf::FloatRect bounds(text.getLocalBounds());
		text.setOrigin((bounds.width - node->getRadius()) / 2 + bounds.left, (bounds.height - node->getRadius()) / 2 +  bounds.top);
		text.setPosition(node->getPosition().x + (node->getRadius() /2) ,node->getPosition().y + (node->getRadius() / 2));
		text.setFillColor(sf::Color::Black);
		
		if (dir == 0)
			return;

		int distance_to_other_node = std::sqrt(std::pow(pos.x - parent_pos.x, 2) + std::pow(pos.y - parent_pos.y, 2));
		connection = std::make_shared<sf::RectangleShape>(sf::Vector2f(distance_to_other_node, 5));
		connection->setPosition(parent_pos.x + node->getRadius(), parent_pos.y + node->getRadius());
		connection->setFillColor(sf::Color::Black);
		if (dir == 2) // right_node
			connection->rotate(45);
		else // left_node
			connection->rotate(135);
	}
}