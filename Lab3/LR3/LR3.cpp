/*Напишите программу для сортировки массива числовых массивов по возрастанию их длин
1.	Количество строк массива можно задать произвольно, но не менее пяти.
2.	Длина каждой строки массива генерируется случайным образом (число в диапазоне от 1 до 10), после чего для данной строки  в нужном объеме выделяется память из кучи (HeapAlloc).
3.	Заполняется массив также случайным образом числами в диапазоне от 1 до 10.
4.	Для увеличения или уменьшения объема памяти, выделенной под строку, используется HeapReAlloc.
5.	Для определения количества элементов в строке используется HeapSize.
6.	Не забудьте освободить всю выделенную память и удалить кучу.*/
#include <iostream>
#include <windows.h>
#include <ctime>
#include <cstdlib>
using namespace std;

void fsort(int* arr[], int asize, HANDLE h) 
{
    bool check = true;
    while (check)
    {
        check = false;
        for (int i = 0; i < asize - 1; i++)
            if (HeapSize(h, 0, arr[i]) > HeapSize(h, 0, arr[i + 1]))
            {
                int* tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                check = true;
            }
    }
}
void error_check(void* ptr) // Проверка на пустоту.
{
    if (ptr == NULL)
        throw 1;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    try     
    {
        HANDLE head_p = NULL;
        head_p = HeapCreate( 
            0,               // Параметры распределения кучи. 
            0x1000,          // Начальный размер кучи, в байтах. 
            0);              // Максимальный размер кучи, в байтах. 0 = куча может увеличиваться в размере.
        error_check(head_p);

        srand(time(0));

        int array_size;
        cout << "Введите размер вашего массива, который не меньше 5: ";
        cin >> array_size;
        while (array_size < 5)
        {
            cout << "Введенное значение меньше 5, повторите попытку: ";
            cin >> array_size;
        }
        int** array_p = (int**)HeapAlloc( 
            head_p,                       // Дескриптор кучи, из которой будет выделена память.
            0,                            // Параметры распределения кучи.
            array_size * sizeof(int*));   // Количество выделяемых байтов.
        for (int i = 0; i < array_size; i++)
        {
            array_p[i] = (int*)HeapAlloc( // Выделяем память под максимальную длину массива.
                head_p,
                0,
                10 * sizeof(int));
            error_check(array_p[i]);
            int length = rand() % 10 + 1;    // случайная длина
            array_p[i] = (int*)HeapReAlloc(  
                head_p,                      // Дескриптор кучи, из которой должна быть перераспределена память.
                0,                           // Параметры перераспределения кучи.
                array_p[i],                  // Указатель на блок памяти, который функция перераспределяет.
                length * sizeof(int));       // Новый размер блока памяти, в байтах. Размер блока памяти может быть увеличен или уменьшен с помощью этой функции.
            
            error_check(array_p[i]);
            
            for (int j = 0; j < length; j++) // Выводим случайно сгенерированные элементы.
            {
                cout.fill(' '); // Заполнение пустого пространства.
                cout.width(3);  // Минимальное количество символов, которые будет использовать следующие выходные значения.
                *(*(array_p + i) + j) = rand() % 10 + 1;
                array_p[i][j] = rand() % 10 + 1;
                cout << *(array_p[i] + j);
            }
            cout << endl;
        }
        for (int i = 0; i < array_size; i++) // Выводим длину каждой кучи.
        {
            SIZE_T n;
            n = HeapSize(
                head_p,      // Дескриптор кучи, в которой находится блок памяти.
                0,           // Параметры размера кучи.
                array_p[i]); // Указатель на блок памяти, размер которого получит функция.
            
            error_check(&n);
            
            if (n == 0)
            {
                cout << "Ошибка размера кучи:" << GetLastError();
                return 1;
            }
            cout << "Размер номера строки: " << i + 1 << " = " << n / sizeof(int) << endl;
        }
        fsort(array_p, array_size, head_p);
        for (int i = 0; i < array_size; i++)
        {
            for (int j = 0; j < (int)HeapSize(head_p, 0, array_p[i]) / sizeof(int); j++)
            {
                cout.fill(' ');
                cout.width(3);
                cout << *(array_p[i] + j);
            }
            cout << endl;
        }


        if (HeapDestroy(head_p) == 0)
            cout << "Ошибка удаления кучи: " << GetLastError() << endl;
        else cout << "Куча удалена" << endl;
    }
    catch (int)
    {
        cout << "Номер ошибки: " << GetLastError();
        return 1;
    }
}
