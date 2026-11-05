#ifndef ENROLLMENT_H
#define ENROLLMENT_H

#include <string>
#include "student.h"

const int MAX_STUDENTS = 100;
const int MAX_REQUESTS = 50;

extern Student students[MAX_STUDENTS];
extern int studentCount;
extern Student requests[MAX_REQUESTS];
extern int qFront;
extern int qCount;

int linearSearch(const std::string& id);
bool pendingHasId(const std::string& id);
void insertionSort();
void addRequest();
void processNext();
void displayStudents();

#endif
