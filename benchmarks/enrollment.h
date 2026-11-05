#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "student.h"
#include "helpers.h"

const int MAX_REQUESTS = 50;

inline std::vector<Student> students; // Uses Vectors to Handle 100,000+ Students
inline int studentCount = 0;

Student requests[MAX_REQUESTS];
int qFront = 0;
int qCount = 0;

int linearSearch(const std::string& id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) return i;
    }
    return -1;
}

bool pendingHasId(const std::string& id) {
    for (int i = 0; i < qCount; i++) {
        if (requests[(qFront + i) % MAX_REQUESTS].id == id) return true;
    }
    return false;
}

bool nameGreater(const std::string& a, const std::string& b) {
    size_t i = 0;
    while (i < a.size() && i < b.size()) {
        char x = std::tolower((unsigned char)a[i]);
        char y = std::tolower((unsigned char)b[i]);
        if (x != y) return x > y;
        i++;
    }
    return a.size() > b.size();
}

void insertionSort() {
    for (int i = 1; i < studentCount; i++) {
        Student key = students[i];
        int j = i - 1;
        while (j >= 0 && nameGreater(students[j].name, key.name)) {
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = key;
    }
}

void addRequest() {
    std::cout << "\n--- Add Enrollment Request ---\n";
    if (qCount == MAX_REQUESTS) {
        std::cout << "Queue is full. Process a request first.\n";
        return;
    }

    Student s;
    while (true) {
        s.id = askText("Student number: ");
        bool isValid = true;
        for (size_t i = 0; i < s.id.size(); i++) {
            if (s.id[i] < '0' || s.id[i] > '9') {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            break;
        }
        std::cout << "  Invalid. Student number must contain digits only (no letters).\n";
    }

    if (linearSearch(s.id) != -1) {
        std::cout << "Rejected: " << s.id << " is already enrolled.\n";
        return;
    }
    if (pendingHasId(s.id)) {
        std::cout << "Rejected: " << s.id << " already has a pending request.\n";
        return;
    }
    s.name = askName("Full name (LN, FN M.I): ", "Name");
    s.program = askName("Program: ", "Program");
    s.year = askInt("Year level (1-5): ", 1, 5);

    bool any = false;
    while (!any) {
        for (int i = 0; i < NUM_SUBJECTS; i++) {
            s.enrolled[i] = askYesNo("Enroll in " + SUBJECT_NAMES[i] + "? (y/n): ");
            if (s.enrolled[i]) any = true;
        }
        if (!any) std::cout << "Pick at least one subject.\n";
    }

    int rear = (qFront + qCount) % MAX_REQUESTS;
    requests[rear] = s;
    qCount++;
    std::cout << "Request added successfully! (Pending position: " << qCount << ").\n";
}

void processNext() {
    std::cout << "\n--- Process Next Request ---\n";
    if (qCount == 0) {
        std::cout << "No pending requests to process.\n";
        return;
    }
    // Since it's a vector, we push back directly instead of checking MAX_STUDENTS
    students.push_back(requests[qFront]);
    studentCount++;
    std::cout << "Successfully Enrolled: " << requests[qFront].name << " (" << requests[qFront].id << ")\n";
    qFront = (qFront + 1) % MAX_REQUESTS;
    qCount--;
}

void displayStudents() {
    std::cout << "\n--- Enrolled Students (Alphabetical A-Z) ---\n";
    if (studentCount == 0) {
        std::cout << "No enrolled students yet.\n";
        return;
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    insertionSort();
    for (int i = 0; i < studentCount; i++) {
        std::cout << (i + 1) << ". ";
        printStudent(students[i]);
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "\nTime taken to Sort and Display (Insertion Sort) = "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count()
              << " milliseconds" << std::endl;
}

#endif