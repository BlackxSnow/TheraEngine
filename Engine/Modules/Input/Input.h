#pragma once

#include <flecs.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <algorithm>
#include <tuple>

#include "../../Engine.h"
#include "../../utility/CCXDefs.h"
#include "../../utility/CCXEvent.h"
#include "../../utility/ConsoleLogging.h"
#include "InputDefs.h"
#include "Bindings.h"

// Improvement Notes:
// - I can implement binding processors via a base class that defines `T Process(T data)` for each output type.
//		The base implementation could directly return the input value, and useful processors could be implemented as inheritors by overriding their relevant overload(s).
// - I could store and send information about the binding which would help pre-processors be more generic and modular.
//		This data could include the expected bounds of the input device for example.
// - Possibly have event data contain a stack allocated float[6] (representative of the maximum data size) to improve data processing.
// - Implement `InputDevice GetDeviceType(int bindingID)` utility to convert binding indices to more legible device types.
// - Different action maps
//		- Priorities and overrides?
// - Gamepad bindings

namespace Thera
{
	namespace Input
	{
		

		inline glm::dvec2 mousePosition;
		inline glm::dvec2 mouseDelta;

		static void UpdateMouse()
		{
			double x, y;
			glfwGetCursorPos(GetWindows()[0], &x, &y);
			mouseDelta = glm::dvec2(x - mousePosition.x, y - mousePosition.y);
			mousePosition = glm::dvec2(x, y);
		}

		void GLFWKeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
		void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		/// <summary>
		/// Invoked with raw GLFW input data on key input event.
		/// </summary>
		inline CCX::Event<GLFWwindow*, int, int, int, int> RawKeyInputReceived;
		/// <summary>
		/// Invoked with raw GLFW input data on mouse button input event.
		/// </summary>
		inline CCX::Event<GLFWwindow*, int, int, int> RawMouseInputReceived;

		void Initialise();
		void Reset(bool iterateBindings = false);

		BindingInstance* CreateBinding(Action* bindTo, Key key);
		BindingInstance* CreateBinding(Action* bindTo, Mouse mouse);
		BindingInstance* CreateBinding(Key key);
		BindingInstance* CreateBinding(Mouse mouse);

		Constituent CreateConstituent(Key key, std::initializer_list<Component> components);
		Constituent CreateConstituent(Mouse mouse, std::initializer_list<Component> components);
		Constituent CreateConstituent(Key mouse, std::initializer_list<int> components);
		Constituent CreateConstituent(Mouse mouse, std::initializer_list<int> components);
		CompositeBinding* CreateCompositeBinding(Action* bindTo, Output _dataType, Precision dataPrecision, std::vector<Constituent>&& constituents);
		CompositeBinding* CreateCompositeBinding(Output _dataType, Precision dataPrecision, std::vector<Constituent>&& constituents);

		Action* CreateAction(std::string& name, Output dataType, Precision precision = Precision::Double);
		Action* CreateAction(std::string&& name, Output dataType, Precision precision = Precision::Double);

		Action* GetAction(std::string&& name);

		void SetBindContext(Action* context);

		Action* Context();
	};
}