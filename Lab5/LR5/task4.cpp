#include "task4.h"

DWORD WINAPI thread1_4(LPVOID);
DWORD WINAPI thread2_4(LPVOID);
HANDLE hMutex;

int task4()
{

    try
    {
        hMutex = CreateMutex( // Создает или открывает объект мьютекса.
            NULL,             // Указатель на структуру SECURITY_ATTRIBUTES. NULL = не может быть унаследован дочерними процессами.
            FALSE,            // FALSE = вызывающий поток не получает права собственности на мьютекс.
            NULL);            // Имя объекта мьютекса. NULL = объект мьютекса создается без имени.
        if (hMutex == NULL)
            throw 1;
        HANDLE ThreadOne = CreateThread(
            NULL,                        // Дескриптор защиты. 
            0,                           // Начальный размер стека. 0 = размер стека исполняемой программы.
            thread1_4,                   // Функция потока. 
            NULL,                        // Параметры потока. 
            0,                           // Опции создания. 0 = поток запускается немедленно после создания. 
            NULL);                       // Идентификатор потока. NULL = идентификатор потока не возвращается.
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
            2,                          // размер массива дескрипторов
            threads,                    // Массив дескрипторов объектов.
            TRUE,                       // TRUE = возвращает состояние всех объектов в массиве
            100000) != WAIT_OBJECT_0)   // WAIT_OBJECT_0 - нулевой объект
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
        ReleaseMutex(hMutex); // Освобождает право собственности на указанный объект мьютекса.
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
