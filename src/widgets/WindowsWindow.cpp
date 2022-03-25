#include "WindowsWindow.h"
#include <iostream>
#include "utilis/MessageBox.h"

WindowsWindow::WindowsWindow(const std::string& title)
	: Window(title)
{
	//config window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//start maximized
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	//config window size and frame rate by monitor
	const GLFWvidmode* monitor = glfwGetVideoMode(glfwGetPrimaryMonitor());
	mWidth = monitor->width;
	mHeight = monitor->height;
	mRefreshRate = monitor->refreshRate;

	//set window colors and apply the refreshrate by monitor settings
	glfwWindowHint(GLFW_REFRESH_RATE, mRefreshRate);
	glfwWindowHint(GLFW_RED_BITS, monitor->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, monitor->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, monitor->blueBits);

	//make the window
	mGLFWwindow = glfwCreateWindow(mWidth, mHeight, title.c_str(), nullptr, nullptr);
	assert(mGLFWwindow == nullptr, "Failed to build the window.");

	glfwMakeContextCurrent(mGLFWwindow);

	//enable vsync,	More about that here: https://microeducate.tech/glfwswapinterval1-fails-to-enable-vsync/
	glfwSwapInterval(VSync);
	glfwSetWindowMonitor(mGLFWwindow, nullptr, NULL, NULL, mWidth, mHeight, mRefreshRate);

	//load glad to provide more functionality to OpenGL
	gladLoadGL();

	//setup for glfwWindow to receive callbacks (More about callbacks: https://stackoverflow.com/questions/29356783/glfwsetcursorposcallback-to-function-in-another-class)
	glfwSetWindowUserPointer(mGLFWwindow, this);

	//Window resize callback
	glfwSetWindowSizeCallback(mGLFWwindow, [](GLFWwindow* window, int width, int height)
	{
		if (WindowsWindow* windowControls = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window)))
		{
			windowControls->mWidth = width;
			windowControls->mHeight = height;
			WindowEvent event(WindowEvent::EventType::WindowResized,width, height);
			//windowControls->windowHandler(event);
			windowControls->windowEventSignal(event);
		}
	});

	//Window Close callback
	glfwSetWindowCloseCallback(mGLFWwindow, [](GLFWwindow* window)
	{
		if (WindowsWindow* windowControls = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window)))
		{
			WinMessageBox exitMsg(nullptr, std::string("Scene was not saved, are you sure you want to exit the application?\n").c_str(), WinMessageBox::INFO);
			//response: YES = 6, NO = 7
			(exitMsg.exec() == 7) ? glfwSetWindowShouldClose(window, GL_FALSE) : glfwSetWindowShouldClose(window, GL_TRUE);
		}
	});

	//window getKey callback
	glfwSetKeyCallback(mGLFWwindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (WindowsWindow* windowControls = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window)))
		{
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyEvent event(KeyEvent::EventType::KeyPressed,(KeyCode)key, 0);
				//windowControls->windowHandler(event); 
				//std::cout << "key pressed " << key << "\n";
				windowControls->windowKeyEventSignal(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyEvent event(KeyEvent::EventType::KeyReleased,(KeyCode)key, 0);
				//windowControls->windowHandler(event); 
				//std::cout << "key released " << key << "\n";
				windowControls->windowKeyEventSignal(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyEvent event(KeyEvent::EventType::KeyPressed,(KeyCode)key, 1);
				//windowControls->windowHandler(event); 
				//std::cout << "key repeat " << key << "\n";
				windowControls->windowKeyEventSignal(event);
				break;
			}
			}
		}
	});

	//Window get typed text callback
	glfwSetCharCallback(mGLFWwindow, [](GLFWwindow* window, unsigned int keycode)
	{
		if (WindowsWindow* windowControls = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window)))
		{
			KeyEvent event(KeyEvent::EventType::KeyTyped,(KeyCode)keycode);
			//windowControls->windowHandler(event); std::cout << "key typed " << keycode << "\n";
			windowControls->windowKeyEventSignal(event);
		}
	});

	//window het mouse button clicked
	glfwSetMouseButtonCallback(mGLFWwindow, [](GLFWwindow* window, int button, int action, int mods)
	{
		if(WindowsWindow* windowControls = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window)))
		{
			switch (action)
			{
			case GLFW_PRESS:
			{	
				MouseEvent event(MouseEvent::EventType::MouseButtonPressed,(MouseCode)button);
				//windowControls->windowHandler(event); std::cout << "mouse btn pressed " << button << "\n";
				windowControls->windowMouseEventSignal(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseEvent event(MouseEvent::EventType::MouseButtonReleased,(MouseCode)button);
				//windowControls->windowHandler(event); std::cout << "mouse btn released " << button << "\n";
				windowControls->windowMouseEventSignal(event);
				break;
			}
			}
		}
	});

	//window get mouse scroll callback
	glfwSetScrollCallback(mGLFWwindow, [](GLFWwindow* window, double xOffset, double yOffset)
	{
		if (WindowsWindow* windowControls = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window)))
		{
			MouseEvent event(MouseEvent::EventType::MouseScrolled, (float)xOffset, (float)yOffset);
			//windowControls->windowHandler(event);
			windowControls->windowMouseEventSignal(event);
		}
	});

	//window get mouse cursor position callback 
	glfwSetCursorPosCallback(mGLFWwindow, [](GLFWwindow* window, double xPos, double yPos)
	{
		if (WindowsWindow* windowControls = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window)))
		{
			MouseEvent event(MouseEvent::EventType::MouseMoved, (float)xPos, (float)yPos);
			//windowControls->windowHandler(event);	std::cout <<"Mouse moved"<< event.getPosition().x << "	" << event.getPosition().y;
			windowControls->windowMouseEventSignal(event);
		}
	});
}

WindowsWindow::~WindowsWindow()
{
	glfwDestroyWindow(mGLFWwindow);
	glfwTerminate();
}

void WindowsWindow::onClose()
{
}

void WindowsWindow::onResize(uint16_t height, uint16_t width)
{
}

void WindowsWindow::onUpdate()
{
}