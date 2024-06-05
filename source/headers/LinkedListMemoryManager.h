//
// Created by gabri on 04/06/2024.
//

// LinkedListMemoryManager.h
#ifndef LINKEDLISTMEMORYMANAGER_H
#define LINKEDLISTMEMORYMANAGER_H

#include "MemoryManager.h"
#include <list>

struct MemoryBlock {
    int start;
    int size;
    bool isFree;
};

class LinkedListMemoryManager : public MemoryManager {
private:
    std::list<MemoryBlock> memoryList;

public:
    LinkedListMemoryManager(int totalSize, int minBlockSize)
        : MemoryManager(totalSize, minBlockSize) {
        memoryList.push_back({0, totalSize, true});
    }

    void allocate(int size) override;
    void deallocate(int index) override;
    void printMemory() const override;
};

#endif // LINKEDLISTMEMORYMANAGER_H