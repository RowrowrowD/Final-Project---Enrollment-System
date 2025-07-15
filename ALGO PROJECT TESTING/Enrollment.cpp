#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
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

struct Course {
    string courseCode;
    string courseTitle;
    int units;
    int yearLevel;
};

struct Enrollee {
    string studentID;
    string studentName;
    string courseCode;
};

// === Utilities (inline to prevent linker errors) ===
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

inline vector<Course> loadCourses() {
    vector<Course> courses;
    ifstream file("courses.txt");
    string line;
    while (getline(file, line)) {
        Course c;
        string unitStr, yearStr;
        stringstream ss(line);
        getline(ss, c.courseCode, '|');
        getline(ss, c.courseTitle, '|');
        getline(ss, unitStr, '|');
        getline(ss, yearStr);
        c.units = stoi(unitStr);
        c.yearLevel = stoi(yearStr);
        courses.push_back(c);
    }
    file.close();
    return courses;
}

// === Utility Function ===
bool courseAlreadyEnrolled(const string& studentID, const string& courseCode) {
    ifstream file("enrollments.txt");
    string line;
    while (getline(file, line)) {
        string id, course;
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, course);
        if (id == studentID && course == courseCode)
            return true;
    }
    return false;
}

// === Enroll a Student ===
void enrollStudent() {
    system("cls");

    vector<Student> students = loadStudents();
    vector<Course> courses = loadCourses();

    string id;
    cout << "Enter Student ID to Enroll: ";
    getline(cin, id);

    auto it = find_if(students.begin(), students.end(), [id](Student s) {
        return s.studentID == id;
    });

    if (it == students.end()) {
        cout << "Student ID not found.\n";
        return;
    }

    Student s = *it;
    cout << "\nEnrolling: " << s.lastName << ", " << s.firstName << " (" << s.studentID << ")\n";
    cout << "Year Level: " << s.yearLevel << "\n\n";

    vector<Course> eligibleCourses;
    for (const auto& c : courses) {
        if (c.yearLevel == s.yearLevel && !courseAlreadyEnrolled(s.studentID, c.courseCode)) {
            eligibleCourses.push_back(c);
        }
    }

    if (eligibleCourses.empty()) {
        cout << "No courses available for this year level or already enrolled.\n";
        return;
    }

    ofstream file("enrollments.txt", ios::app);
    for (const auto& c : eligibleCourses) {
        cout << "+------------------------------------------+\n";
        cout << "Course Code : " << c.courseCode << "\n";
        cout << "Course Title: " << c.courseTitle << "\n";
        cout << "Units       : " << c.units << "\n";
        cout << "+------------------------------------------+\n";
        cout << "Enroll in this subject? (Y/N): ";
        char confirm;
        cin >> confirm;
        cin.ignore();
        if (toupper(confirm) == 'Y') {
            file << s.studentID << "|" << c.courseCode << endl;
            cout << "Enrolled.\n\n";
        }
    }

    file.close();
    cout << "\nEnrollment completed.\n";
}

// === View Enrollees ===
void viewEnrollees() {
    system("cls");

    vector<Student> students = loadStudents();
    vector<Course> courses = loadCourses();
    ifstream file("enrollments.txt");
    string line;

    vector<Enrollee> data;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, code;
        getline(ss, id, '|');
        getline(ss, code);

        string fullName = "N/A";
        for (const auto& s : students) {
            if (s.studentID == id) {
                fullName = s.lastName + ", " + s.firstName + " " + s.middleName;
                break;
            }
        }

        Enrollee e;
        e.studentID = id;
        e.studentName = fullName;
        e.courseCode = code;
        data.push_back(e);
    }
    file.close();

    if (data.empty()) {
        cout << "No enrollment records found.\n";
        return;
    }

    cout << "+------------+-------------------------------+-------------+\n";
    cout << "| Student ID | Student Name                  | Course Code |\n";
    cout << "+------------+-------------------------------+-------------+\n";
    for (const auto& entry : data) {
        cout << "| " << setw(10) << left << entry.studentID
             << " | " << setw(29) << left << entry.studentName
             << " | " << setw(11) << left << entry.courseCode
             << " |\n";
    }
    cout << "+------------+-------------------------------+-------------+\n";
}

// === Enrollment Menu ===
void enrollmentMenu() {
    char choice;
    do {
        system("cls");
        cout << "===========================\n";
        cout << "      ENROLLMENT MENU     \n";
        cout << "===========================\n";
        cout << "[1] Enroll a Student\n";
        cout << "[2] View List of Enrollees\n";
        cout << "[X] Return to Main Menu\n";
        cout << "---------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (toupper(choice)) {
            case '1': enrollStudent(); break;
            case '2': viewEnrollees(); break;
            case 'X': return;
            default: cout << "Invalid input.\n"; break;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    } while (true);
}

