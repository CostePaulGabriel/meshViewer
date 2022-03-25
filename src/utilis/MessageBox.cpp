#include "MessageBox.h"

WinMessageBox::WinMessageBox(const std::unique_ptr<WindowsWindow>& window, const char* text, int titleFlags)
{
	std::string windowTitle; //title is written on which type of messageBox is created, default is ERROR
	switch (titleFlags)
	{
	case WARNING: windowTitle = "WARNING";
		result = MessageBox(window != nullptr ? dynamic_cast<HWND>(window.get()) : NULL, text, windowTitle.c_str(),
			MB_ICONWARNING | MB_OKCANCEL);
		break;
	case INFO: windowTitle = "INFO";
		result = MessageBox(window != nullptr ? dynamic_cast<HWND>(window.get()) : NULL, text, windowTitle.c_str(),
			MB_ICONINFORMATION | MB_YESNO);
		break;
	case CRITICAL: windowTitle = "CRITICAL";
		result = MessageBox(window != nullptr ? dynamic_cast<HWND>(window.get()) : NULL, text, windowTitle.c_str(),
			MB_ICONERROR | MB_OK);
		break;
	default: windowTitle = "ERROR";
		result = MessageBox(window != nullptr ? dynamic_cast<HWND>(window.get()) : NULL, text, windowTitle.c_str(),
			MB_ICONERROR | MB_OKCANCEL);
		break;
	}
	//Sample :  WinMessageBox msgbox(window, "un mesaj", WinMessageBox::INFO);
}