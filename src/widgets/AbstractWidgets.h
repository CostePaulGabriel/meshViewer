#ifndef ABSTRACT_WIDGETS_H
#define ABSTRACT_WIDGETS_H

#include <vector>
#include <string>
#include <functional>
#include <glm/glm.hpp>
#include <glad/glad.h>		//this library should be included only here
#include "events/Event.h"

/*@brief: 
	This class contains all the base class (abstract classes) for derived widgets, such as windows, panels, buttons,etc.
	Note: An abstract class must define a virtual destructor, otherwise the derived objects won`t get destroyed.
*/

//predefinition
class Layer;
class Window;
//class Camera;	
//class Renderer;	

class Layer
{
public:
	explicit Layer(); //const std::string& title
	virtual ~Layer() = default;

	virtual void onAttach() = 0;
	virtual void onDetach() = 0;
	virtual void onEvent(Event& e) = 0;
};

class Window
{
public:
	explicit Window(const std::string& title);
	virtual ~Window() = default;

	virtual void onResize(uint16_t height, uint16_t width) = 0;
	virtual void onUpdate() = 0;
	virtual void onClose() = 0;
};

//class Camera 
//{
//public:
//private:
//};
//
//class Renderer 
//{
//public:
//	explicit Renderer();
//	virtual ~Renderer() = default;
//
//	virtual void start() = 0; //< Renderer is configured to run
//	virtual void update() = 0; //< Rendering once per frame (clearing old buffers is a must)
//
//private:
//	glm::vec4 colorBuffer = { 0.4f, 0.6f, 0.25f, 1.f }; //for now
//
//};

#endif //!ABSTRACT_WIDGETS_H