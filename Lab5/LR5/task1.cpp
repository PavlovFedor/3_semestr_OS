#include "task1.h"

/*1.Написать программу, многократно (не менее 10 раз) выводящую в консоль две различные фразы одновременно.
То есть необходимо создать два различных потока (CreateThread), которые будут многократно выводить в консоль каждый
свою фразу. Обеспечить корректное завершение программы, т. е. основной поток должен завершиться после дочерних
(тех, которые выводят фразы). Для ожидания окончания работы потоков можно использовать функции WaitForSingleObject
или WaitForMultipleObjects.*/

DWORD WINAPI thread1_2(LPVOID); // функция создания потока (LPVOID-указатель на любой тип)
DWORD WINAPI thread2_2(LPVOID);

int task1()
{

    try //для обработки исключения. Позволяет определить блок кода, который будет проверяться на наличие ошибок во время выполния
    {
        HANDLE ThreadOne = CreateThread( 
            NULL,                        // Дескриптор защиты. 
            0,                           // Начальный размер стека. 0 = размер стека исполняемой программы.
            thread1_2,                     // Функция потока. 
            NULL,                        // Параметры потока. 
            0,                           // Опции создания. 0 = поток запускается немедленно после создания. 
            NULL);                       // Идентификатор потока. NULL = идентификатор потока не возвращается.
        if (!ThreadOne)
            throw 1; // нужен для создания и отображения искл и используется для перечисления ошибок, 
                     // которые генерирует функция, но не может самостоятельно обрабатывать искл
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
            throw 1; //для повторного создания исключения
        if (WaitForMultipleObjects(     
            2,                          // размер массива
            threads,                    // Массив
            TRUE,                       // TRUE = функция возвращает состояние всех объектов в массиве
            INFINITE) != WAIT_OBJECT_0) // WAIT_OBJECT_0 - нулевой объект
            throw 1;
    }
    catch (...) 
        //catch (...) - обработка каждого исключения
    {
        cout << "Error number: " << GetLastError();
        return 0;
    }
    return 0;
}

DWORD WINAPI thread1_2(LPVOID t) //функция потока
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
