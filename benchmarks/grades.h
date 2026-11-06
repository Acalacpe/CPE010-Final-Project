#ifndef GRADES_H
#define GRADES_H

#include <iostream>
#include <string>
#include <chrono>
#include "enrollment.h"
#include <iomanip>

void printGradeReportTable(int index) { // Grade Display
    std::cout << "\n==================================================\n";
    std::cout << "                FINAL GRADE REPORT                \n";
    std::cout << "==================================================\n";
    std::cout << "|     Subject      | Final Grade | Status |\n";
    std::cout << "--------------------------------------------------\n";

    int total = 0;
    int gradedCount = 0;

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        if (students[index].enrolled[i]) {
            int grade = students[index].grades[i];
            
            std::string gradeStr;
            std::string status;

            if (grade == NOT_GRADED) {
                gradeStr = "N/A";
                status = "N/A";
            } else {
                total += grade;
                gradedCount++;
                gradeStr = std::to_string(grade);
                status = (grade >= PASSING_GRADE) ? "Passed" : "Failed";
            }

            std::cout << "| " << std::left  << std::setw(16) << SUBJECT_NAMES[i]
                    << " | " << std::left  << std::setw(11) << gradeStr
                    << " | " << std::left  << std::setw(6)  << status
                    << " |\n";
        }
    }

    std::cout << "==================================================\n";
    if (gradedCount > 0) {
        double average = (double)total / gradedCount;
        std::cout << "Overall Average : " << average << "\n";
        std::cout << "Overall Remarks : " << ((average >= PASSING_GRADE) ? "PASSED" : "FAILED") << "\n";
    } else {
        std::cout << "No grades recorded yet.\n";
    }
    std::cout << "==================================================\n";
}

void undoStudentGradeEdit(int studentIndex) {
    GradeChange undone;
    if (!undoLastGradeEdit(undone)) {
        return;
    }

    int index = linearSearch(undone.studentId);
    if (index != -1) {
        students[index].grades[undone.subjectIndex] = undone.oldGrade; // Fixed typo here
        std::cout << "\n--- Undo Successful ---\n";
        std::cout << "Reverted grade for " << students[index].name 
                  << " (" << SUBJECT_NAMES[undone.subjectIndex] << ") back to: ";
        if (undone.oldGrade == NOT_GRADED) {
            std::cout << "Not yet graded\n";
        } else {
            std::cout << undone.oldGrade << "\n";
        }
    }
}

void searchStudent() {
    std::cout << " \nSearch Student \n";

    if (studentCount == 0) {
        std::cout << "No enrolled students available.\n";
        return;
    }

    std::string id = askText("Enter Student Number: ");

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    int index = linearSearch(id);

    if (index == -1) {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "\nTime taken to search = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
              << " milliseconds" << std::endl;

        std::cout << "Student not found.\n";
        return;
    }

    std::cout << "\nStudent Found!\n";
    std::cout << "Name: " << students[index].name << "\n";
    std::cout << "Student ID: " << students[index].id << "\n";
    std::cout << "Program: " << students[index].program << "\n";
    std::cout << "Year Level: " << students[index].year << "\n";

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "\nTime taken to search (Linear Search) = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
              << " milliseconds" << std::endl;

    while (true) {
        std::cout << "\n----------------------------------------\n";
        std::cout << "         STUDENT GRADE OPTIONS          \n";
        std::cout << "----------------------------------------\n";
        std::cout << "1. Display Grade Report\n";
        std::cout << "2. Edit Grade\n";
        std::cout << "3. Undo Last Grade Change\n";
        std::cout << "0. Exit\n";
        
        int option = askInt("Select Option (0-3): ", 0, 3);

        if (option == 0) {
            break;
        }

        switch (option) {
            case 1: {
                printGradeReportTable(index);
                break;
            }
            case 2: {
                while (true) {
                    std::cout << "\nSelect Subject to Edit:\n";
                    for (int i = 0; i < NUM_SUBJECTS; i++) {
                        if (students[index].enrolled[i]) {
                            std::cout << i + 1 << ". " << SUBJECT_NAMES[i] << std::endl;
                        }
                    }
                    std::cout << "0. Exit Editing\n";

                    int choice = askInt("Choice (0-3): ", 0, NUM_SUBJECTS);

                    if (choice == 0) {
                        printGradeReportTable(index);
                        break;
                    }

                    int subjectIndex = choice - 1;

                    if (!students[index].enrolled[subjectIndex]) {
                        std::cout << "Student is not enrolled in this subject. Please pick an enrolled subject.\n";
                        continue;
                    }

                    int oldGrade = students[index].grades[subjectIndex];
                    int newGrade = askInt("Enter Final Grade (0-100): ", 0, 100);

                    recordGradeEdit(students[index].id, subjectIndex, oldGrade, newGrade);
                    students[index].grades[subjectIndex] = newGrade;

                    std::cout << "\nGrade updated successfully for " << SUBJECT_NAMES[subjectIndex] << "!\n";
                }
                break;
            }
            case 3: {
                undoStudentGradeEdit(index);
                printGradeReportTable(index);
                break;
            }
        }
    }
}

#endif
