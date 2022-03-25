#include "Scene.h"

//Exemplu : https://github.com/MagnoVJ/Sasha22/blob/main/src/main.cpp

Scene::Scene(WindowsWindow* window, const char* OpenGLversion) 
	: mWindow(std::move(window))
{
	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window->getGLFWwindow(), true);
	ImGui_ImplOpenGL3_Init(OpenGLversion);

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	//io.ConfigDockingWithShift = true;	//Dock works only when Shift is pressed

	//adding multiple viewports https://github-wiki-see.page/m/ocornut/imgui/wiki/Multi-Viewports
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::SetNextWindowBgAlpha(0.0f);

	//setting the text size and padding
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style->FramePadding = ImVec2(2, 6);
	std::cout << "Creating GUI";

	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style->WindowRounding = 0.0f;
		style->Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	io.Fonts->AddFontFromFileTTF("resources/fonts/opensans/OpenSans-Regular.ttf", cFontSize);
}

void Scene::enableGrid()
{

}

void Scene::onUpdate()
{
	// Tell OpenGL a new frame is about to begin
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGuiWindowFlags mainBarFlags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
	float height = ImGui::GetFrameHeight();
	ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
		windowFlags |= ImGuiWindowFlags_NoBackground;

	ImGui::Begin("DockSpace Demo", nullptr, windowFlags);

	// Submit the DockSpace
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Settings"))
		{
			// Disabling fullscreen would allow the window to be moved to the front of other windows,
			// which we can't undo at the moment without finer window depth/z control.
			ImGui::MenuItem("Fullscreen", NULL, nullptr);
			ImGui::MenuItem("Padding", NULL, nullptr);
			ImGui::Separator();

			if (ImGui::MenuItem("Flag: NoSplit", "", (dockspaceFlags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_NoSplit; }
			if (ImGui::MenuItem("Flag: NoResize", "", (dockspaceFlags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_NoResize; }
			if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspaceFlags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
			if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspaceFlags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
			if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, NULL)) { dockspaceFlags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
			ImGui::Separator();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Import"))
		{
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Begin("Config/Settings");
	ImGui::Button("Hello");
	static float value = 0.0f;
	ImGui::DragFloat("Value", &value);
	ImGui::End();

	ImGui::Begin("Transforms");
	DrawVec3Control("Location", glm::vec3(0.0f, 0.0f, 0.0f));
	DrawVec3Control("Rotation", glm::vec3(0.0f, 0.0f, 0.0f));
	DrawVec3Control("Scale",	glm::vec3(0.0f, 0.0f, 0.0f));
	ImGui::End();

#if 0 //https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples 
	int my_image_width = 0;
	int my_image_height = 0;
	GLuint my_image_texture = 0;
	bool ret = LoadTextureFromFile("../../MyImage01.jpg", &my_image_texture, &my_image_width, &my_image_height);
#endif // 0
	ImGui::Begin("OpenGL Texture Text");
	ImGui::Text("pointer = %p", nullptr);
	ImGui::Text("size = %d x %d", nullptr, nullptr);
	ImGui::Image((void*)(intptr_t)nullptr, ImVec2(NULL, NULL));
	ImGui::End();



	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	glViewport(0, 0, mWindow->getWidth(), mWindow->getHeight());
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

	// else if(opt_ex2_Camera)
	//     example2_camera.update_draw();

	 // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
	// clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui::Begin("Scene");

	// Get the size of the child (i.e. the whole draw size of the windows).
	ImVec2 wsize = ImGui::GetWindowSize();
	// Because I use the texture from OpenGL, I need to invert the V from the UV.
	ImGui::Image(nullptr, wsize, ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();

	// ------ End of docking --------
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

#if 0
// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	// because it would be confusing to have two docking targets within each others.
ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
const ImGuiViewport* viewport = ImGui::GetMainViewport();

ImGui::SetNextWindowPos(viewport->WorkPos);
ImGui::SetNextWindowSize(viewport->WorkSize);
ImGui::SetNextWindowViewport(viewport->ID);
ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
windowFlags |= ImGuiWindowFlags_NoBackground;

ImGui::Begin("DockSpace Demo", nullptr, windowFlags);

// Submit the DockSpace
ImGuiIO& io = ImGui::GetIO();
if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
{
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);
}

if (ImGui::BeginMenuBar())
{
	if (ImGui::BeginMenu("Settings"))
	{
		// Disabling fullscreen would allow the window to be moved to the front of other windows,
		// which we can't undo at the moment without finer window depth/z control.
		ImGui::MenuItem("Fullscreen", NULL, nullptr);
		ImGui::MenuItem("Padding", NULL, nullptr);
		ImGui::Separator();

		if (ImGui::MenuItem("Flag: NoSplit", "", (dockspaceFlags & ImGuiDockNodeFlags_NoSplit) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_NoSplit; }
		if (ImGui::MenuItem("Flag: NoResize", "", (dockspaceFlags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_NoResize; }
		if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspaceFlags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
		if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspaceFlags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspaceFlags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
		if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, NULL)) { dockspaceFlags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
		ImGui::Separator();
		ImGui::EndMenu();
	}

	if (ImGui::BeginMenu("Import"))
	{
		ImGui::EndMenu();
	}
	ImGui::EndMenuBar();
}

ImGui::Begin("Config/Settings");
ImGui::Button("Hello");
static float value = 0.0f;
ImGui::DragFloat("Value", &value);
ImGui::End();

glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

glViewport(0, 0, mWindow->getWidth(), mWindow->getHeight());
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

// else if(opt_ex2_Camera)
//     example2_camera.update_draw();

 // now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
glBindFramebuffer(GL_FRAMEBUFFER, 0);
glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
// clear all relevant buffers
glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
glClear(GL_COLOR_BUFFER_BIT);

ImGui::Begin("Viewport");

// Get the size of the child (i.e. the whole draw size of the windows).
ImVec2 wsize = ImGui::GetWindowSize();
// Because I use the texture from OpenGL, I need to invert the V from the UV.
ImGui::Image(nullptr, wsize, ImVec2(0, 1), ImVec2(1, 0));
ImGui::End();

// ------ End of docking --------
ImGui::End();

ImGui::Render();

ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

// Update and Render additional Platform Windows
// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
{
	GLFWwindow* backup_current_context = glfwGetCurrentContext();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	glfwMakeContextCurrent(backup_current_context);
}
#endif // 0



