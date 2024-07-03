
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

class Student {
public:
    string name;
    string nameSpecialty;
    int numberGroup;
    int averagePoint;

    Student() {};
    Student(string name, string nameSpecialty, int numberGroup, int averagePoint) :
        name(name), nameSpecialty(nameSpecialty), numberGroup(numberGroup), averagePoint(averagePoint) {}

    string toString() const {
        return name + "; " + nameSpecialty + "; " + to_string(numberGroup) + "; " + to_string(averagePoint);
    }

    static Student fromString(const string& str) {
        Student student;
        stringstream ss(str);
        
        getline(ss, student.name, ';');
        getline(ss, student.nameSpecialty, ';');
        ss >> student.numberGroup;
        ss.ignore();
        ss >> student.averagePoint;

        return student;
    }

};

void writeToFile(const string& filename, const vector<Student>& students) {
    ofstream outFile(filename);

    for (const auto& student : students) {
        outFile << student.toString() << endl;
    }
}

vector<Student> readFromFile(const string& filename) {
    ifstream inFile(filename);
    vector<Student> students;
    string line;
    while (getline(inFile, line)) {
        students.push_back(Student::fromString(line));
    }

    return students;
}

bool compareByNameAsc(const Student& a, const Student& b) {
    return a.name < b.name;
}

bool compareByNameDesc(const Student& a, const Student& b) {
    return a.name > b.name;
}

void addStudent(vector<Student>& students) {
    string name, nameSpecialty;
    int numberGroup;
    double averagePoint;
    cout << "!!!Ввод английскими символами!!!" << endl;
    cout << "Введите имя: " << endl;
    cin.ignore();
    getline(cin, name);
    cout << "Введите специальность(PR, DZ и т.п.): " << endl;
    getline(cin, nameSpecialty);
    cout << "Введите номер группы: " << endl;
    cin >> numberGroup;
    cout << "Введите средний балл целым числом: " << endl;
    cin >> averagePoint;

    Student student(name, nameSpecialty, numberGroup, averagePoint);
    students.push_back(student);
}

int main()
{
    setlocale(LC_ALL, "ru");
    vector<Student> students;
    string filename("students.txt");

    int choice;

    cout << "1. Добавить нового студента" << endl;
    cout << "2. Вывести всех студентов" << endl;
    cout << "3. Отсортировать по возрастанию" << endl;
    cout << "4. Отсортировать по убыванию" << endl;
    cout << "5. Выход";
    cout << "Введите номер нужного пункта: " << endl;

    cin >> choice;

    while (choice != 5) {
        switch (choice) {
        case 1: {
            addStudent(students);
            writeToFile(filename, students);
            break;
        }
        case 2: {
            students = readFromFile(filename);
            for (const auto& student : students) {
                cout << student.toString() << endl;
            }
            break;
        }
        case 3: {
            students = readFromFile(filename);
            sort(students.begin(), students.end(), compareByNameAsc);
            writeToFile(filename, students);
            break;
        }
        case 4: {
            students = readFromFile(filename);
            sort(students.begin(), students.end(), compareByNameDesc);
            writeToFile(filename, students);
            break;
        }
        case 5: {
            exit(0);
            break;
        }
        default: {
            cout << "Неверный ввод. Повторите попытку";
            break;
        }
        }
        cout << "Введите номер нужного пункта: ";
        cin >> choice;
    }
    
    return 0;

}
