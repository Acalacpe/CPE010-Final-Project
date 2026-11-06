#ifndef GRADES_H
#define GRADES_H

#include <iostream>
#include <iomanip>
#include "enrollment.h"

inline void printGradeReportTable(int studentIndex) {
    if (studentIndex < 0 || studentIndex >= studentCount) return;
    const Student& student = students[studentIndex];
    std::cout << "\n--- Final Grade Report: " << student.name
              << " (" << student.id << ") ---\n";
    std::cout << std::left << std::setw(18) << "Subject"
              << std::setw(16) << "Final Grade" << "Status\n";

    int total = 0;
    int gradedCount = 0;
    int enrolledCount = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++) {
        if (!student.enrolled[i]) continue;
        enrolledCount++;
        int grade = student.grades[i];
        std::string text = "Not yet graded";
        std::string status = "Pending";
        if (grade != NOT_GRADED) {
            total += grade;
            gradedCount++;
            text = std::to_string(grade);
            status = grade >= PASSING_GRADE ? "Passed" : "Failed";
        }
        std::cout << std::left << std::setw(18) << SUBJECT_NAMES[i]
                  << std::setw(16) << text << status << "\n";
    }

    if (gradedCount == 0) {
        std::cout << "No grades recorded yet.\n";
        return;
    }
    double average = static_cast<double>(total) / gradedCount;
    std::cout << "Average of recorded grades: " << std::fixed
              << std::setprecision(2) << average << "\n";
    if (gradedCount < enrolledCount) {
        std::cout << "Overall remarks: Pending (some subjects are not yet graded).\n";
    } else {
        std::cout << "Overall remarks: "
                  << (average >= PASSING_GRADE ? "PASSED" : "FAILED") << "\n";
    }
}

inline bool updateStudentGrade(int studentIndex, int subjectIndex, int newGrade) {
    if (studentIndex < 0 || studentIndex >= studentCount) {
        std::cout << "Student not found.\n";
        return false;
    }
    if (subjectIndex < 0 || subjectIndex >= NUM_SUBJECTS
        || !students[studentIndex].enrolled[subjectIndex]) {
        std::cout << "Student is not enrolled in this subject.\n";
        return false;
    }
    if (newGrade < 0 || newGrade > 100) {
        std::cout << "Grade must be a whole number from 0 to 100.\n";
        return false;
    }

    Student& student = students[studentIndex];
    int oldGrade = student.grades[subjectIndex];
    if (oldGrade == newGrade) {
        std::cout << "Grade is unchanged.\n";
        return false;
    }

    GradeChange change = {student.id, subjectIndex, oldGrade, newGrade};
    if (!student.gradeHistory.push(change)) {
        std::cout << "Grade history is full. Grade was not changed.\n";
        return false;
    }

    student.grades[subjectIndex] = newGrade;
    std::cout << "Grade updated successfully for " << SUBJECT_NAMES[subjectIndex] << "!\n";
    return true;
}

inline bool undoLatestGradeEdit(int studentIndex) {
    if (studentIndex < 0 || studentIndex >= studentCount) return false;

    Student& student = students[studentIndex];
    GradeChange change;
    
    if (!student.gradeHistory.pop(change)) {
        std::cout << "No grade updates to undo for this student.\n";
        return false;
    }

    student.grades[change.subjectIndex] = change.oldGrade;

    std::cout << "\n--- Undo Successful ---\nReverted grade for "
              << student.name << " (" << change.studentId << ", "
              << SUBJECT_NAMES[change.subjectIndex] << ") back to: ";
    if (change.oldGrade == NOT_GRADED) std::cout << "Not yet graded\n";
    else std::cout << change.oldGrade << "\n";

    printGradeReportTable(studentIndex);
    return true;
}

inline void editGrades(int studentIndex) {
    while (true) {
        std::cout << "\nSelect Subject to Edit:\n";
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            if (students[studentIndex].enrolled[i]) {
                std::cout << i + 1 << ". " << SUBJECT_NAMES[i] << "\n";
            }
        }
        std::cout << "0. Finish editing\n";
        int choice = askInt("Choice (0-3): ", 0, NUM_SUBJECTS);
        if (choice == 0) {
            printGradeReportTable(studentIndex);
            return;
        }
        int subjectIndex = choice - 1;
        if (!students[studentIndex].enrolled[subjectIndex]) {
            std::cout << "Student is not enrolled in this subject. Pick an enrolled subject.\n";
            continue;
        }
        int newGrade = askInt("Enter Final Grade (0-100): ", 0, 100);
        updateStudentGrade(studentIndex, subjectIndex, newGrade);
    }
}

inline void searchStudent() {
    std::cout << "\n--- Search Student ---\n";
    if (studentCount == 0) {
        std::cout << "No enrolled students available.\n";
        return;
    }
    int index = linearSearch(askText("Enter Student Number: "));
    if (index == -1) {
        std::cout << "Student not found.\n";
        return;
    }
    printStudent(students[index]);
    while (true) {
        std::cout << "\n1. Display grade report\n";
        std::cout << "2. Enter or edit grade\n";
        std::cout << "3. Undo last grade edit\n";
        std::cout << "0. Back to main menu\n";

        int option = askInt("Select option (0-3): ", 0, 3);
        if (option == 0) return;
        else if (option == 1) printGradeReportTable(index);
        else if (option == 2) editGrades(index);
        else if (option == 3) undoLatestGradeEdit(index);
    }
}

#endif