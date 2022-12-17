#include "task4.h"

DWORD WINAPI thread1_4(LPVOID);
DWORD WINAPI thread2_4(LPVOID);
HANDLE hMutex;

int task4()
{

    try
    {
        hMutex = CreateMutex( // ������� ��� ��������� ������ ��������.
            NULL,             // ��������� �� ��������� SECURITY_ATTRIBUTES. NULL = �� ����� ���� ����������� ��������� ����������.
            FALSE,            // FALSE = ���������� ����� �� �������� ����� ������������� �� �������.
            NULL);            // ��� ������� ��������. NULL = ������ �������� ��������� ��� �����.
        if (hMutex == NULL)
            throw 1;
        HANDLE ThreadOne = CreateThread(
            NULL,                        // ���������� ������. 
            0,                           // ��������� ������ �����. 0 = ������ ����� ����������� ���������.
            thread1_4,                   // ������� ������. 
            NULL,                        // ��������� ������. 
            0,                           // ����� ��������. 0 = ����� ����������� ���������� ����� ��������. 
            NULL);                       // ������������� ������. NULL = ������������� ������ �� ������������.
        if (!ThreadOne)
            throw 1;
        HANDLE ThreadTwo = CreateThread(
            NULL,
            0,
            thread2_4,
            NULL,
            0,
            NULL);
        if (!ThreadTwo)
            throw 1;
        HANDLE threads[2] = { ThreadOne, ThreadTwo };
        if (!threads)
            throw 1;
        if (WaitForMultipleObjects(
            2,                          // ������ ������� ������������
            threads,                    // ������ ������������ ��������.
            TRUE,                       // TRUE = ���������� ��������� ���� �������� � �������
            100000) != WAIT_OBJECT_0)   // WAIT_OBJECT_0 - ������� ������
            throw 1;
    }
    catch (...)
    {
        cout << "Error number: " << GetLastError() << endl;
        return 0;
    }
    return 0;
}

DWORD WINAPI thread1_4(LPVOID t)
{
    for (int i = 0; i < 10; i++)
    {
        WaitForSingleObject(
            hMutex,
            INFINITE);
        cout << "F";
        Sleep(100);
        cout << "i";
        Sleep(100);
        cout << "r";
        Sleep(100);
        cout << "s";
        Sleep(100);
        cout << "t";
        Sleep(100);
        cout << " ";
        Sleep(100);
        cout << "t";
        Sleep(100);
        cout << "h";
        Sleep(100);
        cout << "r";
        Sleep(100);
        cout << "e";
        Sleep(100);
        cout << "a";
        Sleep(100);
        cout << "d" << endl;
        ReleaseMutex(hMutex); // ����������� ����� ������������� �� ��������� ������ ��������.
    }
    return 0;
}

DWORD WINAPI thread2_4(LPVOID t)
{
    for (int i = 0; i < 10; i++)
    {
        WaitForSingleObject(
            hMutex,
            INFINITE);
        cout << "S";
        Sleep(100);
        cout << "e";
        Sleep(100);
        cout << "c";
        Sleep(100);
        cout << "o";
        Sleep(100);
        cout << "n";
        Sleep(100);
        cout << "d";
        Sleep(100);
        cout << " ";
        Sleep(100);
        cout << "t";
        Sleep(100);
        cout << "h";
        Sleep(100);
        cout << "r";
        Sleep(100);
        cout << "e";
        Sleep(100);
        cout << "a";
        Sleep(100);
        cout << "d" << endl;
        Sleep(100);
        ReleaseMutex(hMutex);
    }
    return 0;
}
