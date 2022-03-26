#include "Scene.h"

//Exemplu : https://github.com/MagnoVJ/Sasha22/blob/main/src/main.cpp

namespace ui {

	Scene::Scene(WindowsWindow* window, const char* OpenGLversion)
		: mWindow(std::move(window))
	{
		std::cout << "Creating Scene.\n";

		// Initialize ImGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigDockingWithShift = true;	//Dock works only when Shift is pressed

		//setting the text size and padding
		ImGuiStyle* style = &ImGui::GetStyle();
		style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style->FramePadding = ImVec2(2, 6);
		style->WindowRounding = 0.0f;
		style->Colors[ImGuiCol_WindowBg].w = 1.0f;

		io.Fonts->AddFontFromFileTTF("resources/fonts/opensans/OpenSans-Regular.ttf", fontSize);

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window->getGLFWwindow(), true);
		ImGui_ImplOpenGL3_Init(OpenGLversion);
	}

	void Scene::onUpdate()
	{
		//Setup ImGui and ImGuizmo to render each frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();

		//Set the flags
		static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
		static ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

		//scene viewport config
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(3.5f, 3.5f));

		//Make the dockspace
		ImGui::Begin("DockSpace", nullptr, windowFlags);
		ImGuiID dockspaceId = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);

		//Draw the tab bar
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open File...", "Ctrl+O"))
				{
					UIEvent event(UIEvent::EventType::LoadScene);
					sceneEventSender(event);
				}
				if (ImGui::MenuItem("Save File", "Ctrl+S"))
				{
					UIEvent event(UIEvent::EventType::SaveScene);
					sceneEventSender(event);
				}
				if (ImGui::MenuItem("Save File As...", "Ctrl+Shift+S"))
				{
					UIEvent event(UIEvent::EventType::SaveScene);
					sceneEventSender(event);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Settings"))
			{
				//enable VSYNC
				static bool setVsync = mWindow->useVSync();
				if (ImGui::MenuItem("Vsync", "", & setVsync))
				{
					mWindow->setVSync(setVsync);
				}
				//some window flags settings
				if (ImGui::MenuItem("Flag: NoSplit", NULL, (dockspaceFlags & ImGuiDockNodeFlags_NoSplit) != 0))
				{
					dockspaceFlags ^= ImGuiDockNodeFlags_NoSplit;
				}
				if (ImGui::MenuItem("Flag: NoDockingInCentralNode", NULL, (dockspaceFlags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))
				{
					dockspaceFlags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
				}
				if (ImGui::MenuItem("Flag: AutoHideTabBar", NULL, (dockspaceFlags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))
				{
					dockspaceFlags ^= ImGuiDockNodeFlags_AutoHideTabBar;
				}
				//ImGui::Separator();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

		//Hierarchy panel where all the objects from the scene are stored
		ImGui::Begin("Hierarchy");
		ImGui::Button("Default Btn");
		static float value = 0.0f;
		ImGui::DragFloat("Value", &value);
		ImGui::End();

		//Object Transforms (Rotate, Scale, Move)
		ImGui::Begin("Transforms");
		drawTransformTools("Location", glm::vec3(10.0f, 10.0f, 10.0f)); ImGui::Dummy(ImVec2(0.0f, 5.0f));	//spacing
		drawTransformTools("Rotation", glm::vec3(10.0f, 10.0f, 10.0f)); ImGui::Dummy(ImVec2(0.0f, 5.0f));  //spacing
		drawTransformTools("Scale", glm::vec3(10.0f, 10.0f, 10.0f));
		ImGui::End();

		//Camera Transforms
		ImGui::Begin("Camera Settings");
		//Field of view, distance
		ImGui::End();

#if 0 //https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples 
		int my_image_width = 0;
		int my_image_height = 0;
		GLuint my_image_texture = 0;
		Texture::LoadTextureFromFile("resources/textures/test_img.jpg", &my_image_texture, &my_image_width, &my_image_height);
		ImGui::Begin("OpenGL Texture Text");
		ImGui::Text("pointer = %p", my_image_texture);
		ImGui::Text("size = %d x %d", my_image_width, my_image_height);
		ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
		ImGui::End();
#endif
		//Scene UI
		ImGui::Begin("Scene");
		// Get the size of the child (i.e. the whole draw size of the windows).
		ImVec2 windowSize = ImGui::GetWindowSize();	
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		// Because I use the texture from OpenGL, I need to invert the V from the UV.
		//ImGui::Image(NULL, windowSize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::End();

		//end of the docking space
		ImGui::End();

		//Render the UI
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			//(OpenGL context(window, attributes) is changed by the platform so I need a backup in case the context will be null.
			GLFWwindow* backupContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupContext);
		}
	}

	void Scene::drawTransformTools(const std::string& label, glm::vec3 values, float resetValue, float columnWidth)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];	//get the first font

		ImGui::PushID(label.c_str());

		ImGui::Columns(2);
		ImGui::SetColumnWidth(0, columnWidth);
		ImGui::Text("%s", label.c_str());
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		//GImGui -> imgui context ptr
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
}