#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <string>
#include "student.h"

int linearSearch(const Student records[], int count, const std::string& id);
bool nameGreater(const std::string& a, const std::string& b);
void insertionSort(Student records[], int count);

#endif
