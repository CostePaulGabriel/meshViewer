#ifndef APPLICATION_H
#define APPLICATION_H

#include "widgets/WindowsWindow.h"
//#include "renderer/Shader.h" //-> ar trebui sa fie inclusa intr-o clasa numita renderer
#include "scene/Scene.h"	// -> ar trebui sa includ doar scena care contine un Renderer care e capabil sa adauge obiecte si shadere

/**@brief This class define the main application.
* This uses Singleton Pattern to keep only one instance of the application
* This is the controller class comparing it to a MVC pattern.
*/

class Application
{
public:
	explicit Application(const std::string& title);
	~Application();

//event sender
	signal<std::string&> logMessageSender;
	signal<bool> sceneSavedSender;

//main functions
	void run();	//run loop

//event handling in slots
	void onWindowEvent(WindowEvent& e);
	void onKeyEvent(KeyEvent& e);
	void onMouseEvent(MouseEvent& e);
	void onUIEvent(UIEvent& e);

	static Application& getApplication() { return *sApplication; }
	const std::unique_ptr<WindowsWindow>& getWindow() const { return mWindow; }

private:
	static Application *sApplication;	//The problem is that Application in initialized only in main window; LNK2001 unresolved external symbol
	std::unique_ptr<WindowsWindow> mWindow;
	ui::Scene* mainScene;
	//std::vector<Scene> scenes; //there can be multiple 3Dscenes, such as view mode/ cloth simulation
};

#endif //!APPLICATION_H


//jSON scene serializer and deserializer
//template <typename T, Class S>
//inline void serialize(T obj) {}
//inline void deserialize(T obj) {}