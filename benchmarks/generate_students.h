#ifndef GENERATE_STUDENTS_H
#define GENERATE_STUDENTS_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "student.h"
#include "enrollment.h"
#include "helpers.h"

void generateRandomStudents_Interface() {   
    // Generate a Random Set of Students
    std::cout << "\n===== RANDOM STUDENT GENERATOR (For Benchmarking) =====\n";
    std::cout << "1. 100 Students \n";
    std::cout << "2. 1,000 Students\n";
    std::cout << "3. 10,000 Students\n";
    std::cout << "4. 100,000 Students\n";
    std::cout << "0. Back to Main Menu\n";

    // Asks how many Students the User wants to Register for Benchmarking
    int choice = askInt("Select option (0-4): ", 0, 4);
    if (choice == 0)
    {
        std::cout << "===== Returning to Main Menu =====\n";
        return;
    }

    int count = 0;
    if (choice == 1)
        count = 100;
    else if (choice == 2)
        count = 1000;
    else if (choice == 3)
        count = 10000;
    else if (choice == 4)
        count = 100000;

    std::random_device rd;
    std::mt19937 gen(rd());

    // Generates a Random ID number, Random Year Level (1 - 5), Random Grade (0 - 100), and If they are Enrolled in a certain Subject
    std::uniform_int_distribution<int> Random_ID(100000000, 999999999);
    std::uniform_int_distribution<int> Random_Year(1, 5);
    std::uniform_int_distribution<int> Random_Grade(0, 100);
    std::uniform_int_distribution<int> Random_Subject_Enrolled(0, 1);

    // Student programs for variety
    std::string programs[] = {"CPE", "CS", "IT", "ECE", "EE"};

    std::cout << "Generating " << count << " students and adding directly to records...\n";

    students.reserve(students.size() + count);

    // Names the Students using a Placeholder name (Student #)
    for (int i = 1; i <= count; ++i)
    {
        Student s;
        s.id = std::to_string(Random_ID(gen));

        s.name = "Student " + std::to_string(i);

        s.program = programs[gen() % 5];
        s.year = Random_Year(gen);

        for (int j = 0; j < NUM_SUBJECTS; ++j) {
            s.enrolled[j] = (Random_Subject_Enrolled(gen) == 1);
            if (s.enrolled[j]) {
                s.grades[j] = Random_Grade(gen);
            } else {
                s.grades[j] = NOT_GRADED;
            }
        }

        students.push_back(s);
        studentCount++;
    }

    // Display how many students were recorded in the system
    std::cout << "Successfully added " << count << " students! Total records: " << studentCount << "\n";
}

#endif