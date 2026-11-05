#ifndef GRADES_H
#define GRADES_H

#include <iostream>
#include <string>
#include "enrollment.h"
#include <iomanip>

void printGradeReportTable(int index) { //Grade Display
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

void updateGrade() {
    std::cout << " \n Enter/Update Final Grades \n";

    if (studentCount == 0) {
        std::cout << "No enrolled students available.\n";
        return;
    }

    std::string id = askText("Enter Student Number: ");
    int index = linearSearch(id);

    if (index == -1) {
        std::cout << "Student not found.\n";
        return;
    }

    std::cout << "\nStudent Found!\n";
    std::cout << "Name: " << students[index].name << "\n";
    std::cout << "Student ID: " << students[index].id << "\n";
    std::cout << "Program: " << students[index].program << "\n";
    std::cout << "Year Level: " << students[index].year << "\n";

    printGradeReportTable(index);

    while (true) {
        int choice = askInt("\nSelect Subject to edit:\n1. English\n2. Mathematics\n3. Science\n0. Exit\n", 0, NUM_SUBJECTS);

        if (choice == 0) {
            break;
        }

        int subjectIndex = choice - 1;

        if (!students[index].enrolled[subjectIndex]) {
            std::cout << "Student is not enrolled in this subject. Please choose an enrolled subject.\n";
            continue;
        }

        int oldGrade = students[index].grades[subjectIndex];
        int newGrade = askInt("Enter Final Grade (0-100): ", 0, 100);

        recordGradeEdit(students[index].id, subjectIndex, oldGrade, newGrade);

        students[index].grades[subjectIndex] = newGrade;
        std::cout << "\nGrade updated successfully for " << SUBJECT_NAMES[subjectIndex] << "!\n";

        printGradeReportTable(index);
    }
    
}

void undoGradeEdit() {
    GradeChange undone;
    if (!undoLastGradeEdit(undone)) {
        return;
    }

    int index = linearSearch(undone.studentId);
    if (index != -1) {
        students[index].grades[undone.subjectIndex] = undone.oldGrade;
        std::cout << "\n--- Undo Successful ---\n";
        std::cout << "Reverted grade for " << students[index].name 
                  << " (" << SUBJECT_NAMES[undone.subjectIndex] << ") back to: ";
        if (undone.oldGrade == NOT_GRADED) {
            std::cout << "Not yet graded\n";
        } else {
            std::cout << undone.oldGrade << "\n";
        }
        
        printGradeReportTable(index);
    }
}

#endif