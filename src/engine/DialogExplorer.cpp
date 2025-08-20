#include "engine/DialogExplorer.h"
#include <codecvt>
#include <locale>
#include <windows.h>

std::string showSaveFileDialog(HWND owner) {
	OPENFILENAMEW ofn;
	wchar_t szFile[MAX_PATH] = L"";

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = owner;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = MAX_PATH;

	// Filter for binary files only
	ofn.lpstrFilter = L"Binary Files\0*.bin\0\0";
	ofn.nFilterIndex = 1;

	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = nullptr;

	// Flags
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

	// Default extension (added automatically if missing)
	ofn.lpstrDefExt = L"bin";

	if (GetSaveFileNameW(&ofn)) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(ofn.lpstrFile);
	}

	return "";
}
