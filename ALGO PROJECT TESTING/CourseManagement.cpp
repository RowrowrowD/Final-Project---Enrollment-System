#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cctype>
using namespace std;

struct Course {
    string courseCode;
    string courseTitle;
    int units;
    int yearLevel;
};

// === Inline Utility Functions ===
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

void saveCourses(const vector<Course>& courses) {
    ofstream file("courses.txt");
    for (const auto& c : courses) {
        file << c.courseCode << "|" << c.courseTitle << "|" << c.units << "|" << c.yearLevel << "\n";
    }
    file.close();
}

// === Add Course ===
void addCourse() {
    system("cls");
    vector<Course> courses = loadCourses();

    Course c;
    cout << "Enter Course Code: ";
    getline(cin, c.courseCode);
    c.courseCode = toUpper(trim(c.courseCode));

    auto it = find_if(courses.begin(), courses.end(), [&](Course x) {
        return x.courseCode == c.courseCode;
    });

    if (it != courses.end()) {
        cout << "Course code already exists.\n";
        return;
    }

    cout << "Enter Course Title: ";
    getline(cin, c.courseTitle);
    cout << "Enter Units: ";
    cin >> c.units;
    cin.ignore();
    cout << "Enter Year Level (1-4): ";
    cin >> c.yearLevel;
    cin.ignore();

    courses.push_back(c);
    saveCourses(courses);

    cout << "\nCourse added successfully.\n";
}

// === View Courses ===
void viewCourses() {
    system("cls");
    vector<Course> courses = loadCourses();

    if (courses.empty()) {
        cout << "No courses available.\n";
        return;
    }

    sort(courses.begin(), courses.end(), [](Course a, Course b) {
        return a.courseCode < b.courseCode;
    });

    cout << "+------------+--------------------------------------------+-------+------+\n";
    cout << "| Code       | Course Title                               | Units | Year |\n";
    cout << "+------------+--------------------------------------------+-------+------+\n";
    for (const auto& c : courses) {
        cout << "| " << setw(10) << left << c.courseCode
             << " | " << setw(42) << left << c.courseTitle
             << " | " << setw(5)  << left << c.units
             << " | " << setw(4)  << left << c.yearLevel << " |\n";
    }
    cout << "+------------+--------------------------------------------+-------+------+\n";
}

// === Edit Course ===
void editCourse() {
    system("cls");
    vector<Course> courses = loadCourses();

    string code;
    cout << "Enter Course Code to Edit: ";
    getline(cin, code);
    code = toUpper(trim(code));

    auto it = find_if(courses.begin(), courses.end(), [&](Course c) {
        return c.courseCode == code;
    });

    if (it == courses.end()) {
        cout << "Course not found.\n";
        return;
    }

    cout << "Editing Course: " << it->courseCode << " - " << it->courseTitle << "\n";

    cout << "Enter New Title: ";
    getline(cin, it->courseTitle);
    cout << "Enter New Units: ";
    cin >> it->units;
    cin.ignore();
    cout << "Enter New Year Level: ";
    cin >> it->yearLevel;
    cin.ignore();

    saveCourses(courses);
    cout << "Course updated successfully.\n";
}

// === Delete Course ===
void deleteCourse() {
    system("cls");
    vector<Course> courses = loadCourses();

    string code;
    cout << "Enter Course Code to Delete: ";
    getline(cin, code);
    code = toUpper(trim(code));

    auto it = remove_if(courses.begin(), courses.end(), [&](Course c) {
        return c.courseCode == code;
    });

    if (it == courses.end()) {
        cout << "Course not found.\n";
        return;
    }

    courses.erase(it, courses.end());
    saveCourses(courses);
    cout << "Course deleted successfully.\n";
}

// === Course Management Menu ===
void courseManagementMenu() {
    char choice;
    do {
        system("cls");
        cout << "==========================\n";
        cout << "   COURSE MANAGEMENT MENU \n";
        cout << "==========================\n";
        cout << "[1] Add Course\n";
        cout << "[2] View Courses\n";
        cout << "[3] Edit Course\n";
        cout << "[4] Delete Course\n";
        cout << "[X] Return to Main Menu\n";
        cout << "--------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (toupper(choice)) {
            case '1': addCourse(); break;
            case '2': viewCourses(); break;
            case '3': editCourse(); break;
            case '4': deleteCourse(); break;
            case 'X': return;
            default: cout << "Invalid input.\n"; break;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    } while (true);
}

