#pragma once

#include <memory>
#include <string>
#include <vector>
#include <flecs.h>
#include <GLFW/glfw3.h>

#include "Data/Mesh.h"
#include "utility/CCXEvent.h"

namespace ecse
{
	extern int WindowWidth;
	extern int WindowHeight;

	
	const std::vector<GLFWwindow*>& GetWindows();
	const flecs::world* GetWorld();

	extern CCX::Event<double> OnUpdate;
	extern CCX::Event<> OnDraw;

	void Init();
	int Loop(int argc, char** argv);
}