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
		if (ImGui::Button("Add Node"))
		{
			Utility::Timer Timer; // Used to just gauge optimization
			int ref_level = 0;
			std::cout << "Added Node" << std::endl;
			if (!Root) { Root = Root->InsertNode(Root, InsertValue, ref_level); }
			else { Root->InsertNode(Root, InsertValue, ref_level); }
			SFML::WalkTree(Root, NULL);
			//while (SFML::Animate(window)) { }
		}
		// Delete Nodes
		ImGui::InputInt("DeleteValue", &DeleteValue);
		if (ImGui::Button("Delete Node"))
		{
			Root->DeleteNode(Root, DeleteValue);
			std::cout << "Deleted Node: " << DeleteValue << std::endl;
			SFML::WalkTree(Root, NULL);
		}

		// Print To console Node Values in Order [Debugging]
		if (ImGui::Button("Order Tree"))
			SFML::WalkTree(Root, NULL);
			//Root->InOrder(Root);

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
	std::shared_ptr<TreeType::BinaryTree> SFML::ref_root;

	SFML::SFML(sf::RenderWindow& window) { ref_window = &window; }

	void SFML::WalkTree(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> parent_node)
	{
		// return if root == nullptr
		if (!root) { return; }

		// Create Objects 
		CreateChildrenNodes(root, parent_node);

		// Recurse Left
		if (root->left_node)
			WalkTree(root->left_node, root);

		// Recurse Right
		if (root->right_node)
			WalkTree(root->right_node, root);
	}

	void SFML::CreateChildrenNodes(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> parent_node)
	{
		// if root, set position to top-center screen
		if (root->dir == TreeType::ROOT && !parent_node)
		{
			ref_root = root;
			root->nodeObject->CreateNode(sf::Vector2f(ref_window->getPosition().x, 20), sf::Vector2f(ref_window->getPosition().x, 20), root->dir, 1);
			std::cout << "Creating Root(" << root->nodeObject->data << ") Node @ Level " <<root->level << " With Pos: (" << root->nodeObject->position.x << "," <<root->nodeObject->position.y << ")" << std::endl;
			return;
		}
		// if left_node off-set from parent node: LEFT
		if (root->dir == TreeType::LEFT && root->nodeObject)
		{
			root->nodeObject->CreateNode(parent_node->nodeObject->position + LEFT_OFFSET, parent_node->nodeObject->position, root->dir, root->level);
			CheckOverlappingNodes(ref_root, root);
			std::cout << "Creating Root(" << root->nodeObject->data << ") Node @ Level " <<root->level << " With Pos: (" << root->nodeObject->position.x << "," <<root->nodeObject->position.y << ")" << std::endl;
		}

		// if right_node off-set from parent node: RIGHT
		if (root->dir == TreeType::RIGHT && root->nodeObject)
		{
			root->nodeObject->CreateNode(parent_node->nodeObject->position + RIGHT_OFFSET, parent_node->nodeObject->position, root->dir, root->level);
			CheckOverlappingNodes(ref_root, root);
			std::cout << "Creating Root(" << root->nodeObject->data << ") Node @ Level " <<root->level << " With Pos: (" << root->nodeObject->position.x << "," <<root->nodeObject->position.y << ")" << std::endl;
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

	bool SFML::CheckOverlappingNodes(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> check_node)
	{
		if (!root) { return false; }

		if (root->nodeObject->position == check_node->nodeObject->position && root != check_node )
		{
			if (root->dir == TreeType::RootDir::LEFT)
			{
				ref_root->left_node->nodeObject->node->setPosition(ref_root->left_node->nodeObject->node->getPosition() + sf::Vector2f(-75, 0));
			}
			else if (root->dir == TreeType::RootDir::RIGHT);
			{
				ref_root->right_node->nodeObject->node->setPosition(ref_root->right_node->nodeObject->node->getPosition() + sf::Vector2f(-75, 0));
			}
		}

		if (root->left_node)
			CheckOverlappingNodes(root->left_node, check_node);

		if (root->right_node)
			CheckOverlappingNodes(root->right_node, check_node);
	}

	void SFML::DrawNodes(std::shared_ptr<TreeType::BinaryTree> root)
	{
		if (!root) { return; }

		ref_window->draw(*root->nodeObject->node);
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