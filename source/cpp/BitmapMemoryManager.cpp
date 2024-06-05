//
// Created by gabri on 04/06/2024.
//

// BitmapMemoryManager.cpp
#include "../headers/BitmapMemoryManager.h"
#include <iostream>

void BitmapMemoryManager::allocate(int size) {
    // Implement the allocate method
    // Update the memoryBitmap accordingly
    cout << "Allocating " << size << " bytes" << endl;
}

void BitmapMemoryManager::deallocate(int index) {
    // Implement the deallocate method
    // Update the memoryBitmap accordingly
    cout << "Deallocating block at index " << index << endl;
}

void BitmapMemoryManager::printMemory() const {
    // Implement the printMemory method
    // iterate over the bitmap and print the values all in the same line without spaces between
    for (const auto &block : memoryBitmap) {
        cout << block;
    }
    cout << endl;
}