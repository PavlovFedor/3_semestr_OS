#include "task1.h"

void task2(VOID) {
    setlocale(0, "");
    STARTUPINFO info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;
    string s = "C:\\Windows\\System32\\notepad.exe";
    wstring  stemp = wstring(s.begin(), s.end());
    LPCWSTR path = stemp.c_str();
    if (CreateProcess(
        path,          //путь к файлу
        NULL,          //командная строка
        NULL,          //дескриптор процесса не наследуется
        NULL,          //дескриптор потока не наследутся
        FALSE,         //установка описателей нследования
        CREATE_SUSPENDED,             //флаги создания процесса
        NULL,          //блок переменных окружения подительского процесса
        NULL,          //использование текущего каталога родительского процесса
        &info,         //указатель на структуру STARTUPINFO
        &processInfo)) //указатель на структуру информации о процессе
    {
        cout << "ID: " << processInfo.dwProcessId << '\n';

        for (int i = 1; i < 11; i++) {
            cout << i << " ";
            Sleep(1000);
        }
        cout << "\n";

        cout << "Notepad open\n";
        if (ResumeThread(processInfo.hThread) == -1)
            cout << "ResumeThread Error\n";

        cout << "Process priority: " << GetThreadPriority(processInfo.hThread) << "\n";

        CloseHandle(processInfo.hProcess);
    }
    else {
        cout << "CreateProcess Error";
    }
    
}