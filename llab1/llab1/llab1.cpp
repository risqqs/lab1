// llab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

using namespace std;

struct Pipe {
    string name;
    double length = 0;
    double diameter = 0;
    bool repair = false;
};

struct Station {
    string name;
    int shops = 0;
    int working = 0;
    double grade = 0;
};

int getInt() {
    int n;
    while (true) {
        cin >> n;
        if (cin.fail() || n <= 0) {
            cout << "Error: enter positive integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n;
        }
    }

double getDouble() {
    double n;
    while (true) {
        cin >> n;
        if (cin.fail() || n <= 0) {
            cout << "Error: enter positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n;
        }
    }
}

bool getBool() {
    int n;
    while (true) {
        cin >> n;
        if (cin.fail() || (n != 0 && n != 1)) {
            cout << "Error: enter 0 (no) or 1 (yes): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return n == 1;
        }
    }
}

void addPipe(Pipe& p) {
    cout << "Enter pipe location: ";
    getline(cin >> ws, p.name);
    cout << "Enter length (km): ";
    p.length = getDouble();
    cout << "Enter diameter (mm): ";
    p.diameter = getDouble();
    cout << "Under repair? (0-no, 1-yes): ";
    p.repair = getBool();
}

void showPipe(const Pipe& p) {
    cout << "\n--- Pipe ---" << endl;
    cout << "Location: " << p.name << endl;
    cout << "Length: " << p.length << " km" << endl;
    cout << "Diameter: " << p.diameter << " mm" << endl;
    cout << "Repair: " << (p.repair ? "Yes" : "No") << endl;
}

void editPipe(Pipe& p) {
    if (p.name.empty()) {
        cout << "Error: no pipe" << endl;
        return;
    }
    cout << "Current repair: " << (p.repair ? "Yes" : "No") << endl;
    cout << "Enter new status (0-no, 1-yes): ";
    p.repair = getBool();
    cout << "Updated" << endl;
}

int main()
{
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
