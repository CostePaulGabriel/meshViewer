#pragma once

/*@brief: This class will contain all the KeyCodes for mouse and keyboard controlls. */

//from glfw3.h
enum class MouseCode
{
	None = -1,
	MouseButtonLeft   = 0,
	MouseButtonRight  = 1,
	MouseButtonMiddle = 2,
	MouseButtonLast	  = 7 //last mouse btn pressed
};

enum class KeyCode
{
	None		= -1,
	Space		= 32,
	Apostrophe  = 39,  /* ' */
	Comma		= 44,  /* , */
	Minus		= 45,  /* - */
	Period		= 46,  /* . */
	Slash		= 47,  /* / */
	Semicolon   = 59,  /* ; */
	Equal		= 61,  /* = */

	D0 = 48, /* 0 */
	D1 = 49, /* 1 */
	D2 = 50, /* 2 */
	D3 = 51, /* 3 */
	D4 = 52, /* 4 */
	D5 = 53, /* 5 */
	D6 = 54, /* 6 */
	D7 = 55, /* 7 */
	D8 = 56, /* 8 */
	D9 = 57, /* 9 */

	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,

	LeftBracket = 91,  /* [ */
	Backslash = 92,  /* \ */
	RightBracket = 93,  /* ] */
	GraveAccent = 96,  /* ` */

	World1 = 161, /* non-US #1 */
	World2 = 162, /* non-US #2 */

	// Function keys
	Escape		= 256,
	Enter		= 257,
	Tab			= 258,
	Backspace	= 259,
	Insert		= 260,
	Delete		= 261,
	
	// Arrows
	Right		= 262,
	Left		= 263,
	Down		= 264,
	Up			= 265,

	PageUp		= 266,
	PageDown	= 267,
	Home		= 268,
	End			= 269,
	CapsLock	= 280,
	ScrollLock	= 281,
	NumLock		= 282,
	PrintScreen = 283,
	Pause		= 284,

	F1  = 290,
	F2  = 291,
	F3  = 292,
	F4  = 293,
	F5  = 294,
	F6  = 295,
	F7  = 296,
	F8  = 297,
	F9  = 298,
	F10 = 299,
	F11 = 300,
	F12 = 301,
	F13 = 302,
	F14 = 303,
	F15 = 304,
	F16 = 305,
	F17 = 306,
	F18 = 307,
	F19 = 308,
	F20 = 309,
	F21 = 310,
	F22 = 311,
	F23 = 312,
	F24 = 313,
	F25 = 314,
	// Keypad 
	Keypad0 = 320,
	Keypad1 = 321,
	Keypad2 = 322,
	Keypad3 = 323,
	Keypad4 = 324,
	Keypad5 = 325,
	Keypad6 = 326,
	Keypad7 = 327,
	Keypad8 = 328,
	Keypad9 = 329,
	KeypadDecimal  = 330,
	KeypadDivide   = 331,
	KeypadMultiply = 332,
	KeypadSubtract = 333,
	KeypadAdd	   = 334,
	KeypadEnter	   = 335,
	KeypadEqual    = 336,
	//Shift
	LeftShift = 340,
	RightShift = 344,
	//Ctrl
	LeftControl = 341,
	RightControl = 345,
	//Alt
	LeftAlt = 342,
	RightAlt = 346,
	//Windows Key
	LeftSuper = 343,
	RightSuper = 347
};