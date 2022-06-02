#include "../Headers/Interface.hpp"

namespace Interface
{

	ImGUI::ImGUI()
		: InsertValue(0), DeleteValue(0), Root(nullptr) { }

	void ImGUI::NodeWindow()
	{
		ImGui::Begin("Insert/Delete/Search"); // window title

		// Add Nodes
		ImGui::InputInt("InsertValue", &InsertValue);
		if(ImGui::Button("Add Node"))
		{
			if (!Root) 
			{ 
				Root = Root->InsertNode(Root, InsertValue);
			}
			else { Root->InsertNode(Root, InsertValue); }
			std::cout << "Added Node: " << InsertValue << std::endl;
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
		{
			Root->InOrder(Root);
		}

		ImGui::End();
	}

	// ==================== SFML ======================

	SFML::SFML() 
		: offset(100, 100)
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
		CreateNode(root, root->data, offset, 20, sf::Color::Green);
		offset += offset;

		PreOrder(root->left_node);

		PreOrder(root->right_node);

	}

	void SFML::CreateNode(std::shared_ptr<TreeType::BinaryTree> root, int data, sf::Vector2f pos, int radius, sf::Color col)
	{
		std::cout << "Node Created: " << data << std::endl;

		std::shared_ptr<CircleText> circle_text = std::make_shared<CircleText>();
		std::shared_ptr<sf::CircleShape> Node = std::make_shared<sf::CircleShape>(radius, 100);

		Node->setPosition(pos);
		Node->setFillColor(col);
		Node->setOrigin(Node->getRadius() - 15, Node->getRadius() - 30);

		sf::Text text;
		text.setFont(m_font);
		text.setString(std::to_string(data));
		text.setPosition(Node->getPosition().x, Node->getPosition().y);
		text.setFillColor(sf::Color::Black);
		text.setScale(1.5, 1.5);

		circle_text->circle = Node;
		circle_text->text = text;

		NodesArray.push_back(circle_text);
	}

	void SFML::DrawNodes(sf::RenderWindow& window, std::shared_ptr<TreeType::BinaryTree> root)
	{

		sf::CircleShape draw;

		ImGui::Begin("Draw Window");
		if (ImGui::Button("DrawTest"))
		{
			PreOrder(root);
			std::cout << "NodesArrSize: " << NodesArray.size() << std::endl;
		}
		ImGui::End();
		for (unsigned int i = 0; i < NodesArray.size(); i++)
		{
			window.draw(*NodesArray[i]->circle);
			window.draw(NodesArray[i]->text);
		}
	}
	


}