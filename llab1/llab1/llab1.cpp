// llab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

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

void addStation(Station& s) {
    cout << "Enter station name: ";
    getline(cin >> ws, s.name);
    cout << "Enter total shops: ";
    s.shops = getInt();
    cout << "Enter working shops: ";
    s.working = getInt();

    while (s.working > s.shops) {
        cout << "Error: working shops > total" << endl;
        cout << "Enter working shops: ";
        s.working = getInt();
    }

    cout << "Enter station grade: ";
    s.grade = getDouble();
}

void showStation(const Station& s) {
    cout << "\n--- Station ---" << endl;
    cout << "Name: " << s.name << endl;
    cout << "Total shops: " << s.shops << endl;
    cout << "Working shops: " << s.working << endl;
    cout << "Grade: " << s.grade << endl;
}

void editStation(Station& s) {
    if (s.name.empty()) {
        cout << "Error: no station" << endl;
        return;
    }

    cout << "Current: " << s.working << " of " << s.shops << " working" << endl;
    cout << "Enter new working shops: ";
    int n = getInt();

    while (n > s.shops) {
        cout << "Error: working shops > total" << endl;
        cout << "Enter working shops: ";
        n = getInt();
    }

    s.working = n;
    cout << "Updated" << endl;
}

void saveFile(const Pipe& p, const Station& s, const string& name) {
    ofstream file(name);
    if (!file.is_open()) {
        cout << "Error: cannot save" << endl;
        return;
    }

    file << "Pipe" << endl;
    file << p.name << endl;
    file << p.length << endl;
    file << p.diameter << endl;
    file << p.repair << endl;

    file << "Station" << endl;
    file << s.name << endl;
    file << s.shops << endl;
    file << s.working << endl;
    file << s.grade << endl;

    file.close();
    cout << "Saved: " << name << endl;
}

void loadFile(Pipe& p, Station& s, const string& name) {
    ifstream file(name);
    if (!file.is_open()) {
        cout << "Error: cannot load" << endl;
        return;
    }

    string line;

    getline(file, line);
    if (line != "Pipe") {
        cout << "Error: wrong format" << endl;
        file.close();
        return;
    }

    getline(file >> ws, p.name);
    file >> p.length >> p.diameter >> p.repair;
    file.ignore();

    getline(file, line);
    if (line != "Station") {
        cout << "Error: wrong format" << endl;
        file.close();
        return;
    }

    getline(file >> ws, s.name);
    file >> s.shops >> s.working >> s.grade;

    if (s.working > s.shops) {
        s.working = s.shops;
    }

    file.close();
    cout << "Loaded: " << name << endl;
}

void showAll(const Pipe& p, const Station& s) {
    if (p.name.empty() && s.name.empty()) {
        cout << "No data" << endl;
        return;
    }

    if (!p.name.empty()) {
        showPipe(p);
    }

    if (!s.name.empty()) {
        showStation(s);
    }
}

void menu() {
    Pipe p;
    Station s;
    int n;
    string name;

    while (true) {
        cout << "\n=== Menu ===" << endl;
        cout << "1. Add pipe" << endl;
        cout << "2. Add station" << endl;
        cout << "3. View all" << endl;
        cout << "4. Edit pipe" << endl;
        cout << "5. Edit station" << endl;
        cout << "6. Save" << endl;
        cout << "7. Load" << endl;
        cout << "0. Exit" << endl;
        cout << "Choose: ";

        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (n) {
        case 1: addPipe(p); break;
        case 2: addStation(s); break;
        case 3: showAll(p, s); break;
        case 4: editPipe(p); break;
        case 5: editStation(s); break;
        case 6:
            if (p.name.empty() || s.name.empty()) {
                cout << "Error: add pipe and station first" << endl;
            }
            else {
                cout << "Enter filename: ";
                getline(cin, name);
                saveFile(p, s, name);
            }
            break;
        case 7:
            cout << "Enter filename: ";
            getline(cin, name);
            loadFile(p, s, name);
            break;
        case 0:
            cout << "Exit" << endl;
            return;
        default:
            cout << "Error: wrong choice" << endl;
            break;
        }
    }
}

int main()
{
    menu();
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
