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
			std::cout << "Added Node" << std::endl;
			if (!Root) { Root = Root->InsertNode(Root, InsertValue); }
			else { Root->InsertNode(Root, InsertValue); }
			SFML::WalkTree(Root, NULL);

			//while (SFML::Animate(window)) { }
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

	// Static Variables
	sf::Font SFML::m_font;
	sf::Clock SFML::m_clock;
	float SFML::duration = float();
	int SFML::current_frame = 1;
	sf::Time SFML::m_time;
	float SFML::animate_time = 0.1f;
	sf::RenderWindow* SFML::ref_window;
	sf::Vector2f SFML::LEFT_OFFSET(-SettingsPanel::offset, SettingsPanel::offset);
	sf::Vector2f SFML::RIGHT_OFFSET(SettingsPanel::offset, SettingsPanel::offset);

	SFML::SFML(sf::RenderWindow& window) { ref_window = &window; }

	void SFML::WalkTree(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> parent_node)
	{
		// Recurse Left
		if (root->left_node != nullptr)
			WalkTree(root->left_node, root);

		// Create Objects 
		CreateChildrenNodes(root, parent_node);

		// Recurse Right
		if (root->right_node != nullptr)
			WalkTree(root->right_node, root);
	}

	void SFML::CreateChildrenNodes(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> parent_node)
	{

		if (root->dir == TreeType::ROOT && !parent_node)
		{
			std::cout << "Creating Root Node" << std::endl;
			root->nodeObject->CreateNode(sf::Vector2f(ref_window->getPosition().x, 20), sf::Vector2f(ref_window->getPosition().x, 20), root->dir);
			return;
		}

		if (root->dir == TreeType::LEFT)
		{
			std::cout << "Creating Left Node" << std::endl;
			root->nodeObject->CreateNode(parent_node->nodeObject->position + LEFT_OFFSET, parent_node->nodeObject->position, root->dir);
		}

		if (root->dir == TreeType::RIGHT)
		{
			std::cout << "Creating Right Node" << std::endl;
			root->nodeObject->CreateNode(parent_node->nodeObject->position + RIGHT_OFFSET, parent_node->nodeObject->position, root->dir);
		}

	}

	bool SFML::Animate()
	{
//		m_time = m_clock.restart();
//		duration += m_time.asSeconds();
//
//		if (duration > animate_time)
//		{
//			duration = 0;
//			
//			if (current_frame < 9)
//			{
//				ref_window->clear();
//				std::cout << "Animating" << std::endl;
//				std::shared_ptr<Interface::CircleText> tmp = AnimationStack.top();
//				tmp->circle->move(sf::Vector2f(20, 20));
//				tmp->text.move(sf::Vector2f(20, 20));
//				ref_window->draw(*tmp->circle);
//				ref_window->draw(tmp->text);
//				ref_window->display();
//				
//				current_frame += 1;
//				return true;
//			}
//			else
//			{
//				std::cout << "Restarted" << std::endl;
//				current_frame = 0;
//				AnimationStack.pop();
//				return false;
//			}
//		}
//
		return false;
	}

	void SFML::DrawNodes(std::shared_ptr<TreeType::BinaryTree> root)
	{
		if (!root) { return; }

		ref_window->draw(*root->nodeObject->node_object);
		ref_window->draw(root->nodeObject->text);

		DrawNodes(root->right_node);
		DrawNodes(root->left_node);
	}
	void SFML::DrawLines(std::shared_ptr<TreeType::BinaryTree> root) 
	{
		if (!root) { return; }

		if(root->nodeObject->connection)
			ref_window->draw(*root->nodeObject->connection);

		DrawLines(root->right_node);
		DrawLines(root->left_node);
	}

	void SFML::Display(std::shared_ptr<TreeType::BinaryTree> root)
	{
		DrawLines(root);
		DrawNodes(root);
	}
	
}