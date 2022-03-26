#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "Mesh.h"
#include "events/KeyCodes.h"
#include "widgets/WindowsWindow.h"	//-> access the window size and other properties

#include <imgui/imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <ImGuizmo/ImGuizmo.h>

/*@brief: The class Scene represents the 3D scene rendered inside a imGui widget.
*	This will implement all the widgets from the ImGui3D base class.
*	This scene contains a list of 3D objects represented by the mesh class.
*	Events: select object, scale object, rotate object.
*	A scene can also be serialized and deserialized in a custom format, I choose the jSON format, more here https://isocpp.org/wiki/faq/serialization.
	ImGui = Intermediate graphical user interface, game design pattern.
*/

namespace ui
{
	const float fontSize = 18.0f;	//ui font size

	class Scene
	{
	public:
		//opengl version used is 410, so by default this is used
		explicit Scene(WindowsWindow* window, const char* OpenGLversion = "#version 410"); 
		~Scene() = default;

		//events
		signal<UIEvent&> sceneEventSender;	

		//scene functions
		void onUpdate(); //This is the function that runs in the application loop, all the scene is updated each frame
		void addMesh(Mesh& mesh);		 //add a 3d object in the scene
		void onMeshSelected(Mesh& mesh); //select/deselect an object
		void drawGrid(bool flag);		 //enable/disable a 3D grid
	
	protected:
		static void drawTransformTools(const std::string& label, glm::vec3 values, float resetValue = 0.0f, float columnWidth = 80.0f);
	
	private:
		WindowsWindow* mWindow; //access the window settings
		//std::vector<Mesh> meshes; //a list of active 3D models in the scene
	};

	//generic serialization for all the meshes
}

#endif