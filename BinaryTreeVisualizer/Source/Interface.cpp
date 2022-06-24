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

			std::cout << "------------End--------------\n";
		}
		// Delete Nodes
		ImGui::InputInt("DeleteValue", &DeleteValue);

		if (ImGui::Button("Delete Node"))
		{
			Root = Root->DeleteNode(Root, DeleteValue);
			std::cout << "Deleted Node: " << DeleteValue << std::endl;
		}

		if (ImGui::Button("Create"))
		{
			int ref_level = 0;
			// Helper so i dont manually have to insert nodes
			
			// Tree
			//std::vector<int> bst_arr = { 25, 15, 30, 23, 35, 16, 11, 20, 18, 17, 19 };
			
			std::vector<int> bst_arr = { 30, 28, 32, 26, 34, 24, 36, 22, 38, 20, 40 };

			for (unsigned int i = 0; i < bst_arr.size(); i++)
			{
				if (!Root) { Root = Root->InsertNode(Root, bst_arr[i], ref_level); }
				else { Root->InsertNode(Root, bst_arr[i], ref_level); }
			}
		}

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
	
	// Draws All Connections Lines First, so there not overlapping the node
	void SFML::DrawAllConnections(std::shared_ptr<TreeType::BinaryTree> root)
	{
		if (!root)
			return;

		DrawAllConnections(root->left_node);

		if (root->nodeObject->connection)
			ref_window->draw(*root->nodeObject->connection);

		DrawAllConnections(root->right_node);
	}

	// Draw Nodes & Text 
	void SFML::DrawBinaryTree(std::shared_ptr<TreeType::BinaryTree> root)
	{
		// Pre Order Traversal
		if (!root) { return; }

		DrawBinaryTree(root->left_node);

		ref_window->draw(*root->nodeObject->node);
		ref_window->draw(root->nodeObject->text);

		DrawBinaryTree(root->right_node);
		
	}
}
