#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum MountainType {
    VOLCANO,
    FOLDED,
    PLATEAU,
    OTHER
};

const string mountNames[] = {"Вулканическая", "Складчатая", "Платообразная", "Другая"};

struct MountLocation {
    char country[50];
    MountainType type;
};

struct Mountain {
    char name[50];
    int height;
    MountLocation location;
};

const int mountCount = 20;

void printMount(Mountain m) {
    cout << "Название: " << m.name
         << ", Высота: " << m.height
         << ", Страна: " << m.location.country
         << ", Тип: " << mountNames[m.location.type]
         << endl;
}

void calcAndPrintAverage(Mountain arr[]) {
    double sum = 0;
    for (int i = 0; i < mountCount; i++) {
        sum += arr[i].height;
    }
    cout << "Средняя высота всех 20 вершин: " << sum / mountCount << " м" << endl;
}

void sort(Mountain arr[]) {
    for (int i = 0; i < mountCount - 1; i++) {
        for (int j = 0; j < mountCount - i - 1; j++) {
            if (arr[j].height > arr[j + 1].height) {
                Mountain temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printVosmitisach(Mountain arr[]) {
    cout << "Страны местонахождения 3-х восьмитысячников:" << endl;
    int count = 0;
    for (int i = 0; i < mountCount; i++) {
        if (arr[i].height >= 8000) {
            cout << count + 1 << ". " << arr[i].name << " - " << arr[i].location.country << endl;
            count++;
            if (count == 3) break;
        }
    }
}

void changeMountainByHeight(Mountain arr[]) {
    int searchHeight;
    cout << "Введите высоту горы для изменения: ";
    cin >> searchHeight;

    for (int i = 0; i < mountCount; i++) {
        if (arr[i].height == searchHeight) {
            cout << "Введите новые данные" << endl;
            cout << "Название: ";
            cin >> arr[i].name;
            cout << "Высота: ";
            cin >> arr[i].height;
            cout << "Страна: ";
            cin >> arr[i].location.country;
            arr[i].location.type = OTHER;

            cout << "Данные успешно изменены" << endl;
            return;
        }
    }
    cout << "Гора с такой высотой не найдена." << endl;
}

void printFilteredMountains(Mountain filteredArr[], int count, string country) {
    cout << "Горные вершины в стране " << country << ":" << endl;
    if (count == 0) {
        cout << "Не найдено" << endl;
    } else {
        for (int i = 0; i < count; i++) {
            printMount(filteredArr[i]);
        }
    }
}

void filterByCountry(Mountain arr[]) {
    string searchCountry;
    cout << "Введите страну для поиска: ";
    cin >> searchCountry;

    Mountain filteredArr[mountCount];
    int filteredCount = 0;

    for (int i = 0; i < mountCount; i++) {
        if (arr[i].location.country == searchCountry) {
            filteredArr[filteredCount] = arr[i];
            filteredCount++;
        }
    }

    printFilteredMountains(filteredArr, filteredCount, searchCountry);
}

void updateHeightsFromTextFile(Mountain arr[], string filename) {
    ifstream fin;
    fin.open(filename);

    if (fin.is_open()) {
        string searchName;
        int newHeight;

        while (!fin.eof()) {
            fin >> searchName >> newHeight;

            for (int i = 0; i < mountCount; i++) {
                if (arr[i].name == searchName) {
                    arr[i].height = newHeight;
                    break;
                }
            }
        }
    }
    fin.close();
}

void saveToBinaryFile(Mountain arr[], string filename) {
    ofstream out(filename, ios::binary | ios::out);

    if (out.is_open()) {
        out.write((char*)arr, sizeof(Mountain) * mountCount);
    }
    out.close();
}

void loadFromBinaryFile(Mountain arr[], string filename) {
    fstream in(filename, ios::binary | ios::in);

    if (in.is_open()) {
        in.read((char*)arr, sizeof(Mountain) * mountCount);
    }
    in.close();
}

int main() {
    setlocale(LC_ALL, "ru");

    Mountain mountains[mountCount] = {
        {"Эверест", 8848, {"Китай", FOLDED}},
        {"Чогори", 8611, {"Пакистан", FOLDED}},
        {"Канченджанга", 8586, {"Непал", FOLDED}},
        {"Лхоцзе", 8516, {"Непал", FOLDED}},
        {"Макалу", 8485, {"Непал", FOLDED}},
        {"Чо-Ойю", 8188, {"Китай", FOLDED}},
        {"Дхаулагири", 8167, {"Непал", FOLDED}},
        {"Манаслу", 8163, {"Непал", FOLDED}},
        {"Нангапарбат", 8126, {"Пакистан", FOLDED}},
        {"Аннапурна", 8091, {"Непал", FOLDED}},
        {"Эльбрус", 5642, {"Россия", VOLCANO}},
        {"Монблан", 4809, {"Франция", FOLDED}},
        {"Килиманджаро", 5895, {"Танзания", VOLCANO}},
        {"Денали", 6190, {"США", FOLDED}},
        {"Аконкагуа", 6960, {"Аргентина", FOLDED}},
        {"Фудзияма", 3776, {"Япония", VOLCANO}},
        {"Арарат", 5165, {"Турция", VOLCANO}},
        {"Везувий", 1281, {"Италия", VOLCANO}},
        {"Этна", 3357, {"Италия", VOLCANO}},
        {"Олимп", 2917, {"Греция", OTHER}}
    };
    string filename = "text.txt";
    int choice;

    do {
        cout << "1. Вывести среднюю высоту всех вершин" << endl;
        cout << "2. Отсортировать вершины по возрастанию высоты и вывести" << endl;
        cout << "3. Вывести страны трех восьмитысячников" << endl;
        cout << "4. Изменить данные горы (по высоте)" << endl;
        cout << "5. Найти горы по стране" << endl;
        cout << "6. Считать данные из файла" << endl;
        cout << "7. Считать данные из бинарного файла" << endl;
        cout << "8. Записать данные в бинарный файл" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1:
                calcAndPrintAverage(mountains);
                break;
            case 2:
                sort(mountains);
                cout << "Данные отсортированы" << endl;
                for (int i = 0; i < mountCount; i++) {
                    printMount(mountains[i]);
                }
                break;
            case 3:
                printVosmitisach(mountains);
                break;
            case 4:
                changeMountainByHeight(mountains);
                break;
            case 5:
                filterByCountry(mountains);
                break;
            case 6:
                updateHeightsFromTextFile(mountains, filename);
                break;
            case 7:
                loadFromBinaryFile(mountains, filename);
                break;
            case 8:
                saveToBinaryFile(mountains, filename);
                break;
            case 0:
                cout << "Завершение программы" << endl;
                break;
            default:
                cout << "Неверный ввод, попробуйте еще раз" << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}