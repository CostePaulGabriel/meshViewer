#ifndef MESSAGE_BOX_H
#define MESSAGE_BOX_H

#include "widgets/WindowsWindow.h"
#include <windows.h>

/**@brief WinMessageBox is a wrapper class around Windows MessageBox
*	https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox?redirectedfrom=MSDN.
	//int MessageBox(
	//		[in, optional] HWND    hWnd,		-> window modal, if is null this messagebox doesn`t have a parent
	//		[in, optional] LPCTSTR lpText,		-> message to display
	//		[in, optional] LPCTSTR lpCaption,	-> title (default is ERROR)
	//		[in]           UINT    uType		-> buttons with behaviour
	//);
*/
class WinMessageBox
{
public:
	enum TitleFlags { _ERROR = ERROR, WARNING, CRITICAL, INFO };
	explicit WinMessageBox(const std::unique_ptr<WindowsWindow>& window, const char* text, int titleFlags = _ERROR);
	~WinMessageBox() = default;

	int exec() const { return result; }
private:
	int result; //< what button was pressed by the user
};

#endif