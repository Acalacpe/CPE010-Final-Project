#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <string>
#include "student.h"

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

    bool isFull() const {
        return top >= MAX_STACK_SIZE - 1;
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool push(const GradeChange& change) {
        if (isFull()) {
            std::cout << "Grade history stack overflow!\n";
            return false;
        }
        changes[++top] = change;
        return true;
    }

    bool pop(GradeChange& poppedChange) {
        if (isEmpty()) {
            std::cout << "No grade updates to undo!\n";
            return false;
        }
        poppedChange = changes[top--];
        return true;
    }

    bool peek(GradeChange& topChange) const {
        if (isEmpty()) return false;
        topChange = changes[top];
        return true;
    }
};

inline GradeStack gradeHistoryStack;

inline void recordGradeEdit(const std::string& studentId, int subjectIndex, int oldGrade, int newGrade) {
    GradeChange gc = { studentId, subjectIndex, oldGrade, newGrade };
    gradeHistoryStack.push(gc);
}

inline bool undoLastGradeEdit(GradeChange& undoneChange) {
    return gradeHistoryStack.pop(undoneChange);
}

std::string askText(const std::string& prompt) {
    std::string s;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, s)) exit(0);
        if (!s.empty()) return s;
        std::cout << "  Cannot be empty.\n";
    }
}

std::string askName(const std::string& prompt, const std::string& label) {
    while (true) {
        std::string s = askText(prompt);
        bool ok = true;
        bool hasLetter = false;
        for (size_t i = 0; i < s.size(); i++) {
            char c = s[i];
            if (std::isalpha((unsigned char)c)) hasLetter = true;
            else if (c != ' ' && c != ',' && c != '.' && c != '-' && c != '\'') ok = false;
        }
        if (ok && hasLetter) return s;
        std::cout << "  Invalid. " << label << " must have letters only (no numbers or symbols).\n";
    }
}

int askInt(const std::string& prompt, int lo, int hi) {
    while (true) {
        std::cout << prompt;
        std::string s;
        if (!std::getline(std::cin, s)) exit(0);
        bool ok = !s.empty() && s.size() <= 9;
        for (size_t i = 0; i < s.size(); i++)
            if (s[i] < '0' || s[i] > '9') ok = false;
        if (ok) {
            int v = std::stoi(s);
            if (v >= lo && v <= hi) return v;
        }
        std::cout << "  Invalid. Enter a whole number from " << lo << " to " << hi << ".\n";
    }
}

bool askYesNo(const std::string& prompt) {
    while (true) {
        std::string s = askText(prompt);
        if (s == "y" || s == "Y") return true;
        if (s == "n" || s == "N") return false;
        std::cout << "  Enter y or n.\n";
    }
}

std::string gradeText(const Student& s, int sub) {
    if (!s.enrolled[sub]) return "Not enrolled";
    if (s.grades[sub] == NOT_GRADED) return "Not yet graded";
    return std::to_string(s.grades[sub]) + (s.grades[sub] >= PASSING_GRADE ? " (Passed)" : " (Failed)");
}

void printStudent(const Student& s) {
    std::cout << s.name << " | ID: " << s.id << " | " << s.program << ", Year " << s.year << "\n";
}

#endif
