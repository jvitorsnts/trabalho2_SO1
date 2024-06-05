//
// Created by gabri on 04/06/2024.
//
// MemoryManager.h
#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <vector>
#include "MemoryHandling.h"

class MemoryManager {
protected:
    int totalMemorySize;
    int minimumBlockSize;
    std::vector<MemoryHandling> memOperations;

    int bytesInUse;
    int allocatedBytes;
    int deallocatedBytes;
    int numAllocations;
    int numDeallocations;

public:
    MemoryManager(int totalSize, int minBlockSize)
        : totalMemorySize(totalSize), minimumBlockSize(minBlockSize), bytesInUse(0),
          allocatedBytes(0), deallocatedBytes(0), numAllocations(0), numDeallocations(0) {}

    virtual void allocate(int size) = 0; // Pure virtual function
    virtual void deallocate(int index) = 0; // Pure virtual function
    virtual void printMemory() const = 0; // Pure virtual function

    void addOperation(const MemoryHandling& operation) {
        memOperations.push_back(operation);
    }

    void executeOperations() {
        for (const auto& operation : memOperations) {
            if (operation.getAction() == 'A') {
                allocate(operation.getSize());
            } else if (operation.getAction() == 'D') {
                deallocate(operation.getId());
            }
        }
    }

    int getBytesInUse() const {
        return bytesInUse;
    }

    int getAllocatedBytes() const {
        return allocatedBytes;
    }

    int getDeallocatedBytes() const {
        return deallocatedBytes;
    }

    int getNumAllocations() const {
        return numAllocations;
    }

    int getNumDeallocations() const {
        return numDeallocations;
    }

    void printStatistics() const
    {
        std::cout << "Bytes in use: " << getBytesInUse() << std::endl;
        std::cout << "Allocated bytes: " << getAllocatedBytes() << std::endl;
        std::cout << "Deallocated bytes: " << getDeallocatedBytes() << std::endl;
        std::cout << "Number of allocations: " << getNumAllocations() << std::endl;
        std::cout << "Number of deallocations: " << getNumDeallocations() << std::endl;
    }
};

#endif // MEMORYMANAGER_H
