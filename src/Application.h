#ifndef APPLICATION_H
#define APPLICATION_H


#include "utilis/Log.h"
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

//main functions
	void run();		//run loop or update loop

	void onWindowEvent(WindowEvent& e);
	void onKeyEvent(KeyEvent& e);
	void onMouseEvent(MouseEvent& e);
	//void onUiEvent(UiEvent& e);

	static Application& getApplication() { return *s_application; }
	const std::unique_ptr<WindowsWindow>& getWindow() const { return window; }

private:
	static Application *s_application;	//The problem is that Application in initialized only in main window; LNK2001 unresolved external symbol
	std::unique_ptr<WindowsWindow> window;
	//std::vector<ImGuiLayer> layers; //a list of all the panels
	//std::vector<Scene> scenes; //there can be multiple 3Dscenes, such as view mode/ cloth simulation
};

#endif //!APPLICATION_H


//jSON scene serializer and deserializer
//template <typename T, typename Class>
//inline void serialize(T obj) {}
//inline void deserialize(T obj) {}