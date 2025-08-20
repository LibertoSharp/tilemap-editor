#ifndef DIALOGEXPLORER_H
#define DIALOGEXPLORER_H
#include <string>
#include <iostream>

typedef struct HWND__ *HWND;

std::string showSaveFileDialog(HWND owner = nullptr);
#endif //DIALOGEXPLORER_H
