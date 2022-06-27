#include "../Headers/Node.hpp"

namespace Object
{
	Node::Node(int value)
		: connection(NULL),
	   	  data(value)
	{
		if (!font.loadFromFile("../../../../BinaryTreeVisualizer/Fonts/BodoniFLF-Bold.ttf"))
		{
			std::cout << "Error Loading Font" << std::endl;
		}
	};

	int Node::DistanceToChildNode(sf::Vector2f parent_pos)
	{
		return std::sqrt(std::pow(position.x - parent_pos.x, 2) + std::pow(position.y - parent_pos.y, 2));
	}

	float Node::AngleToChildNode(sf::Vector2f parent_pos)
	{
		// atan2(y2 - y1, x2 - x1) * 180 / PI
		return std::atan2(position.y - parent_pos.y, position.x - parent_pos.x) * 180 / PI;
	}

	void Node::InitCircleObject(std::shared_ptr<sf::CircleShape>& node)
	{
		node->setFillColor(sf::Color::Green);
		node->setPosition(position);

		// Text Object
		text.setFont(font);
		text.setString(std::to_string(data));
		sf::FloatRect bounds(text.getLocalBounds());
		text.setOrigin((bounds.width - node->getRadius()) / 2 + bounds.left, (bounds.height - node->getRadius()) / 2 +  bounds.top);
		text.setPosition(node->getPosition().x + (node->getRadius() /2) ,node->getPosition().y + (node->getRadius() / 2));
		text.setFillColor(sf::Color::Black);
	}

	void Node::InitConnectionLine(std::shared_ptr<Node>& parent)
	{
		if (!parent) { return; }

		connection = std::make_shared<sf::RectangleShape>(sf::Vector2f(DistanceToChildNode(parent->position), 5));
		connection->setPosition(parent->position.x + node->getRadius(), parent->position.y + node->getRadius());
		connection->setFillColor(sf::Color::Black);
		connection->rotate(AngleToChildNode(parent->position));
	}

	void Node::CreateObject(std::shared_ptr<Node> root, std::shared_ptr<Node> parent, int dir)
	{
		// Init CircleShape
		node = std::make_shared<sf::CircleShape>(SettingsPanel::nRadius);

		// parent is null if its the Root node
		if (!parent && dir == 0)
		{
			position = sf::Vector2f(SettingsPanel::sWidth / 2, 20);
		}
		else
		{
			// Left
			if (dir == 1)
				position = parent->position + SettingsPanel::LEFT_OFFSET;
			// Right
			else if(dir == 2)
				position = parent->position + SettingsPanel::RIGHT_OFFSET;
		}

		// CircleShape Node
		InitCircleObject(node);

		// Connection Line [RectangleShape]
		InitConnectionLine(parent);
	}

	void Node::UpdatePosition(std::shared_ptr<Node>& root, std::shared_ptr<Node>& parent, int dir)
	{
		if (dir == 1) // left
			position = parent->position + SettingsPanel::LEFT_OFFSET;
		else if(dir == 2) // right
			position = parent->position + SettingsPanel::RIGHT_OFFSET;

		node->setPosition(position);
		text.setPosition(node->getPosition().x + (node->getRadius() / 2), node->getPosition().y + (node->getRadius() / 2));
		connection->setPosition(parent->position.x + node->getRadius(), parent->position.y + node->getRadius());
		connection->setRotation(AngleToChildNode(parent->position));
		
	}
}