#include "task2.h"

void printLastFileError(HANDLE h_file, const std::string& message_after_error = "") {
	int error;
	if ((error = GetLastError()) != 0) {
		std::cout << error << ": " << message_after_error << std::endl;
		CloseHandle(h_file);
		exit(1);
	}
}

void cutData(LPCWSTR source_filename, LONG position, LPCWSTR destination_filename) {

	// Создание файлп для чтения
	HANDLE h_file = CreateFile(
		source_filename,// путь к файлу
		GENERIC_READ,// только чтение 
		0, // режим разделения доступа
		NULL, // не наследуется
		OPEN_EXISTING,// открывает существующий файл
		FILE_FLAG_DELETE_ON_CLOSE,//  удаляет файл после закрытия дескриптора
		NULL// шаблона нет
	);
	
	printLastFileError(h_file, "when setting handle to source_file");

	// перемещает указатель в открытом файле
	SetFilePointer(h_file,// наш файл 
		position, // шаг считывания файла
		NULL, // усложнение шага считывания файла
		FILE_BEGIN// читать с начала файла
	);
	printLastFileError(h_file, "when setting pointer in source_file");

	DWORD buff, num_of_read_bytes;
	// читаем файл
	ReadFile(h_file,// наш файл 
		&buff, // буфер данных
		sizeof(buff),//  количество байт для прочтения
		&num_of_read_bytes,//  количество фактически прочитанных байт
		NULL// усложнение для асинхронного чтения
	);
	std::cout << "read_bytes: " << num_of_read_bytes << "\n";// DEBUG
	printLastFileError(h_file, "when reading source_file");

	// закрытие дескриптора нашего файла
	CloseHandle(h_file);


	// открываем пустой файл для записи
	h_file = CreateFile(destination_filename,
		GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
	);
	printLastFileError(h_file, "when setting handle to destination_file");

	DWORD num_of_written_bytes;
	
	WriteFile(h_file,// наш файл
		&buff, // буфер данных
		num_of_read_bytes,//кол-во байтов для записи  
		&num_of_written_bytes,// кол-во фактичеки записанных байтов
		NULL// усложнение для асинхронного чтения
	);
	std::cout << "written_bytes: " << num_of_written_bytes << "\n";  // DEBUG
	printLastFileError(h_file, "when writing destination_file");

	// закрытие дескриптора нашего файла
	CloseHandle(h_file);
}

void task2() {
	string s;
	std::cout << "Введите путь source файла"
	// указываем пути наших файлов
	LPCWSTR source_file = getline (cin, s);
	
	std::cout << "Введите путь test файла"
	LPCWSTR destin_file = getline (cin, s);;

	cutData(source_file, 1, destin_file);
}