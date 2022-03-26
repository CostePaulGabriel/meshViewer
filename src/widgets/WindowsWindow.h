#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

#include <iostream>
#include "widgets/AbstractWidgets.h"

class WindowsWindow : public Window
{
public:
	//using WindowEventHandler = std::function<void(Event&)>; //for event callbacks
	signal<WindowEvent&> windowEventSignal;
	signal<KeyEvent&> windowKeyEventSignal;
	signal<MouseEvent&> windowMouseEventSignal;

	explicit WindowsWindow(const std::string& title);
	~WindowsWindow();
	//void setWindowCallback(const WindowEventHandler& handler) { windowHandler = handler; }	//https://github.com/glfw/glfw/issues/15 -> setting up a class that triggers the callbacks, in my case is Event class
	
	virtual void setVSync(bool state) override { VSync = state; glfwSwapInterval(VSync); }
	bool useVSync() const { return VSync; }
	void sceneSaved(bool flag) { safeClose = flag; if(flag) std::cout << "Scene saved!\n"; }
	virtual GLFWwindow* getGLFWwindow() const override { return mGLFWwindow; }
	virtual uint16_t getWidth() const override { return mWidth; }
	virtual uint16_t getHeight() const override { return mHeight; }

private:
	GLFWwindow* mGLFWwindow = nullptr;
	std::string mTitle;
	uint16_t mWidth, mHeight;
	uint16_t mRefreshRate;
	bool VSync = true;
	bool safeClose = false; //Safe close is a flag that announce the user that the scene was not saved
	//WindowEventHandler windowHandler;
};

#endif //!WINDOWS_WINDOW_H