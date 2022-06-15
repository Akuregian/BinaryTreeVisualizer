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
			std::cout << "------------Start------------\n";
			std::cout << "Added Node" << std::endl;
			if (!Root) { Root = Root->InsertNode(Root, InsertValue, ref_level); }
			else { Root->InsertNode(Root, InsertValue, ref_level); }
			SFML::WalkTree(Root, NULL);
			//while (SFML::Animate(window)) { }
			std::cout << "------------End--------------\n";
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
			SFML::UpdatePositions(Root);

		ImGui::End();
	}

	// ==================== SFML ======================

	// Static Variables
	sf::Clock SFML::m_clock;
	float SFML::duration = float();
	int SFML::current_frame = 1;
	sf::Time SFML::m_time;
	float SFML::animate_time = 0.1f;
	sf::RenderWindow* SFML::ref_window;

	SFML::SFML(sf::RenderWindow& window) { ref_window = &window; }

	void SFML::WalkTree(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> parent)
	{
		// return if root == nullptr
		if (!root) { return; }

		// Create Objects 
		CreateChildrenNodes(root, parent);

		// Debuggin
		std::cout << "Creating Root(" << root->nodeObject->data << ") Node @ Level "
			<< root->level << " With Pos: (" << root->nodeObject->position.x << ","
			<< root->nodeObject->position.y << "), Branch_Side:"; 
			std::string dir = (root->branch_side == 0 && root->branch_side != 2) ? "LEFT" : "RIGHT"; 
			if (root->dir == TreeType::RootDir::ROOT) { dir = "ROOT"; }
			std::cout << dir << std::endl;


		// Recurse Left
		if (root->left_node)
			WalkTree(root->left_node, root);

		// Recurse Right
		if (root->right_node)
			WalkTree(root->right_node, root);
	}

	void SFML::CreateChildrenNodes(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> parent)
	{
		if (root->dir == TreeType::RootDir::ROOT && !root->parent)
			root->nodeObject->CreateObject(root->nodeObject, NULL, NULL);

		if (root->dir == TreeType::LEFT && !root->nodeObject->node)
			root->nodeObject->CreateObject(root->nodeObject, parent->nodeObject, root->dir);

		if (root->dir == TreeType::RIGHT && !root->nodeObject->node)
			root->nodeObject->CreateObject(root->nodeObject, parent->nodeObject, root->dir);
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

	void SFML::CheckOverlappingNodes(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> check_node)
	{
		if (!root) { return; }

		if (root->nodeObject->position == check_node->nodeObject->position && root != check_node)
		{
			std::cout << "**Found Overlapping Node**\n";

			if (root->dir == TreeType::RootDir::LEFT)
			{
			}

			else if (root->dir == TreeType::RootDir::RIGHT)
			{
			}
		}

		if (root->left_node)
			CheckOverlappingNodes(root->left_node, check_node);

		if (root->right_node)
			CheckOverlappingNodes(root->right_node, check_node);
	}

	void SFML::UpdatePositions(std::shared_ptr<TreeType::BinaryTree> root)
	{
		if (!root) { return; }

		if(root->parent)
			root->nodeObject->position = root->parent->nodeObject->position;

		UpdatePositions(root->left_node);
		UpdatePositions(root->right_node);
	}

	void SFML::DrawBinaryTree(std::shared_ptr<TreeType::BinaryTree> root)
	{
		if (!root) { return; }

		if(root->nodeObject->connection)
			ref_window->draw(*root->nodeObject->connection);

		ref_window->draw(*root->nodeObject->node);
		ref_window->draw(root->nodeObject->text);

		DrawBinaryTree(root->right_node);
		DrawBinaryTree(root->left_node);
	}
	
}
