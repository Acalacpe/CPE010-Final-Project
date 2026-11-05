#ifndef GRADES_H
#define GRADES_H

#include <iostream>
#include <string>
#include "enrollment.h"

void updateGrade() {

    std::cout << " \n Enter/Update Final Grades \n";

    if (studentCount == 0) {
        std::cout << "No enrolled students available.\n";
        return;
    }

    std::string id = askText("Enter Student Number: ");

    int index = linearSearch(id);

    if (index == -1){
        std::cout << "Student not found.\n";
        return;
    }

    std::cout << "\nStudent Found!\n";
    std::cout << "Name: " << students[index].name << "\n";
    std::cout << "Student ID: " << students[index].id << "\n";
    std::cout << "Course: " << students[index].course << "\n";
    std::cout <<"Year Level: " << students[index].year << "\n";

    std::cout << "\n Enrolled Subjects \n";

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        if (students[index].enrolled[i]) {
            
            std::cout << i + 1 << ". "
                      << SUBJECT_NAMES[i] << " - ";

            if (students[index].grades[i] == NOT_GRADED) {
                std::cout << "Not yet graded\n";
            }
            else{
                std::cout << students[index].grades[i] << "\n";
            }
        }
    }

    int choice = askInt(
        "\nSelect Subject (1-3): ",
        1, NUM_SUBJECTS
    );

    int subjectIndex = choice - 1;

    if (!students[index].enrolled[subjectIndex]) {
        std::cout << "Student is not enrolled in this subject.\n";
        return;
    }

    int grade = askInt(
        "Enter Final Grade (0-100): ",
        0, 100
    );

    students[index].grades[subjectIndex] = grade;

    std::cout << "\nGrade successfully saved!\n";
    std::cout << "Student: " << students[index].name << "\n";
    std::cout << "Suject: " << SUBJECT_NAMES[subjectIndex] << "\n";
    std::cout << "Final Grade: " << grade << "\n";

    if (grade >= PASSING_GRADE) {
        std::cout << "Status: Passed\n";
    }
    else {
        std::cout << "Status: Failed\n";
    }
}

#endif