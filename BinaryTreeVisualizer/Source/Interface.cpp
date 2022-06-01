#include "../Headers/Interface.hpp"

namespace Interface
{

	ImGUI::ImGUI()
		: value(0)
	{
	}

	void ImGUI::NodeWindow(std::shared_ptr<TreeType::BinaryTree>& bTree, std::shared_ptr<TreeType::BinaryTree>& Root)
	{
		ImGui::Begin("Insert/Delete/Search"); // window title
		//ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(WindowText.c_str()).x)*0.5f); // calculate text size
		//ImGui::Text(WindowText.c_str()); // set text into center of window
		ImGui::InputInt("Value", &value);

		// Add Nodes
		if(ImGui::Button("Add Node"))
		{
			if (!Root) { Root = bTree->InsertNode(Root, value); }
			else { bTree->InsertNode(Root, value); }
		}

		// Print To console Node Values in Order [Debugging]
		if (ImGui::Button("Order Tree"))
		{
			bTree->InOrder(Root);
		}

		ImGui::End();
	}
}