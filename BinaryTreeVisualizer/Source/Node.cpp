#include "../Headers/Node.hpp"

namespace Object
{
	Node::Node(int value)
		: node_object(std::make_shared<sf::CircleShape>()),
		  data(value)
	{
		if (!font.loadFromFile("../../../../BinaryTreeVisualizer/Fonts/BodoniFLF-Bold.ttf"))
		{
			std::cout << "Error Loading Font" << std::endl;
		}
	};

	void Node::CreateNode(sf::Vector2f pos)
	{
		position = pos;
		node_object->setFillColor(sf::Color::Green);
		node_object->setPosition(position);
		node_object->setRadius(SettingsPanel::nRadius);

		text.setFont(font);
		text.setString(std::to_string(data));
		text.setPosition((node_object->getPosition().x + node_object->getRadius()) / 2, (node_object->getPosition().y + node_object->getRadius())/ 2);
		text.setScale(1.5, 1.5);
		text.setFillColor(sf::Color::Black);
	}

}