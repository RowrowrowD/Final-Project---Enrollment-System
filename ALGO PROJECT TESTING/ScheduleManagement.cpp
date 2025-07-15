#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

struct Course {
    string courseCode;
    string courseTitle;
    int units;
    int yearLevel;
};

struct Schedule {
    string courseCode;
    string courseTitle;
    int units;
    int yearLevel;
    string section;
    string day;
    string time;
    string room;
};

// === Loaders ===
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

vector<Schedule> loadSchedules() {
    vector<Schedule> schedules;
    ifstream file("schedules.txt");
    string line;
    while (getline(file, line)) {
        Schedule s;
        string unitStr, yearStr;
        stringstream ss(line);
        getline(ss, s.courseCode, '|');
        getline(ss, s.courseTitle, '|');
        getline(ss, unitStr, '|');
        getline(ss, yearStr, '|');
        getline(ss, s.section, '|');
        getline(ss, s.day, '|');
        getline(ss, s.time, '|');
        getline(ss, s.room);
        s.units = stoi(unitStr);
        s.yearLevel = stoi(yearStr);
        schedules.push_back(s);
    }
    file.close();
    return schedules;
}

// === Add Schedule ===
void addSchedule() {
    system("cls");
    vector<Course> courses = loadCourses();
    vector<Schedule> schedules = loadSchedules();

    string courseCode;
    cout << "Enter Course Code: ";
    getline(cin, courseCode);

    auto it = find_if(courses.begin(), courses.end(), [&](Course c) {
        return c.courseCode == courseCode;
    });

    if (it == courses.end()) {
        cout << "Course not found.\n";
        return;
    }

    string section, day, time, room;
    cout << "Enter Section: ";
    getline(cin, section);
    cout << "Enter Day (e.g. MWF/TTH): ";
    getline(cin, day);
    cout << "Enter Time (e.g. 8:00AM - 9:30AM): ";
    getline(cin, time);
    cout << "Enter Room: ";
    getline(cin, room);

    // Prevent duplicate schedule (same course and section)
    for (const auto& s : schedules) {
        if (s.courseCode == courseCode && s.section == section) {
            cout << "Schedule for this course and section already exists.\n";
            return;
        }
    }

    ofstream file("schedules.txt", ios::app);
    file << it->courseCode << "|" << it->courseTitle << "|" << it->units << "|"
         << it->yearLevel << "|" << section << "|" << day << "|" << time << "|" << room << "\n";
    file.close();

    cout << "\nSchedule added successfully.\n";
}

// === View Schedules ===
void viewSchedules() {
    system("cls");
    vector<Schedule> schedules = loadSchedules();

    if (schedules.empty()) {
        cout << "No schedules available.\n";
        return;
    }

    sort(schedules.begin(), schedules.end(), [](Schedule a, Schedule b) {
        return a.courseCode < b.courseCode;
    });

    cout << "+------------+--------------------------------------------+-------+------+---------+--------+--------------------+-----------+\n";
    cout << "| Code       | Course Title                               | Units | Year | Section | Day    | Time               | Room      |\n";
    cout << "+------------+--------------------------------------------+-------+------+---------+--------+--------------------+-----------+\n";
    for (const auto& s : schedules) {
        cout << "| " << setw(10) << left << s.courseCode
             << " | " << setw(42) << left << s.courseTitle
             << " | " << setw(5)  << left << s.units
             << " | " << setw(4)  << left << s.yearLevel
             << " | " << setw(7)  << left << s.section
             << " | " << setw(6)  << left << s.day
             << " | " << setw(18) << left << s.time
             << " | " << setw(9)  << left << s.room << " |\n";
    }
    cout << "+------------+--------------------------------------------+-------+------+---------+--------+--------------------+-----------+\n";
}

// === Schedule Menu ===
void scheduleManagementMenu() {
    char choice;
    do {
        system("cls");
        cout << "=============================\n";
        cout << "   SCHEDULE MANAGEMENT MENU \n";
        cout << "=============================\n";
        cout << "[1] Add Schedule\n";
        cout << "[2] View Schedules\n";
        cout << "[X] Return to Main Menu\n";
        cout << "-----------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (toupper(choice)) {
            case '1': addSchedule(); break;
            case '2': viewSchedules(); break;
            case 'X': return;
            default: cout << "Invalid input.\n"; break;
        }

        cout << "\nPress Enter to continue...";
        cin.get();
    } while (true);
}

