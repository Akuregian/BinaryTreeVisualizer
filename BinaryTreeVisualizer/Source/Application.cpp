// BinaryTreeVisualizer.cpp : Defines the entry point for the application.
//

//#include "../Headers/ImGUI_Interface.h"
//#include "glad/glad.h"
//#include "GLFW/glfw3.h"
#include "../Headers/Interface.hpp"
#include <imgui-SFML.h>


int main(int, char**)
{
	// SFML Window
	sf::RenderWindow window(sf::VideoMode(SettingsPanel::sWidth, SettingsPanel::sHeight), "Window title");

	// ImGui Window
	ImGui::SFML::Init(window);

	// GUI_Interface
	std::shared_ptr<Interface::ImGUI> GUI = std::make_shared<Interface::ImGUI>();
	std::shared_ptr<Interface::SFML> SFML = std::make_shared<Interface::SFML>(window);

	// DeltaTime Used to Render ImGUI windows
	sf::Clock DeltaTime;

	while (window.isOpen())
	{
		sf::Event events;
		while (window.pollEvent(events))
		{
			// Process Events for ImGui
			ImGui::SFML::ProcessEvent(events);
			if (events.type == sf::Event::Closed)
				window.close();
		}

		ImGui::SFML::Update(window, DeltaTime.restart());

		// ImGui Stuff
		GUI->NodeWindow(window);

		window.clear(sf::Color(210, 210, 210));

		SFML->Display(GUI->Root);

		ImGui::SFML::Render(window); // Render last so it doesnt get covered up
		window.display();
	}
	
	ImGui::SFML::Shutdown();

	return 0;
}
