#ifndef WINDOWS_WINDOW_H
#define WINDOWS_WINDOW_H

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

	//events
	virtual void onResize(uint16_t height, uint16_t width) override;
	virtual void onUpdate() override;
	virtual void onClose() override; //< ask user to save the data
	//void setWindowCallback(const WindowEventHandler& handler) { windowHandler = handler; }	//https://github.com/glfw/glfw/issues/15 -> setting up a class that triggers the callbacks, in my case is Event class
	
	//member
	void setVSync(bool state) { VSync = state; glfwSwapInterval(VSync); }
	GLFWwindow* getGLFWwindow() const { return mGLFWwindow; }
	uint16_t getWidth() { return mWidth; }
	uint16_t getHeight() { return mHeight; }

private:
	GLFWwindow* mGLFWwindow = nullptr;
	std::string mTitle;
	uint16_t mWidth, mHeight;
	uint16_t mRefreshRate;
	bool VSync = true;
	//WindowEventHandler windowHandler;
};

#endif //!WINDOWS_WINDOW_H