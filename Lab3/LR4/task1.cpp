#include "task1.h"

void task1( VOID ) {
    setlocale(0, "");
    STARTUPINFO info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;
    string s = "C:\\Windows\\System32\\notepad.exe";
    wstring  stemp= wstring(s.begin(),s.end());
    LPCWSTR path = stemp.c_str();
    if (CreateProcessW(
                path,          //путь к файлу
                NULL,          //командная строка
                NULL,          //дескриптор процесса не наследуется
                NULL,          //дескриптор потока не наследутся
                FALSE,         //установка описателей нследования
                0,             //флаги создания процесса
                NULL,          //блок переменных окружения подительского процесса
                NULL,          //использование текущего каталога родительского процесса
                &info,         //указатель на структуру STARTUPINFO
                &processInfo)) //указатель на структуру информации о процессе
    {
        cout << "ID: " << processInfo.dwProcessId << '\n';
        char ch;
        bool flag = true;

        do {
            if (flag) {
                flag = false;
                cout << "s - приостановить поток\nr - возобновить поток\nt - завершить работу\n";
            }
            cin >> ch;
            if (ch == 's') { 
                flag = true;
                if (SuspendThread(processInfo.hThread) == -1) {
                    cout << "SuspendThread Error\n";
                }
            }
            if (ch == 'r') {
                flag = true;
                if (ResumeThread(processInfo.hThread) == -1) {
                    cout << "ResumeThread Error\n";
                }
            }
            if (ch == 't') {
                flag = true;
                if (!TerminateProcess(processInfo.hProcess,0))
                    cout << "TerminateProcess Error\n";
            }
        } while (ch != 't');

        WaitForSingleObject(processInfo.hProcess, INFINITE);

        CloseHandle(processInfo.hProcess);
        //CloseHandle(processInfo.hThread);
    }
    else {
        cout << "CreateProcess Error";
    }
}