#pragma once

#include <GLFW/glfw3.h>
#include "events/KeyCodes.h"
#include <glm/vec2.hpp>

//Signal-Slot event system library(thread safe)
#include <sigslot/signal.hpp>
using namespace sigslot;

/**@brief 
*	Multithreading :
	This is a thread safe event system based on the Observer Pattern, multiple observers will subscribe to a specific event,
	and when that event is triggered all the subscribers/observers to that specific event will be announced.
	Thread safe means that while the event is processed by a thread, no other thread will try to get his resource and modify it, 
	if it does, this will result in a deadlock or unexpected behaviour.
	To avoid those problems, each thread will lock the resource using an std::mutex and unlock it when the processing has been finished.

	Event class is a base class for all the derived Events, contains an Enum that helps to differentiate between events, and a getter for the eventType.
	MouseEvents, KeyEvents, WindowEvents and UIEvents are constructed when an event occurs.
	Then that event is sent with a signal to the Application class slot, that decide what to do with that event.
*/

//object connect & pointer connect
#define PtrConnect(objectSender, signal, objectReceiver, slot)  objectSender->signal.connect(slot, objectReceiver)
#define ObjConnect(objectSender, signal, objectReceiver, slot)  objectSender.signal.connect(slot, objectReceiver)

struct Event
{
	enum class EventType : uint32_t
	{
		WindowResized, WindowMaximized, WindowMinimized, WindowClosed,			//Window events
		MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased,		//Mouse events
		KeyPressed, KeyReleased, KeyTyped, KeyRepeat,							//Key events
		SaveScene,	LoadScene, 													//Scene events
		MeshLoaded,	MeshDeleted, MeshTransformed, MeshSelected, MeshDeselected, //Mesh events
		TextureChanged			
	};
	Event() = default;
	virtual ~Event() = default;
	virtual EventType getType() const = 0;
};

class MouseEvent : public Event
{
public:
	explicit MouseEvent(const EventType type, const float xOffset, const float yOffset)
	{
		switch (type)
		{
		case EventType::MouseMoved:    { mType = type; mPosition.x = xOffset; mPosition.y = yOffset; } break;
		case EventType::MouseScrolled: { mType = type; mScroll.x = xOffset; mScroll.y = yOffset; } break;
		default: break;
		}
	};
	explicit MouseEvent(const EventType type, const MouseCode button)
		: mType(type), mButton(button) { };

	~MouseEvent() = default;

	virtual EventType getType() const override { return mType; }
	glm::vec2 getPosition() const { return mPosition; }				//this is the position when a specific event occurs
	glm::vec2 getScroll() const { return mScroll; }
	int getBtnPressed() const { return (int)mButton; }	

	//Used only to check the user input (no instance of event needed)
	static bool isMouseBtnPressed(GLFWwindow* window, MouseCode btn)	
	{
		int btnState = glfwGetMouseButton(window, (int)btn);
		return btnState == GLFW_PRESS;
	}
private:
	EventType mType;
	glm::vec2 mPosition;
	glm::vec2 mScroll;
	MouseCode mButton;
	//bool cursorLocked = false;
};

class KeyEvent : public Event
{
public:
	explicit KeyEvent(const EventType type, const KeyCode keycode)
	{
		switch (type)
		{
		case EventType::KeyPressed: { mType = type; mKey = keycode;} break;
		case EventType::KeyReleased:{ mType = type; mKey = keycode;} break;
		case EventType::KeyTyped:   { mType = type; mKey = keycode;} break;
		default:
			break;
		}
	}
	explicit KeyEvent(const EventType type, const KeyCode keycode, const uint16_t repeatCount)
		: mType(type), mKey(keycode), mRepeatCount(repeatCount){ };

	~KeyEvent() = default;
	
	virtual EventType getType() const override { return mType; }
	uint32_t getRepeatCount() const { return mRepeatCount; }
	uint32_t getKeyPressed() const { return (uint32_t)mKey; }

	//Used only to check the user input (no instance of event needed)
	static bool isKeyPressed(GLFWwindow* window, KeyCode key)
	{
		int keyState = glfwGetKey(window, (uint32_t)key);
		return keyState == GLFW_PRESS || keyState == GLFW_REPEAT;
	}
private:
	EventType mType;
	KeyCode mKey;
	uint16_t mRepeatCount;
};

class WindowEvent : public Event
{
public:	
	explicit WindowEvent(const EventType type, const uint16_t width = 0, const uint16_t height = 0)
	{
		switch (type)
		{
		case EventType::WindowResized:   { mType = type; mWidth = width; mHeight = height; }  break;
		case EventType::WindowMaximized: { mType = type; mWidth = width; mHeight = height; }  break;
		case EventType::WindowMinimized: { mType = type; mWidth = width; mHeight = height; }  break;
		default: break;
		}
	}
	~WindowEvent() = default;
	virtual EventType getType() const override { return mType; }
	uint16_t getWidth() const { return mWidth; }
	uint16_t getHeight() const { return mHeight; }
private:
	EventType mType;
	uint16_t mWidth;
	uint16_t mHeight;
};

class UIEvent : public Event
{
public:
	//Construct an Event that contains the path to a new mesh/texture or scene
	explicit UIEvent(const EventType type, const std::string path = "")
	{ 
		switch (type)
		{
		case EventType::MeshLoaded: {mType = type; mNewMeshPath = path;} break; 
		case EventType::MeshSelected: {mType = type; mSelectedMesh = path; } break;
		case EventType::MeshDeselected: {mType = type; mSelectedMesh = ""; } break;
		case EventType::TextureChanged: {mType = type; mNewTexturePath = path;} break; 
		case EventType::SaveScene : {mType = type; mScenePath = path; } break;
		case EventType::LoadScene : {mType = type; mScenePath = path; } break;
		default: break;
		}
	};
	explicit UIEvent(const EventType type, const std::vector<glm::vec3> meshTransforms)
	{
		//EventType::MeshTransformed
		mType = type;
		mMeshTransforms = meshTransforms;
	};

	virtual EventType getType() const override { return mType; }
	const std::string& getMeshPath() const { return mNewMeshPath; }
	const std::string& getScenePath() const { return mScenePath; }
	const std::string& getTexturePath() const { return mNewTexturePath; }
	const std::string& getSelectedMesh() const { return mSelectedMesh; }
	
	//< Returns the Transforms getTransforms()[0] = Location, getTransforms()[1] = Rotation, getTransforms()[2] = Scale.
	const std::vector<glm::vec3>& getTransforms() const {return mMeshTransforms; } 
	
private:
	EventType mType;
	std::string mNewMeshPath;   //stores the path to a mesh (3D model)
	std::string mNewTexturePath;//stores the path of the loaded texture
	std::string mScenePath;		//Serialize/Deserialize the scene to/from path
	std::string mSelectedMesh;  //selected mesh in the scene identifier
	std::vector<glm::vec3> mMeshTransforms{}; //vector stores 3 elements (Location(x,y,z), Rotation (x,y,z), Scale(x,y,z))
};