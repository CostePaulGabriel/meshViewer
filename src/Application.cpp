#include "Application.h"
#include "utilis/Log.h"
#include "utilis/MessageBox.h"
#include "utilis/FileDialog.h"

Application* Application::sApplication = nullptr;	//initialize as null

Application::Application(const std::string& title) :
	mWindow{ std::make_unique<WindowsWindow>(title)}, //give the windowsWindow the application title
	mainScene{new ui::Scene(mWindow.get())}	
{	
	Log log("Application Started!");
	
	//Send events
	//applogSender.Connect(&log, &Log::writeLog);
	//applogSender.Emit("\nApplication Started.");

	//receive callbacks for window events (obsolete, now I use signal and slot)
	//window->setWindowCallback(std::bind(&Application::onEvent, this, std::placeholders::_1));

	//Receive events from window in multiple slots (multithreaded)
	//QtConnect(window, WindowsWindow::windowSender, this, &Application::onEvent);
	//window->windowSignal.connect(&Application::onSlot, this);	//this is without macro
	PtrConnect(mWindow, WindowsWindow::windowMouseEventSignal, this, &Application::onMouseEvent);
	PtrConnect(mWindow, WindowsWindow::windowKeyEventSignal, this, &Application::onKeyEvent);
	PtrConnect(mWindow, WindowsWindow::windowEventSignal, this, &Application::onWindowEvent);
	PtrConnect(mainScene, ui::Scene::sceneEventSender, this, &Application::onUIEvent);
}

Application::~Application()
{
	Log log("Application ended!");
	delete mainScene;
}

void Application::run()
{	
	//pregatim shader, vertexbuffers, arraybuffers, indexbuffers(elementbuffers)	
	Shader shader("resources/shaders/shader.vert", "resources/shaders/shader.frag"); //aici se vor incarca 2 shadere default


	while (!glfwWindowShouldClose(mWindow->getGLFWwindow()))
	{
		//clear buffers on each frame (2D & 3D)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw the imgui
		mainScene->onUpdate();	//aici o sa fie camera, mesh

		//update the window context
		glfwSwapBuffers(mWindow->getGLFWwindow());

		//receive events from window
		glfwPollEvents();
	}

	// Deletes all ImGui instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Delete window before ending the program
	glfwDestroyWindow(mWindow->getGLFWwindow());
	// Terminate GLFW before ending the program
	glfwTerminate();
}

void Application::onKeyEvent(KeyEvent& e)
{
	//check which key was pressed
	//check the event type
	if (e.getType() == KeyEvent::EventType::KeyPressed || e.getType() == KeyEvent::EventType::KeyTyped)
	{
		std::cout << "KeyPressedEvent " << "keyCode = [ " << e.getKeyPressed()<<" ]\n";
	}
}
void Application::onMouseEvent(MouseEvent& e)
{
	//check is mouse scrooled inside imgui, then scroll the camera
	if(e.getType() == MouseEvent::EventType::MouseMoved)
		std::cout << "mouseMovedEvent " <<"[x = " << e.getPosition().x <<", y = "<<e.getPosition().y << "]\n";
	if(e.getType() == MouseEvent::EventType::MouseButtonPressed)
		std::cout << "mouseButtonPressedEvent " << "[ " << e.getBtnPressed() << " ]\n";
}
void Application::onWindowEvent(WindowEvent& e)
{
	//check if window resized and update the elements in the scene
	std::cout << "Window resized: [w =" << e.getWidth() << " h =" << e.getHeight() << "]\n";
}

void Application::onUIEvent(UIEvent& e)
{
	switch (e.getType())
	{
	case UIEvent::EventType::LoadScene: 
	{ std::cout << "File dialog: open file.\n";
		FileDialog fileDialog; 
		fileDialog.openFileDialog();

		//when a scene is loaded reset the flag
		mWindow->sceneSaved(false);
	}
		break;
	case UIEvent::EventType::SaveScene:
	{ std::cout << "File save scene: open file.\n";
		FileDialog fileDialog;
		fileDialog.saveFileDialog("");
		//scene.serialize();
		//scene.deserialize();
		mWindow->sceneSaved(true);
	}
	break;
	}
}