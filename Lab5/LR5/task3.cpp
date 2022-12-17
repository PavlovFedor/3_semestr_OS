#include "task3.h"

CRITICAL_SECTION cs; // Объект критического раздела.

DWORD WINAPI thread1_3(LPVOID);
DWORD WINAPI thread2_3(LPVOID);

int task3()
{
    InitializeCriticalSection(&cs); // Инициализирует объект критического раздела.
    try
    {
        HANDLE ThreadOne = CreateThread(
            NULL,                        // Дескриптор защиты. 
            0,                           // Начальный размер стека. 0 = размер стека исполняемой программы.
            thread1_3,                   // Функция потока. 
            NULL,                        // Параметры потока. 
            0,                           // Опции создания. 0 = поток запускается немедленно после создания. 
            NULL);                       // Идентификатор потока. NULL = идентификатор потока не возвращается.
        if (!ThreadOne)
            throw 1;
        HANDLE ThreadTwo = CreateThread(
            NULL,
            0,
            thread2_3,
            NULL,
            0,
            NULL);
        if (!ThreadTwo)
            throw 1;
        HANDLE threads[2] = { ThreadOne, ThreadTwo };
        if (!threads)
            throw 1;
        if (WaitForMultipleObjects(
            2,                          // размер массива дескрипторов
            threads,                    // Массив дескрипторов объектов.
            TRUE,                       // TRUE = возвращает состояние всех объектов в массиве
            INFINITE) != WAIT_OBJECT_0) // WAIT_OBJECT_0 - нулевой объект
            throw 1;
        DeleteCriticalSection(&cs); // Освобождает все ресурсы, используемые неизвестным объектом критического раздела.
    }
    catch (...)
    {
        cout << "Error number: " << GetLastError() << endl;
        return 0;
    }
    return 0;
}

DWORD WINAPI thread1_3(LPVOID t)
{
    for (int i = 0; i < 10; i++)
    {
        EnterCriticalSection(&cs); // принимает объект критического раздела
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
        Sleep(100);
        LeaveCriticalSection(&cs); // Освобождает объект критического раздела.
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI thread2_3(LPVOID t)
{
    for (int i = 0; i < 10; i++)
    {
        EnterCriticalSection(&cs);
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
        LeaveCriticalSection(&cs);
        Sleep(1);
    }
    return 0;
}
