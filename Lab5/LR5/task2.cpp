#include "task2.h"

DWORD WINAPI thread1(LPVOID);
DWORD WINAPI thread2(LPVOID);

int task2()
{

    try
    {
        HANDLE ThreadOne = CreateThread(
            NULL,                        // ���������� ������. 
            0,                           // ��������� ������ �����. 0 = ������ ����� ����������� ���������.
            thread1,                     // ������� ������. 
            NULL,                        // ��������� ������. 
            0,                           // ����� ��������. 0 = ����� ����������� ���������� ����� ��������. 
            NULL);                       // ������������� ������. NULL = ������������� ������ �� ������������.
        if (!ThreadOne)
            throw 1;
        HANDLE ThreadTwo = CreateThread(
            NULL,
            0,
            thread2,
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
            INFINITE) != WAIT_OBJECT_0) // WAIT_OBJECT_0 - ������� ������
            throw 1;
    }
    catch (...)
    {
        cout << "Error number: " << GetLastError() << endl;
        return 0;
    }
    return 0;
}

DWORD WINAPI thread1(LPVOID t)
{
    for (int i = 0; i < 10; i++)
    {
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
    }
    return 0;
}

DWORD WINAPI thread2(LPVOID t)
{
    for (int i = 0; i < 10; i++)
    {
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
    }
    return 0;
}
