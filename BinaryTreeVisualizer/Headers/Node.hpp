#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Headers/Settings.hpp"
#include "../Utility/Utility.hpp"

constexpr auto PI = 3.14159265359;

namespace Object
{
	class Node
	{
	public:
		Node(int value);
		void CreateObject(std::shared_ptr<Node> root, std::shared_ptr<Node> parent, int dir);
		void InitCircleObject(std::shared_ptr<sf::CircleShape>& node);
		void InitConnectionLine(std::shared_ptr<Node>& parent, int& dir);
		int DistanceToChildNode(sf::Vector2f parent_pos);
		float AngleToChildNode(sf::Vector2f parent_pos);

		std::shared_ptr<sf::CircleShape> node;
		sf::Text text;
		sf::Font font;
		sf::Color color;
		sf::Vector2f position;
		std::shared_ptr<sf::RectangleShape> connection;
		int data;
	};
}
