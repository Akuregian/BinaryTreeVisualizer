#include <imgui.h>
#include "../Headers/BinarySearchTree.hpp"

namespace Interface
{
	class ImGUI
	{
		public:
			ImGUI();
			void NodeWindow(std::shared_ptr<TreeType::BinaryTree>& bTree, std::shared_ptr<TreeType::BinaryTree>& Root);

	private:
			int value;
	};

	class SFML
	{

	};
}