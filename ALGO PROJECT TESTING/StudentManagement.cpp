#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;

struct Student {
    string studentID;
    string lastName;
    string firstName;
    string middleName;
    string gender;
    string birthday;
    string address;
    string degreeProgram;
    int yearLevel;
};

// === Inline Shared Functions ===
inline string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

inline string toUpper(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

inline vector<Student> loadStudents() {
    vector<Student> students;
    ifstream file("students.txt");
    string line;
    while (getline(file, line)) {
        Student s;
        stringstream ss(line);
        string yearStr;
        getline(ss, s.studentID, '|');
        getline(ss, s.lastName, '|');
        getline(ss, s.firstName, '|');
        getline(ss, s.middleName, '|');
        getline(ss, s.gender, '|');
        getline(ss, s.birthday, '|');
        getline(ss, s.address, '|');
        getline(ss, s.degreeProgram, '|');
        getline(ss, yearStr);
        s.yearLevel = stoi(yearStr);
        students.push_back(s);
    }
    file.close();
    return students;
}

// === New: Auto-generate student ID ===
inline string getNextStudentID() {
    ifstream file("students.txt");
    string lastID = "20250000";
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id;
        getline(ss, id, '|');
        if (!id.empty()) {
            lastID = id;
        }
    }
    file.close();
    int nextID = stoi(lastID) + 1;
    return to_string(nextID);
}

// === Save Students ===
void saveStudents(const vector<Student>& students) {
    ofstream file("students.txt");
    for (const auto& s : students) {
        file << s.studentID << "|" << s.lastName << "|" << s.firstName << "|" << s.middleName << "|"
             << s.gender << "|" << s.birthday << "|" << s.address << "|" << s.degreeProgram << "|"
             << s.yearLevel << "\n";
    }
    file.close();
}

// === Add Student ===
void addStudent() {
    system("cls");

    Student s;
    s.studentID = getNextStudentID();
    cout << "Generated Student ID: " << s.studentID << "\n";

    cout << "Enter Last Name: ";
    getline(cin, s.lastName);

    cout << "Enter First Name: ";
    getline(cin, s.firstName);

    cout << "Enter Middle Name: ";
    getline(cin, s.middleName);

    cout << "Enter Gender (Male/Female): ";
    getline(cin, s.gender);

    cout << "Enter Birthday (YYYY-MM-DD): ";
    getline(cin, s.birthday);

    cout << "Enter Address: ";
    getline(cin, s.address);

    cout << "Enter Degree Program: ";
    getline(cin, s.degreeProgram);

    cout << "Enter Year Level (1–4): ";
    cin >> s.yearLevel;
    cin.ignore();

    // Save
    ofstream file("students.txt", ios::app);
    file << s.studentID << "|" << s.lastName << "|" << s.firstName << "|" << s.middleName << "|"
         << s.gender << "|" << s.birthday << "|" << s.address << "|" << s.degreeProgram << "|"
         << s.yearLevel << "\n";
    file.close();

    cout << "\nStudent added successfully.\n";
}

// === View Student List ===
void viewStudents() {
    system("cls");
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "No student records available.\n";
        return;
    }

    sort(students.begin(), students.end(), [](Student a, Student b) {
        return a.studentID < b.studentID;
    });

    cout << "+------------+-------------------------------+\n";
    cout << "| Student ID | Full Name                     |\n";
    cout << "+------------+-------------------------------+\n";
    for (const auto& s : students) {
        string fullName = s.lastName + ", " + s.firstName + " " + s.middleName;
        cout << "| " << setw(10) << left << s.studentID
             << " | " << setw(29) << left << fullName << " |\n";
    }
    cout << "+------------+-------------------------------+\n";
}

// === Edit Student ===
void editStudent() {
    system("cls");
    vector<Student> students = loadStudents();
    string id;
    cout << "Enter Student ID to Edit: ";
    getline(cin, id);

    auto it = find_if(students.begin(), students.end(), [&](Student s) {
        return s.studentID == id;
    });

    if (it == students.end()) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Editing student: " << it->studentID << "\n";

    cout << "Enter New Last Name: ";
    getline(cin, it->lastName);
    cout << "Enter New First Name: ";
    getline(cin, it->firstName);
    cout << "Enter New Middle Name: ";
    getline(cin, it->middleName);
    cout << "Enter New Gender: ";
    getline(cin, it->gender);
    cout << "Enter New Birthday: ";
    getline(cin, it->birthday);
    cout << "Enter New Address: ";
    getline(cin, it->address);
    cout << "Enter New Degree Program: ";
    getline(cin, it->degreeProgram);
    cout << "Enter New Year Level: ";
    cin >> it->yearLevel;
    cin.ignore();

    saveStudents(students);
    cout << "Student information updated.\n";
}

// === Delete Student ===
void deleteStudent() {
    system("cls");
    vector<Student> students = loadStudents();
    string id;
    cout << "Enter Student ID to Delete: ";
    getline(cin, id);

    auto it = remove_if(students.begin(), students.end(), [&](Student s) {
        return s.studentID == id;
    });

    if (it == students.end()) {
        cout << "Student not found.\n";
        return;
    }

    students.erase(it, students.end());
    saveStudents(students);
    cout << "Student deleted successfully.\n";
}

// === Student Management Menu ===
void studentManagementMenu() {
    char choice;
    do {
        system("cls");
        cout << "=============================\n";
        cout << "   STUDENT MANAGEMENT MENU  \n";
        cout << "=============================\n";
        cout << "[1] Add Student\n";
        cout << "[2] View Student List\n";
        cout << "[3] Edit Student\n";
        cout << "[4] Delete Student\n";
        cout << "[X] Return to Main Menu\n";
        cout << "-----------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (toupper(choice)) {
            case '1': addStudent(); break;
            case '2': viewStudents(); break;
            case '3': editStudent(); break;
            case '4': deleteStudent(); break;
            case 'X': return;
            default: cout << "Invalid choice.\n"; break;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    } while (true);
}

