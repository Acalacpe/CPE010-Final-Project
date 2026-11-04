#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <string>
#include "student.h"

std::string askText(const std::string& prompt) {
    std::string s;
    while (true) {
        std::cout << prompt;
        if (!std::getline(std::cin, s)) exit(0);
        if (!s.empty()) return s;
        std::cout << "  Cannot be empty.\n";
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
    std::cout << s.name << " | ID: " << s.id << " | " << s.course << ", Year " << s.year << "\n";
    for (int i = 0; i < NUM_SUBJECTS; i++)
        std::cout << "      " << SUBJECT_NAMES[i] << ": " << gradeText(s, i) << "\n";
}

#endif