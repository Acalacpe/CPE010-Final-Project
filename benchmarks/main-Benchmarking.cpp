#include <iostream>
#include "enrollment.h"
#include "grades.h"
#include "generate_students.h"

int main() {
  
    
    while (true) {
        std::cout << "\n===== STUDENT ENROLLMENT & GRADE RECORD SYSTEM =====\n";
        std::cout << "\n[Status] Enrolled: " << studentCount << " | Pending Requests: " << qCount << "\n";
        std::cout << "1. Add enrollment request\n";
        std::cout << "2. Process next request\n";
        std::cout << "3. Display students alphabetically\n";
        std::cout << "4. Search student\n";
        std::cout << "5. Generate Random Students\n";
        std::cout << "0. Exit Test\n";
        
        int choice = askInt("Enter choice (0-5): ", 0, 5);
         if (choice == 0) {
            std::cout << "Exiting test driver.\n";
            break;
        }
        else if (choice == 1) addRequest();
        else if (choice == 2) processNext();
        else if (choice == 3) displayStudents();
        else if (choice == 4) searchStudent();
        else if (choice == 5) generateRandomStudents_Interface();
    }
 
    return 0;
}
