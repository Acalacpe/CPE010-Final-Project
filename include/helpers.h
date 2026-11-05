#ifndef HELPERS_H
#define HELPERS_H

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

extern GradeStack gradeHistoryStack;

bool recordGradeEdit(const std::string& studentId, int subjectIndex,
                     int oldGrade, int newGrade);
bool undoLastGradeEdit(GradeChange& change);
std::string askText(const std::string& prompt);
std::string askName(const std::string& prompt, const std::string& label);
int askInt(const std::string& prompt, int lo, int hi);
bool askYesNo(const std::string& prompt);
std::string gradeText(const Student& student, int subjectIndex);
void printStudent(const Student& student);

#endif
