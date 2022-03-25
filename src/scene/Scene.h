#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "Mesh.h"
#include "events/KeyCodes.h"
#include "widgets/WindowsWindow.h"	//-> access the window size and other properties

#include <imgui/imgui.h>
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
class Scene
{
public:
	explicit Scene(WindowsWindow* window, const char* OpenGLversion = "#version 410"); //opengl version used is 410, so by default this is used
	~Scene() = default;

	//signal<UiEvent&> sceneEventSender;

//scene functions
	void addMesh(Mesh& mesh);		//add a 3d object in the scene
	void deleteMesh(Mesh& mesh);	//remove a 3d object from scene
	void enableGrid();	//enable a 3D grid
	void disableGrid();	//disable the 3D grid
	void buildScene(); //this function will build all the components from the scene

//events
	void onUpdate(); //This is the function that runs in the application loop, all the scene is updated each frame
	void onKeyEvent(KeyCode key);
	void onMouseEvent(MouseCode btn);
	void onSelected(Mesh& mesh);//select an object
	void onDeselected(Mesh& mesh);//deselect an object

private:
	WindowsWindow* mWindow; //pointer to WindowsWindow, used to update the imgui context according to the windowEvents(resizing,keyPressed,mouse,etc.)
	//std::vector<Mesh> meshes; //a list of active 3D models in the scene
	const float cFontSize = 18.0f;

	void DrawVec3Control(const std::string& label, glm::vec3 values, float resetValue = 0.0f, float columnWidth = 100.0f)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text("%s", label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);

		ImGui::PopID();
	}
};


class Editor 
{

};

class Console 
{

};





#endif