//
// Created by gabri on 04/06/2024.
//

// LinkedListMemoryManager.cpp
#include "../headers/LinkedListMemoryManager.h"
#include <iostream>

LinkedListMemoryManager::LinkedListMemoryManager(int totalSize, int minBlockSize, int allocType)
    : MemoryManager(totalSize, minBlockSize, allocType) {
        memoryList.push_back({0, totalSize, true});
}

int LinkedListMemoryManager::allocate(int size) {
    // Implement the allocate method using a linked list
    // prints the size for now
    int index = 0;
    std::cout << "Allocating " << size << " bytes" << std::endl;
    if (allocationType == 1) {
        index = firstFit(size);
    } else {
        index = nextFit(size);
    }
    if (index != -1) {
        int blocksNeeded = size / minimumBlockSize + (size % minimumBlockSize != 0);
        allocatedBytes += blocksNeeded * minimumBlockSize;
        numAllocations++;
        std::cout << "Block allocated at index " << index << std::endl;
    } else {
        std::cout << "Block could not be allocated" << std::endl;
    }
    return index;
}

void LinkedListMemoryManager::deallocate(int id) {
    // Implement the deallocate method
        // prints the index for now
    std::cout << "Deallocating block at id " << id << std::endl;
    for (auto& operation : memOperations) {
        if(operation.getId() == id){
            int blocks = operation.getSize() / minimumBlockSize + (operation.getSize() % minimumBlockSize != 0);
            deallocatedBytes += blocks * minimumBlockSize;
            numDeallocations++;
            for (int i = operation.getIndex(); i < operation.getIndex() + (operation.getSize()/minimumBlockSize); i++) {
                // todo: dealocates the block
            }
            break;
        }

    }
}

void LinkedListMemoryManager::printMemory() const {
    // Implement the printMemory method
    std::cout << "Printing memory" << std::endl;
}

int LinkedListMemoryManager::firstFit(int size) {
    // finds the first sequence of blocks that are empty and have enough space to allocate the size
    // and then fills the blocks with 1 and returns the index of the first block
    std::cout << "First fit" << std::endl;
    cout << size << endl;
    return 0;
}

int LinkedListMemoryManager::nextFit(int size) {
    // finds the next sequence of blocks that are empty and have enough space to allocate the size
    // and then fills the blocks with 1 and returns the index of the first block
    std::cout << "Next fit" << std::endl;
    cout << size << endl;
    return 0;
}