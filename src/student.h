#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include <cctype>
#include <cstdlib>

const int NUM_SUBJECTS = 3;
const int NOT_GRADED = -1;
const int PASSING_GRADE = 75;

const std::string SUBJECT_NAMES[NUM_SUBJECTS] = {
    "English", "Mathematics", "Science"
};

struct GradeChange {
    std::string studentId;
    int subjectIndex;
    int oldGrade;
    int newGrade;
};

const int MAX_STACK_SIZE = 50;

struct GradeStack {
    GradeChange changes[MAX_STACK_SIZE];
    int top = -1;

    bool isFull() const { return top >= MAX_STACK_SIZE - 1; }
    bool isEmpty() const { return top == -1; }

    bool push(const GradeChange& change) {
        if (isFull()) return false;
        changes[++top] = change;
        return true;
    }

    bool pop(GradeChange& change) {
        if (isEmpty()) return false;
        change = changes[top--];
        return true;
    }

    bool peek(GradeChange& change) const {
        if (isEmpty()) return false;
        change = changes[top];
        return true;
    }
};

struct Student {
    std::string id;
    std::string name;
    std::string program;
    int year = 0;
    bool enrolled[NUM_SUBJECTS] = {false, false, false};
    int grades[NUM_SUBJECTS] = {NOT_GRADED, NOT_GRADED, NOT_GRADED};
    GradeStack gradeHistory;
};


inline std::string askText(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string value;
        if (!std::getline(std::cin, value)) std::exit(0);
        if (value.find_first_not_of(" \t\r\n") != std::string::npos) return value;
        std::cout << "  Cannot be empty.\n";
    }
}

inline std::string askName(const std::string& prompt, const std::string& label) {
    while (true) {
        std::string value = askText(prompt);
        bool valid = true;
        bool hasLetter = false;
        for (std::size_t i = 0; i < value.size(); i++) {
            char c = value[i];
            if (std::isalpha(static_cast<unsigned char>(c))) hasLetter = true;
            else if (c != ' ' && c != ',' && c != '.' && c != '-' && c != '\'')
                valid = false;
        }
        if (valid && hasLetter) return value;
        std::cout << "  Invalid. " << label
                  << " must contain letters; spaces, commas, periods, hyphens, and apostrophes are allowed.\n";
    }
}

inline int askInt(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::cout << prompt;
        std::string value;
        if (!std::getline(std::cin, value)) std::exit(0);
        bool valid = !value.empty() && value.size() <= 9;
        for (std::size_t i = 0; i < value.size(); i++) {
            if (value[i] < '0' || value[i] > '9') valid = false;
        }
        if (valid) {
            int number = std::stoi(value);
            if (number >= lo && number <= hi) return number;
        }
        std::cout << "  Invalid. Enter a whole number from " << lo << " to " << hi << ".\n";
    }
}

inline bool askYesNo(const std::string& prompt) {
    while (true) {
        std::string value = askText(prompt);
        if (value == "y" || value == "Y") return true;
        if (value == "n" || value == "N") return false;
        std::cout << "  Enter y or n.\n";
    }
}

inline std::string gradeText(const Student& student, int subjectIndex) {
    if (!student.enrolled[subjectIndex]) return "Not enrolled";
    if (student.grades[subjectIndex] == NOT_GRADED) return "Not yet graded";
    return std::to_string(student.grades[subjectIndex])
        + (student.grades[subjectIndex] >= PASSING_GRADE ? " (Passed)" : " (Failed)");
}

inline void printStudent(const Student& student) {
    std::cout << student.name << " | ID: " << student.id << " | "
              << student.program << ", Year " << student.year << "\n";
}



#endif