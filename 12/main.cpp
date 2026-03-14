#include "Class.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    
    cout << "=== Тест класса CVector ===" << endl << endl;
    
    // Тест 1: Создание векторов
    cout << "Тест 1: Создание векторов" << endl;
    int size1, size2;
    cout << "Введите размер вектора 1: ";
    cin >> size1;
    
    CVector1 vector1(size1);
    cout << "Введите элементы вектора 1:" << endl;
    for (int i = 0; i < size1; ++i) {
        cout << "  элемент " << i + 1 << ": ";
        cin >> vector1[i];
    }
    
    cout << "Введите размер вектора 2: ";
    cin >> size2;
    
    CVector1 vector2(size2);
    cout << "Введите элементы вектора 2:" << endl;
    for (int i = 0; i < size2; ++i) {
        cout << "  элемент " << i + 1 << ": ";
        cin >> vector2[i];
    }
    
    cout << endl;
    
    // Тест 2: Сложение
    cout << "Тест 2: Сложение векторов" << endl;
    CVector1 sum = vector1 + vector2;
    cout << "Вектор 1: " << vector1 << endl;
    cout << "Вектор 2: " << vector2 << endl;
    cout << "Сумма: " << sum << endl << endl;
    
    // Тест 3: Вычитание
    cout << "Тест 3: Вычитание векторов" << endl;
    CVector1 difference = vector1 - vector2;
    cout << "Разность: " << difference << endl << endl;
    
    // Тест 4: Скалярное умножение
    cout << "Тест 4: Скалярное умножение" << endl;
    double scalarProduct = vector1 * vector2;
    cout << "Скалярное произведение: " << scalarProduct << endl << endl;
    
    // Тест 5: Сохранение в файл
    cout << "Тест 5: Сохранение в файл" << endl;
    const char* filename = "vector_result.txt";
    cout << "Сохранение результатов в файл: " << filename << endl;
    
    ofstream clearFile(filename, ios::out | ios::trunc);
    clearFile.close();
    
    vector1.show(filename);
    vector2.show(filename);
    sum.show(filename);
    difference.show(filename);
    cout << "Данные сохранены!" << endl << endl;
    
    // Тест 6: Загрузка из файла
    cout << "Тест 6: Загрузка из файла" << endl;
    cout << "Загружаем вектор из файла..." << endl;
    
    vector1.saveToFile("vector_load.txt");
    CVector1 loadedVector("vector_load.txt");
    
    cout << "Загруженный вектор: " << loadedVector << endl;
    cout << "Совпадает с оригиналом: " << ((vector1[0] == loadedVector[0]) ? "Да" : "Нет") << endl << endl;
    
    // Тест 7: Копирование и перемещение
    cout << "Тест 7: Копирование и перемещение" << endl;
    CVector1 copiedVector = vector1;
    cout << "Скопированный вектор: " << copiedVector << endl;
    
    CVector1 movedVector = CVector1(3);
    movedVector[0] = 10;
    movedVector[1] = 20;
    movedVector[2] = 30;
    CVector1 movedVector2 = move(movedVector);
    cout << "Перемещенный вектор: " << movedVector2 << endl << endl;
    
    cout << "=== Все тесты завершены ===" << endl;
    
    return 0;
}