#include "task1.h"

void task2(VOID) {
    setlocale(0, "");
    STARTUPINFO info = { sizeof(info) };
    PROCESS_INFORMATION processInfo;
    string s = "C:\\Windows\\System32\\notepad.exe";
    wstring  stemp = wstring(s.begin(), s.end());
    LPCWSTR path = stemp.c_str();
    if (CreateProcess(
        path,          //���� � �����
        NULL,          //��������� ������
        NULL,          //���������� �������� �� �����������
        NULL,          //���������� ������ �� ����������
        FALSE,         //��������� ���������� �����������
        CREATE_SUSPENDED,             //����� �������� ��������
        NULL,          //���� ���������� ��������� ������������� ��������
        NULL,          //������������� �������� �������� ������������� ��������
        &info,         //��������� �� ��������� STARTUPINFO
        &processInfo)) //��������� �� ��������� ���������� � ��������
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