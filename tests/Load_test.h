//
// Created by tomin on 16.10.2024.
//

#ifndef SMARTPOINTER_LOAD_TEST_H
#define SMARTPOINTER_LOAD_TEST_H
#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <cmath>
#include "../pointers/ShrdPtr.h"

void benchmark() {
    cout << left << setw(10) << "Count"
         << setw(15) << "Raw Duration (ms)  "
         << setw(15) << "Smart Duration (ms)" << endl;

    // Степенное увеличение объектов от 10 до 1 000 000
    for (size_t i = 1; i <= 7; ++i) {
        size_t numObjects = static_cast<size_t>(pow(10, i)); // 10, 100, 1000, ..., 10^7

        // Без умных указателей
        auto start = chrono::high_resolution_clock::now();
        int** rawPointers = new int*[numObjects];
        for (size_t j = 0; j < numObjects; ++j) {
            rawPointers[j] = new int(j);
        }
        for (size_t j = 0; j < numObjects; ++j) {
            delete rawPointers[j];
        }
        delete[] rawPointers;
        auto end = chrono::high_resolution_clock::now();
        auto durationRaw = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        // Умные указатели
        start = chrono::high_resolution_clock::now();
        {
            vector<ShrdPtr<int>> smartPointers;
            for (size_t j = 0; j < numObjects; ++j) {
                smartPointers.emplace_back(new int(j));
            }
        }
        end = chrono::high_resolution_clock::now();
        auto durationSmart = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        cout << left << setw(10) << numObjects
             << setw(19) << durationRaw
             << setw(19) << durationSmart << endl;
    }
}

int load_main() {
    test_shrdPtr();
    test_unqPtr();
    benchmark();
    return 0;
}

#endif //SMARTPOINTER_LOAD_TEST_H
