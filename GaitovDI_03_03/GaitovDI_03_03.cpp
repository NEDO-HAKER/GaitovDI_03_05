#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian"); // Настройка для корректного вывода в консоли

    const char* SEM_NAME = "Global\\UniqueAppSemaphore2026"; // Уникальное имя именованного семафора

    HANDLE hSemaphore = CreateSemaphoreA(NULL, 2, 2, SEM_NAME); // Создание или открытие именованного семафора с начальным и максимальным значением 2

    if (hSemaphore == NULL) 
    {
        cerr << "CreateSemaphore failed, error: " << GetLastError() << endl;
        ExitProcess(1);
    } // Проверка успешности создания семафора

    DWORD result = WaitForSingleObject(hSemaphore, 0); // Попытка захватить семафор без ожидания (таймаут 0 мс)

    if (result == WAIT_TIMEOUT)
    {
        cout << "Превышено допустимое количество копий программы. Завершение работы." << endl;
        CloseHandle(hSemaphore);
        ExitProcess(0);
    } // Обработка случая, когда все слоты семафора заняты (запущено уже 2 экземпляра)

    if (result != WAIT_OBJECT_0)
    {
        cerr << "WaitForSingleObject failed, error: " << GetLastError() << endl;
        CloseHandle(hSemaphore);
        ExitProcess(1);
    } // Обработка прочих ошибок ожидания семафора

    cout << "Программа успешно запущена. Нажмите Enter для завершения." << endl;
    cin.get(); // Основная работа программы — ожидание ввода пользователя

    ReleaseSemaphore(hSemaphore, 1, NULL);
    CloseHandle(hSemaphore); // Освобождение слота семафора и закрытие его дескриптора

    cout << "Семафор освобожден." << endl;
    ExitProcess(0); // Информационное сообщение и корректное завершение процесса
}