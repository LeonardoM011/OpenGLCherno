#pragma once
#include "Test.h"

namespace test {
	class TestClearColor : public Test {
	public:
		TestClearColor();
		~TestClearColor();
		void OnUpdate(float Delta) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float _clearColor[4];
	};
}
