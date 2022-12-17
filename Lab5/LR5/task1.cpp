#include "task1.h"

/*1.�������� ���������, ����������� (�� ����� 10 ���) ��������� � ������� ��� ��������� ����� ������������.
�� ���� ���������� ������� ��� ��������� ������ (CreateThread), ������� ����� ����������� �������� � ������� ������
���� �����. ���������� ���������� ���������� ���������, �. �. �������� ����� ������ ����������� ����� ��������
(���, ������� ������� �����). ��� �������� ��������� ������ ������� ����� ������������ ������� WaitForSingleObject
��� WaitForMultipleObjects.*/

DWORD WINAPI thread1_2(LPVOID); // ������� �������� ������ (LPVOID-��������� �� ����� ���)
DWORD WINAPI thread2_2(LPVOID);

int task1()
{

    try //��� ��������� ����������. ��������� ���������� ���� ����, ������� ����� ����������� �� ������� ������ �� ����� ��������
    {
        HANDLE ThreadOne = CreateThread( 
            NULL,                        // ���������� ������. 
            0,                           // ��������� ������ �����. 0 = ������ ����� ����������� ���������.
            thread1_2,                     // ������� ������. 
            NULL,                        // ��������� ������. 
            0,                           // ����� ��������. 0 = ����� ����������� ���������� ����� ��������. 
            NULL);                       // ������������� ������. NULL = ������������� ������ �� ������������.
        if (!ThreadOne)
            throw 1; // ����� ��� �������� � ����������� ���� � ������������ ��� ������������ ������, 
                     // ������� ���������� �������, �� �� ����� �������������� ������������ ����
        HANDLE ThreadTwo = CreateThread(
            NULL,
            0,
            thread2_2,
            NULL,
            0,
            NULL);
        if (!ThreadTwo)
            throw 1;
        HANDLE threads[2] = { ThreadOne, ThreadTwo };
        if (!threads)
            throw 1; //��� ���������� �������� ����������
        if (WaitForMultipleObjects(     
            2,                          // ������ �������
            threads,                    // ������
            TRUE,                       // TRUE = ������� ���������� ��������� ���� �������� � �������
            INFINITE) != WAIT_OBJECT_0) // WAIT_OBJECT_0 - ������� ������
            throw 1;
    }
    catch (...) 
        //catch (...) - ��������� ������� ����������
    {
        cout << "Error number: " << GetLastError();
        return 0;
    }
    return 0;
}

DWORD WINAPI thread1_2(LPVOID t) //������� ������
{
    for (int i = 0; i < 10000; i++)
        cout << "First thread\n";
    return 0;
}

DWORD WINAPI thread2_2(LPVOID t)
{
    for (int i = 0; i < 10000; i++)
        cout << "Second thread\n";
    return 0;
}
