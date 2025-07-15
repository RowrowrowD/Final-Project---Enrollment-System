#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

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

// === Shared Utility Functions ===

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}

string toUpper(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

vector<Student> loadStudents() {
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

vector<Course> loadCourses() {
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

