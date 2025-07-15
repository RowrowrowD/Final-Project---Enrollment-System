#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;

void enrollmentMenu();
void studentManagementMenu();
void scheduleManagementMenu();
void courseManagementMenu();
void displayTutorial();
void exitProgram();

int main() {
    char choice;

    while (true) {
        system("cls");
        cout << "+===========================================================+\n";
        cout << "|        WELCOME TO GROUPNAME SCHOOL ENROLLMENT SYSTEM     |\n";
        cout << "+===========================================================+\n";
        cout << "| [1] Enrollment Menu                                       |\n";
        cout << "| [2] Student Management                                    |\n";
        cout << "| [3] Schedule Management                                   |\n";
        cout << "| [4] Course Management                                     |\n";
        cout << "| [T] Tutorial (System Usage Guide)                         |\n";
        cout << "| [X] Exit Program                                          |\n";
        cout << "+===========================================================+\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (toupper(choice)) {
            case '1':
                enrollmentMenu();
                break;
            case '2':
                studentManagementMenu();
                break;
            case '3':
                scheduleManagementMenu();
                break;
            case '4':
                courseManagementMenu();
                break;
            case 'T':
                displayTutorial();
                break;
            case 'X':
                exitProgram();
                return 0;
            default:
                cout << "\nInvalid input. Please select a valid option.\n";
                cout << "Press Enter to return to the menu...";
                cin.get();
        }
    }

    return 0;
}













