#include "algorithms.h"

#include <cctype>

int linearSearch(const Student records[], int count, const std::string& id) {
    for (int i = 0; i < count; i++) {
        if (records[i].id == id) return i;
    }
    return -1;
}

bool nameGreater(const std::string& a, const std::string& b) {
    std::size_t i = 0;
    while (i < a.size() && i < b.size()) {
        int x = std::tolower(static_cast<unsigned char>(a[i]));
        int y = std::tolower(static_cast<unsigned char>(b[i]));
        if (x != y) return x > y;
        i++;
    }
    return a.size() > b.size();
}

void insertionSort(Student records[], int count) {
    for (int i = 1; i < count; i++) {
        Student key = records[i];
        int j = i - 1;
        while (j >= 0 && nameGreater(records[j].name, key.name)) {
            records[j + 1] = records[j];
            j--;
        }
        records[j + 1] = key;
    }
}
