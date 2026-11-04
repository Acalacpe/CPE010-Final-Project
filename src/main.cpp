#include <iostream>
#include "enrollment.h"

int main() {
  
    
    while (true) {
        std::cout << "\n===== STUDENT ENROLLMENT & GRADE RECORD SYSTEM =====\n";
        std::cout << "\n[Status] Enrolled: " << studentCount << " | Pending Requests: " << qCount << "\n";
        std::cout << "1. Add enrollment request\n";
        std::cout << "2. Process next request\n";
        std::cout << "3. Display students alphabetically\n";
        std::cout << "0. Exit Test\n";
        
        int choice;
        std::cout << "Enter choice (0-3): ";
        if (!(std::cin >> choice)) break;
        std::cin.ignore(); // Clear newline buffer

        if (choice == 0) {
            std::cout << "Exiting test driver.\n";
            break;
        }
        else if (choice == 1) addRequest();
        else if (choice == 2) processNext();
        else if (choice == 3) displayStudents();
        else std::cout << "Invalid choice. Try again.\n";
    }

    return 0;
}