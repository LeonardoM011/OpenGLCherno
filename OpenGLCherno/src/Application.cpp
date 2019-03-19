#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "vendor/imgui/imgui.h"
#include "vendor/imgui/imgui_impl_glfw_gl3.h"
#include "tests/TestClearColor.h"
#include "tests/TestTexture2D.h"

int main(int argc, char **argv) {
	GLFWwindow* window;
	
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Glew init failed!" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		/*float positions[] = {
			-0.5f, -0.5f,  0.0f,  0.0f,
			-0.5f,  0.5f,  0.0f,  1.0f,
			 0.5f,  0.5f,  1.0f,  1.0f,
			 0.5f, -0.5f,  1.0f, -0.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};*/

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		/*VertexArray va;
		VertexBuffer vb(positions, (4 * 4) * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		glm::mat4 projectionMat = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); // 2.0f * 2 = 4, 1.5f * 2 = 3 => 4:3 aspect ratio
		glm::mat4 viewMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		
		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

		Texture texture("res/textures/Cherno.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		va.UnBind();
		vb.Unbind();
		ib.Unbind();
		shader.UnBind();
		*/

		Renderer renderer;

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		/*glm::vec3 translationA(0.1f, 0.0f ,0.0f);
		glm::vec3 translationB(0.2f, 0.0f ,0.0f);*/

		test::Test *currentTest = nullptr;
		test::TestMenu *testMenu = new test::TestMenu(currentTest);
		currentTest = testMenu;

		testMenu->RegisterTest<test::TestClearColor>("Clear Color");
		testMenu->RegisterTest<test::TestTexture2D>("2D Texture");

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window)) {
			/* Render here */
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

			renderer.Clear();

			ImGui_ImplGlfwGL3_NewFrame();

			if (currentTest) {

				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test");
				if (currentTest != testMenu && ImGui::Button("<-")) {
					delete currentTest;
					currentTest = testMenu;
				}
				currentTest->OnImGuiRender();
				ImGui::End();

			}

			/*
			{
				glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), translationA);
				glm::mat4 MVP = projectionMat * modelMat * viewMat;
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", MVP);
				renderer.Draw(va, ib, shader);
			}
			{
				glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), translationB);
				glm::mat4 MVP = projectionMat * modelMat * viewMat;
				shader.Bind();
				shader.SetUniformMat4f("u_MVP", MVP);
				renderer.Draw(va, ib, shader);
			}
			
			
			{
				ImGui::SliderFloat3("Translation A", &translationA.x, -2.0f, 2.0f);
				ImGui::SliderFloat3("Translation B", &translationB.x, -2.0f, 2.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			*/

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	
		delete currentTest;

		if (currentTest != testMenu) {
			delete testMenu;
		}

	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
