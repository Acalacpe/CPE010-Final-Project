#ifndef STUDENT_H
#define STUDENT_H

#include <string>

const int NUM_SUBJECTS = 3;
const int NOT_GRADED = -1;
const int PASSING_GRADE = 75;

const std::string SUBJECT_NAMES[NUM_SUBJECTS] = {
    "English", "Mathematics", "Science"
};

struct Student {
    std::string id;
    std::string name;
    std::string program;
    int year = 0;
    bool enrolled[NUM_SUBJECTS] = {false, false, false};
    int grades[NUM_SUBJECTS] = {NOT_GRADED, NOT_GRADED, NOT_GRADED};
};

#endif
