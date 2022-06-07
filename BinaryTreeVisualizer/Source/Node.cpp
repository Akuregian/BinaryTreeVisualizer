#include "../Headers/Node.hpp"

namespace Object
{
	Node::Node(int value)
		: node_object(std::make_shared<sf::CircleShape>()),
		  connection(NULL),
	   	  data(value)
	{
		if (!font.loadFromFile("../../../../BinaryTreeVisualizer/Fonts/BodoniFLF-Bold.ttf"))
		{
			std::cout << "Error Loading Font" << std::endl;
		}
	};

	void Node::CreateNode(sf::Vector2f pos, sf::Vector2f parent_pos, int dir)
	{
		// CircleShape Node
		position = pos;
		node_object->setFillColor(sf::Color::Green);
		node_object->setPosition(position);
		node_object->setRadius(SettingsPanel::nRadius);

		// Text Object
		text.setFont(font);
		text.setString(std::to_string(data));
		sf::FloatRect bounds(text.getLocalBounds());
		text.setOrigin((bounds.width - node_object->getRadius()) / 2 + bounds.left, (bounds.height - node_object->getRadius()) / 2 +  bounds.top);
		text.setPosition(node_object->getPosition().x + (node_object->getRadius() /2) ,node_object->getPosition().y + (node_object->getRadius() / 2));
		text.setFillColor(sf::Color::Black);
		
		if (parent_pos == pos)
			return;

		connection = std::make_shared<sf::RectangleShape>(sf::Vector2f(50, 5));
		connection->setPosition(parent_pos.x + node_object->getRadius(), parent_pos.y + node_object->getRadius());
		connection->setFillColor(sf::Color::Black);
		if (dir == 2)
			connection->rotate(45);
		else
			connection->rotate(135);
	}
}