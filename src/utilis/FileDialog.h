#pragma once
#include "MessageBox.h"
#include <string>

//Windows File dialog implementation for opening a fileDialog or save dialog

class FileDialog
{
public:
    FileDialog() = default;
    ~FileDialog() = default;

	std::string openFileDialog(const char* filter = NULL)
	{
        OPENFILENAMEA ofn;

        char szFile[260];

        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
		
		if (filter)
			ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
		else ofn.lpstrFilter = filter;

        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        // Display the Open dialog box. 
        if (GetOpenFileNameA(&ofn) == TRUE)
        {
            return ofn.lpstrFile;

        }
        return std::string();
	};

	std::string saveFileDialog(const char* filter)
	{
		OPENFILENAMEA ofn;
		CHAR szFile[260] = { 0 };
		CHAR currentDir[256] = { 0 };
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		if (GetCurrentDirectoryA(256, currentDir))
			ofn.lpstrInitialDir = currentDir;
		ofn.lpstrFilter = filter;
		ofn.nFilterIndex = 1;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR;

		// Sets the default extension by extracting it from the filter
		ofn.lpstrDefExt = strchr(filter, '\0') + 1;

		if (GetSaveFileNameA(&ofn) == TRUE)
			return ofn.lpstrFile;

		return std::string();
	}

private:
	OPENFILENAMEA ofn;      // dialog box
	//HWND hwnd;              // owner window (WindowsWindow)
	HANDLE hf;              // file handle 
};