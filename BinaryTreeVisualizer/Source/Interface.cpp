#include "../Headers/Interface.hpp"

namespace Interface
{


	ImGUI::ImGUI()
		: InsertValue(0), DeleteValue(0), Root(nullptr) { }

	void ImGUI::NodeWindow(sf::RenderWindow& window)
	{
		ImGui::Begin("Insert/Delete/Search"); // window title

		// Add Nodes
		ImGui::InputInt("InsertValue", &InsertValue);
		if(ImGui::Button("Add Node"))
		{
			if (!Root) { Root = Root->InsertNode(Root, InsertValue); }
			else { Root->InsertNode(Root, InsertValue); }
			SFML::PreOrder(Root);
			while (SFML::Animate(window)) { }
		}
		// Delete Nodes
		ImGui::InputInt("DeleteValue", &DeleteValue);
		if (ImGui::Button("Delete Node"))
		{
			Root->DeleteNode(Root, DeleteValue);
			std::cout << "Deleted Node: " << DeleteValue << std::endl;
		}

		// Print To console Node Values in Order [Debugging]
		if (ImGui::Button("Order Tree"))
			Root->InOrder(Root);

		ImGui::End();
	}

	// ==================== SFML ======================

	// Static Vars
	sf::Font SFML::m_font;
	std::vector<std::shared_ptr<CircleText>> SFML::NodesArray;
	sf::Clock SFML::m_clock;
	float SFML::duration = float();
	int SFML::current_frame = 1;
	sf::Time SFML::m_time;
	float SFML::animate_time = 0.1f;
	std::stack<std::shared_ptr<Interface::CircleText>> SFML::AnimationStack;

	SFML::SFML() 
	{
		if (!m_font.loadFromFile("../../../../BinaryTreeVisualizer/Fonts/BodoniFLF-Bold.ttf"))
		{
			std::cout << "Error Loading Font" << std::endl;
		}
	}

	void SFML::PreOrder(std::shared_ptr<TreeType::BinaryTree> root)
	{
		// return if tree is null
		if (root == nullptr) { return; }
		
		// print nodes data value
		CreateNode(root, root->data, sf::Vector2f(100, 100), 20, sf::Color::Green);

		// Recur Left
		PreOrder(root->left_node);

		// Recur Right
		PreOrder(root->right_node);

	}

	void SFML::CreateNode(std::shared_ptr<TreeType::BinaryTree> root, int data, sf::Vector2f pos, int radius, sf::Color col)
	{
		// Create Objects [Circle, Text]
		std::shared_ptr<CircleText> circle_text = std::make_shared<CircleText>();
		std::shared_ptr<sf::CircleShape> Node = std::make_shared<sf::CircleShape>(radius, 100);

		// Initialize Circle Object
		Node->setPosition(pos);
		Node->setFillColor(col);
		Node->setOrigin(Node->getRadius() - 15, Node->getRadius() - 30);

		// Initlialize Text Object
		sf::Text text;
		text.setFont(m_font);
		text.setString(std::to_string(data));
		text.setPosition(Node->getPosition().x, Node->getPosition().y);
		text.setFillColor(sf::Color::Black);
		text.setScale(1.5, 1.5);

		// Set Struct Values
		circle_text->circle = Node;
		circle_text->text = text;
		
		// push into array
		NodesArray.push_back(circle_text);
		
		// Animation Stack
		AnimationStack.push(circle_text);
	}

	bool SFML::Animate(sf::RenderWindow& window)
	{
		m_time = m_clock.restart();
		duration += m_time.asSeconds();

		if (duration > animate_time)
		{
			duration = 0;
			
			if (current_frame < 9)
			{
				window.clear();
				std::cout << "Animating" << std::endl;
				std::shared_ptr<Interface::CircleText> tmp = AnimationStack.top();
				tmp->circle->move(sf::Vector2f(20, 20));
				tmp->text.move(sf::Vector2f(20, 20));
				window.draw(*tmp->circle);
				window.draw(tmp->text);
				window.display();
				
				current_frame += 1;
				return true;
			}
			else
			{
				std::cout << "Restarted" << std::endl;
				current_frame = 0;
				AnimationStack.pop();
				return false;
			}
		}
	}

	void SFML::DrawNodes(sf::RenderWindow& window, std::shared_ptr<TreeType::BinaryTree> root)
	{
		for (unsigned int i = 0; i < NodesArray.size(); i++)
		{
			window.draw(*NodesArray[i]->circle);
			window.draw(NodesArray[i]->text);
		}
	}
	


}