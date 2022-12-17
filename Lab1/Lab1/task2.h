#pragma once
#include <iostream>
#include <windows.h>
#include <tchar.h>

using namespace std;

void printLastFileError(HANDLE h_file, const std::string& message_after_error);
void cutData(LPCWSTR source_filename, DWORD position, LPCWSTR destination_filename);

void task2();
