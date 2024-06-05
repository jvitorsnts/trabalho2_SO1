//
// Created by gabri on 04/06/2024.
//

// BitmapMemoryManager.cpp
#include "../headers/BitmapMemoryManager.h"
#include <iostream>

BitmapMemoryManager::BitmapMemoryManager(int totalSize, int minBlockSize, int allocType)
    : MemoryManager(totalSize, minBlockSize, allocType), memoryBitmap(totalSize / minBlockSize, 0) {}

int BitmapMemoryManager::allocate(int size) {
    // Implement the allocate method
    // Update the memoryBitmap accordingly
    int index;
    cout << "Allocating " << size << " bytes" << endl;
    if (allocationType == 1) {
     index = firstFit(size);
    } else {
        index = nextFit(size);
    }
    cout << "Block allocated at index " << index << endl;

    return index;
}

void BitmapMemoryManager::deallocate(int id) {
    // Implement the deallocate method
    // Update the memoryBitmap accordingly
    cout<<"Finding dealocate"<<endl;
     for (auto& operation : memOperations) {
        if(operation.getId() == id){
            for (int i = operation.getIndex(); i < operation.getIndex() + (operation.getSize()/minimumBlockSize); i++) {
                memoryBitmap[i] = 0;
            }
            break;
        }
            
     }

    cout << "Deallocating block of id " << id << endl;
}

void BitmapMemoryManager::printMemory() const {
    // Implement the printMemory method
    // iterate over the bitmap and print the values all in the same line without spaces between
    for (const auto &block : memoryBitmap) {
        cout << block;
    }
    cout << endl;
}

int BitmapMemoryManager::firstFit(int size) {
// finds the first sequence of blocks that are empty and have enough space to allocate the size
// and then fills the blocks with 1 and returns the index of the first block
    int blocks = size / minimumBlockSize;
    int count = 0;
    int index = -1;
    for (int i = 0; i < memoryBitmap.size(); i++) {
        if (memoryBitmap[i] == 0) {
            count++;
            if (count == blocks) {
                index = i - blocks + 1;
                break;
            }
        } else {
            count = 0;
        }
    }
    if (index != -1) {
        for (int i = index; i < index + blocks; i++) {
            memoryBitmap[i] = 1;
        }
    }
    return index;
}

int BitmapMemoryManager::nextFit(int size) {
    // Implement the nextFit method
    // Return the index of the next block that fits the size
    int blocks = size / minimumBlockSize;
    int count = 0;
    int index = -1;

    for (int i = managerIndex; i < memoryBitmap.size(); i++) {
        if (memoryBitmap[i] == 0) {
            count++;
            if (count == blocks) {
                index = i - blocks + 1;
                break;
            }
        } else {
            count = 0;
        }
    }

    if (count != blocks) {
        count = 0;
        for (int i = 0; i < managerIndex; i++) {
            if (memoryBitmap[i] == 0) {
                count++;
                if (count == blocks) {
                    index = i - blocks + 1;
                    break;
                }
            } else {
                count = 0;
            }
        }
    }

    if (index != -1) {
        managerIndex = index+blocks+1;
        while (memoryBitmap[managerIndex] == 1) {
            if (managerIndex == memoryBitmap.size()) managerIndex =  0;
            else managerIndex++;
        }

        for (int i = index; i < index + blocks; i++) {
            memoryBitmap[i] = 1;
        }
    }
    return index;
    return -1;
}