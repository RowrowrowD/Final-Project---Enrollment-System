#include <iostream>
using namespace std;

void displayTutorial() {
    system("cls");
    cout << "+===============================================================+\n";
    cout << "|                   SYSTEM TUTORIAL & FLOW GUIDE                |\n";
    cout << "+===============================================================+\n\n";

    cout << "Welcome to the Student Enrollment System Tutorial.\n\n";
    cout << "This guide will walk you through the proper usage and order of\n";
    cout << "operations within the system.\n\n";

    cout << "+----------------------------+\n";
    cout << "| STEP-BY-STEP SYSTEM FLOW   |\n";
    cout << "+----------------------------+\n";

    cout << "1. Student Management\n";
    cout << "   - Go to [2] Student Management Menu\n";
    cout << "   - Use [1] Add Student to register students (auto ID starts from 20250001)\n";
    cout << "   - Use [2] to view students in table format\n";
    cout << "   - You may also edit or delete using [3] or [4]\n\n";

    cout << "2. Course Management\n";
    cout << "   - Go to [4] Course Management Menu\n";
    cout << "   - Use [1] Add Course to define the subjects offered per year level\n";
    cout << "   - Use [2] View Courses to check list (sorted with table format)\n\n";

    cout << "3. Schedule Management\n";
    cout << "   - Go to [3] Schedule Management Menu\n";
    cout << "   - Use [1] Add Schedule to assign sections, time, room per course\n";
    cout << "   - View/Edit/Delete as needed\n\n";

    cout << "4. Enrollment\n";
    cout << "   - Go to [1] Enrollment Menu\n";
    cout << "   - Use [1] Enroll a Student\n";
    cout << "     ? System auto-filters courses based on student year level\n";
    cout << "     ? Each subject asks: Do you want to enroll? [Y/N]\n";
    cout << "     ? Duplicates are prevented, and confirmation is required\n";
    cout << "   - Use [2] to view enrolled students and their subjects\n\n";

    cout << "5. Exit Program\n";
    cout << "   - Go to [X] from the main menu\n";
    cout << "   - Displays your group name and members\n";
    cout << "   - Cleanly ends the program\n\n";

    cout << "+---------------------------+\n";
    cout << "| GENERAL TIPS              |\n";
    cout << "+---------------------------+\n";
    cout << "- Always add students BEFORE enrolling.\n";
    cout << "- Make sure courses and schedules are set up.\n";
    cout << "- View outputs are displayed using organized tables.\n";
    cout << "- The system saves everything in real-time to .txt files.\n";

    cout << "\nPress Enter to return to the Main Menu...";
    cin.get();
}


