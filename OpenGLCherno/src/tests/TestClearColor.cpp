#include "TestClearColor.h"
#include "Renderer.h"
#include "imgui/imgui.h"

namespace test {
	TestClearColor::TestClearColor() :
		_clearColor { 0.2f, 0.3f, 0.8f, 1.0f }
	{

	}

	TestClearColor::~TestClearColor() {

	}
	
	void TestClearColor::OnUpdate(float Delta) {

	}

	void TestClearColor::OnRender() {
		GLCall(glClearColor(_clearColor[0], _clearColor[1], _clearColor[2], _clearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::OnImGuiRender() {
		ImGui::ColorEdit4("Clear Color", _clearColor);
	}
	
}
