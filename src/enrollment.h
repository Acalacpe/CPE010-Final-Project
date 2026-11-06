#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <iostream>
#include "student.h"
#include "algorithms.h"

const int MAX_STUDENTS = 100;
const int MAX_REQUESTS = 50;

inline Student students[MAX_STUDENTS];
inline int studentCount = 0;
inline Student requests[MAX_REQUESTS];
inline int qFront = 0;
inline int qCount = 0;

inline int linearSearch(const std::string& id) {
    return linearSearch(students, studentCount, id);
}

inline bool pendingHasId(const std::string& id) {
    for (int i = 0; i < qCount; i++) {
        if (requests[(qFront + i) % MAX_REQUESTS].id == id) return true;
    }
    return false;
}

inline void insertionSort() {
    insertionSort(students, studentCount);
}

inline void addRequest() {
    std::cout << "\n--- Add Enrollment Request ---\n";
    if (qCount == MAX_REQUESTS) {
        std::cout << "Queue is full. Process a request first.\n";
        return;
    }

    Student student;
    while (true) {
        student.id = askText("Student number: ");
        bool valid = true;
        for (std::size_t i = 0; i < student.id.size(); i++) {
            if (student.id[i] < '0' || student.id[i] > '9') valid = false;
        }
        if (valid) break;
        std::cout << "  Invalid. Student number must contain digits only.\n";
    }

    if (linearSearch(student.id) != -1) {
        std::cout << "Rejected: " << student.id << " is already enrolled.\n";
        return;
    }
    if (pendingHasId(student.id)) {
        std::cout << "Rejected: " << student.id << " already has a pending request.\n";
        return;
    }

    student.name = askName("Full name (LN, FN M.I): ", "Name");
    student.program = askName("Program: ", "Program");
    student.year = askInt("Year level (1-5): ", 1, 5);

    bool any = false;
    while (!any) {
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            student.enrolled[i] = askYesNo("Enroll in " + SUBJECT_NAMES[i] + "? (y/n): ");
            if (student.enrolled[i]) any = true;
        }
        if (!any) std::cout << "Pick at least one subject.\n";
    }

    int rear = (qFront + qCount) % MAX_REQUESTS;
    requests[rear] = student;
    qCount++;
    std::cout << "Request added successfully! (Pending position: " << qCount << ").\n";
}

inline void processNext() {
    std::cout << "\n--- Process Next Request ---\n";
    if (qCount == 0) {
        std::cout << "No pending requests to process.\n";
        return;
    }
    if (studentCount == MAX_STUDENTS) {
        std::cout << "Student records are full. Request stays in the queue.\n";
        return;
    }

    students[studentCount++] = requests[qFront];
    std::cout << "Successfully Enrolled: " << requests[qFront].name
              << " (" << requests[qFront].id << ")\n";
    qFront = (qFront + 1) % MAX_REQUESTS;
    qCount--;
}

inline void displayStudents() {
    std::cout << "\n--- Enrolled Students (Alphabetical A-Z) ---\n";
    if (studentCount == 0) {
        std::cout << "No enrolled students yet.\n";
        return;
    }
    insertionSort();
    for (int i = 0; i < studentCount; i++) {
        std::cout << i + 1 << ". ";
        printStudent(students[i]);
    }
}

#endif