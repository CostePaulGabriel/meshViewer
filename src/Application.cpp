#include "Application.h"
#include "utilis/MessageBox.h"

Application* Application::s_application = nullptr;	//initialize as null

Application::Application(const std::string& title) :
	window{ std::make_unique<WindowsWindow>(title)}	//give the windowsWindow the application title
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
	PtrConnect(window, WindowsWindow::windowMouseEventSignal, this, &Application::onMouseEvent);
	PtrConnect(window, WindowsWindow::windowKeyEventSignal, this, &Application::onKeyEvent);
	PtrConnect(window, WindowsWindow::windowEventSignal, this, &Application::onWindowEvent);
	
	//more connects from UIEvents (after scene class is finished)
}

Application::~Application()
{
	Log log("Application ended!");
}

void Application::run()
{
	//make some arrays just for testing
	
	//pregatim shader, vertexbuffers, arraybuffers, indexbuffers(elementbuffers)	//aici se vor incarca 2 shadere default
	Shader shader("resources/shaders/shader.vert", "resources/shaders/shader.frag");

	//pregatire scena, editor
	//Scene = new scene va fi in constructor
	//aici va fi scene->config() care va seta culorile default si locatia

	Scene* mainScene = new Scene(window.get());

	while (!glfwWindowShouldClose(window->getGLFWwindow()))
	{
		//clear buffers on each frame (2D & 3D)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Draw the imgui
		//Renderer::render(Material)...	//aici o sa fie adaugat un material la runtime
		mainScene->onUpdate();	//aici o sa fie camera, mesh
		//Editor->onUpdate();	aici o sa fie butoane
		//Console->onUpdate();	aici un terminal simplu care va scrie un mesaj de demonstratie la eveniment sau etc

		//update the window context
		glfwSwapBuffers(window->getGLFWwindow());

		//receive events from window
		glfwPollEvents();
	}

	// Deletes all ImGui instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Delete window before ending the program
	glfwDestroyWindow(window->getGLFWwindow());
	// Terminate GLFW before ending the program
	glfwTerminate();
}

void Application::onKeyEvent(KeyEvent& e)
{
	//check which key was pressed
	//check the event type
	if (e.getType() == KeyEvent::EventType::KeyPressed || e.getType() == KeyEvent::EventType::KeyTyped ||
		e.getType() == KeyEvent::EventType::KeyRepeat)
	{
		std::cout << "KeyPressedEvent " << "keyCode = [ " << e.getKeyPressed()<<" ]\n";
	}

}
void Application::onMouseEvent(MouseEvent& e)
{
	//check is mouse scrooled inside imgui, then scroll the camera
	if(e.getType() == MouseEvent::EventType::MouseMoved)
		std::cout << "mouseMovedEvent " <<"[x = " << e.getPosition().x <<", y = "<<e.getPosition().y << "]\n";
}
void Application::onWindowEvent(WindowEvent& e)
{
	//check if window resized and update the elements in the scene
	std::cout << "Window resized: [w =" << e.getWidth() << " h =" << e.getHeight() << "]\n";
}
