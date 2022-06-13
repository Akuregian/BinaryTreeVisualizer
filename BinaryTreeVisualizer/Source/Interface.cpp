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
			SFML::WalkTree(Root);
			//while (SFML::Animate(window)) { }
			std::cout << "------------End--------------\n";
		}
		// Delete Nodes
		ImGui::InputInt("DeleteValue", &DeleteValue);
		if (ImGui::Button("Delete Node"))
		{
			Root->DeleteNode(Root, DeleteValue);
			std::cout << "Deleted Node: " << DeleteValue << std::endl;
			SFML::WalkTree(Root);
		}

		// Print To console Node Values in Order [Debugging]
		if (ImGui::Button("Order Tree"))
			SFML::RecalculatePositions(Root);
			//SFML::WalkTree(Root);
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
	std::shared_ptr<TreeType::BinaryTree> SFML::ref_root;

	SFML::SFML(sf::RenderWindow& window) { ref_window = &window; }

	void SFML::WalkTree(std::shared_ptr<TreeType::BinaryTree> root)
	{
		// return if root == nullptr
		if (!root) { return; }

		// Create Objects 
		CreateChildrenNodes(root);

		// Debuggin
		std::cout << "Creating Root(" << root->nodeObject->data << ") Node @ Level "
			<< root->level << " With Pos: (" << root->nodeObject->position.x << ","
			<< root->nodeObject->position.y << "), Branch_Side:"; 
			std::string dir = (root->branch_side == 0 && root->branch_side != 2) ? "LEFT" : "RIGHT"; 
			if (root->dir == TreeType::RootDir::ROOT) { dir = "ROOT"; }
			std::cout << dir << std::endl;


		// Recurse Left
		if (root->left_node)
			WalkTree(root->left_node);

		// Recurse Right
		if (root->right_node)
			WalkTree(root->right_node);
	}

	void SFML::CreateChildrenNodes(std::shared_ptr<TreeType::BinaryTree> root)
	{
		// if root, set position to top-center screen
		if (root->dir == TreeType::ROOT && !root->parent)
		{
			ref_root = root;
			root->nodeObject->CreateNode(sf::Vector2f(ref_window->getPosition().x, 20), sf::Vector2f(ref_window->getPosition().x, 20), root->dir, 1);
			return;
		}

		// if left_node off-set from parent node: LEFT
		if (root->dir == TreeType::LEFT && !root->nodeObject->node)
		{
			root->nodeObject->CreateNode(root->parent->nodeObject->node->getPosition() + SettingsPanel::LEFT_OFFSET, root->parent->nodeObject->position, root->dir, root->level);
			CheckOverlappingNodes(ref_root, root);
		}

		// if right_node off-set from parent node: RIGHT
		if (root->dir == TreeType::RIGHT && !root->nodeObject->node)
		{
			root->nodeObject->CreateNode(root->parent->nodeObject->node->getPosition() + SettingsPanel::RIGHT_OFFSET, root->parent->nodeObject->position, root->dir, root->level);
			CheckOverlappingNodes(ref_root, root);
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

	void SFML::CheckOverlappingNodes(std::shared_ptr<TreeType::BinaryTree> root, std::shared_ptr<TreeType::BinaryTree> check_node)
	{
		if (!root) { return; }

		if (root->nodeObject->position == check_node->nodeObject->position && root != check_node)
		{
			std::cout << "**Found Overlapping Node**\n";

			if (root->dir == TreeType::RootDir::LEFT)
			{
				ref_root->left_node->nodeObject->node->setPosition(ref_root->left_node->nodeObject->node->getPosition() + SettingsPanel::LEFT_SHIFT);
				ref_root->left_node->nodeObject->position = ref_root->left_node->nodeObject->node->getPosition();
				ref_root->left_node->nodeObject->text.setPosition(ref_root->left_node->nodeObject->node->getPosition().x + (ref_root->left_node->nodeObject->node->getRadius() /2),
											   ref_root->left_node->nodeObject->node->getPosition().y + (ref_root->left_node->nodeObject->node->getRadius() / 2));

				int distance_to_other_node = std::sqrt(std::pow(ref_root->left_node->nodeObject->node->getPosition().x - ref_root->left_node->parent->nodeObject->node->getPosition().x, 2) +
												       std::pow(ref_root->left_node->nodeObject->node->getPosition().y - ref_root->left_node->parent->nodeObject->node->getPosition().y, 2));

				ref_root->left_node->nodeObject->connection->setSize(sf::Vector2f(distance_to_other_node, 5));

				ref_root->left_node->nodeObject->connection->setPosition(ref_root->left_node->parent->nodeObject->position.x + ref_root->nodeObject->node->getRadius(),
																		 ref_root->left_node->parent->nodeObject->position.y + ref_root->nodeObject->node->getRadius());
				ref_root->left_node->nodeObject->connection->setRotation(70+90);
			}
			else if (root->dir == TreeType::RootDir::RIGHT)
			{
				ref_root->right_node->nodeObject->node->setPosition(ref_root->right_node->nodeObject->node->getPosition() + SettingsPanel::RIGHT_SHIFT);
				ref_root->right_node->nodeObject->position = ref_root->right_node->nodeObject->node->getPosition();
				ref_root->right_node->nodeObject->text.setPosition(ref_root->right_node->nodeObject->node->getPosition().x + (ref_root->right_node->nodeObject->node->getRadius() /2),
											   ref_root->right_node->nodeObject->node->getPosition().y + (ref_root->right_node->nodeObject->node->getRadius() / 2));

				int distance_to_other_node = std::sqrt(std::pow(ref_root->right_node->nodeObject->node->getPosition().x - ref_root->right_node->parent->nodeObject->node->getPosition().x, 2) +
												       std::pow(ref_root->right_node->nodeObject->node->getPosition().y - ref_root->right_node->parent->nodeObject->node->getPosition().y, 2));

				ref_root->right_node->nodeObject->connection->setSize(sf::Vector2f(distance_to_other_node, 5));

				ref_root->right_node->nodeObject->connection->setPosition(ref_root->right_node->parent->nodeObject->position.x + ref_root->nodeObject->node->getRadius(),
																		  ref_root->right_node->parent->nodeObject->position.y + ref_root->nodeObject->node->getRadius());

				ref_root->right_node->nodeObject->connection->setRotation(17);
			}

		}

		if (root->left_node)
			CheckOverlappingNodes(root->left_node, check_node);

		if (root->right_node)
			CheckOverlappingNodes(root->right_node, check_node);
	}

	void SFML::RecalculatePositions(std::shared_ptr<TreeType::BinaryTree> root)
	{
		if (!root) { return; }

		if (root->dir == TreeType::RootDir::LEFT && root->level > 1)
		{
			std::cout << "Entered LEFT Level 2\n";
			root->nodeObject->node->setPosition(root->parent->nodeObject->node->getPosition() + SettingsPanel::LEFT_SHIFT + SettingsPanel::LEFT_OFFSET);
			root->nodeObject->position = root->nodeObject->node->getPosition();
			root->nodeObject->text.setPosition(root->nodeObject->node->getPosition().x + (root->nodeObject->node->getRadius() /2),
											   root->nodeObject->node->getPosition().y + (root->nodeObject->node->getRadius() / 2));

			root->nodeObject->connection->setPosition(root->parent->nodeObject->position.x + root->nodeObject->node->getRadius(),
													  root->parent->nodeObject->position.y + root->nodeObject->node->getRadius());

			root->nodeObject->connection->setRotation(135);
		}
		else if (root->dir == TreeType::RootDir::RIGHT && root->level > 1)
		{
			std::cout << "Entered RIGHT Level 2\n";
			root->nodeObject->node->setPosition(root->parent->nodeObject->node->getPosition() + SettingsPanel::RIGHT_SHIFT + SettingsPanel::RIGHT_OFFSET);
			root->nodeObject->position = root->nodeObject->node->getPosition();
			root->nodeObject->text.setPosition(root->nodeObject->node->getPosition());
			root->nodeObject->text.setPosition(root->nodeObject->node->getPosition().x + (root->nodeObject->node->getRadius() /2),
											   root->nodeObject->node->getPosition().y + (root->nodeObject->node->getRadius() / 2));

			root->nodeObject->connection->setPosition(root->parent->nodeObject->position.x + root->nodeObject->node->getRadius(),
													  root->parent->nodeObject->position.y + root->nodeObject->node->getRadius());

			root->nodeObject->connection->setRotation(45);
		}

		RecalculatePositions(root->left_node);
		RecalculatePositions(root->right_node);
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