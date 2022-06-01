// BinaryTreeVisualizer.cpp : Defines the entry point for the application.
//

#include "../Headers/ImGUI_Interface.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


int main(int, char**)
{
	// Setup window
	if (!glfwInit())
		return 1;

	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui - Example", NULL, NULL);
	if (window == NULL)
		return 1;

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1); // Enable vsync

	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

	MyGUI::GUI_INTERFACE App;
	App.Init(window, glsl_version);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		App.NewFrame();

		// Code Goes Here
		App.Update();

		App.Render(window);
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);

	}

	App.Shutdown();
    return 0;
}
