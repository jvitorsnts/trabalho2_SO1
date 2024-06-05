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
    int allocationType;
    std::vector<MemoryHandling> memOperations;

    int bytesInUse;
    int allocatedBytes;
    int deallocatedBytes;
    int numAllocations;
    int numDeallocations;

public:
    MemoryManager(int totalSize, int minBlockSize, int allocType)
        : totalMemorySize(totalSize), minimumBlockSize(minBlockSize), allocationType(allocType),bytesInUse(0),
          allocatedBytes(0), deallocatedBytes(0), numAllocations(0), numDeallocations(0) {}

    virtual int allocate(int size) = 0; // Pure virtual function
    virtual void deallocate(int index) = 0; // Pure virtual function
    virtual void printMemory() const = 0; // Pure virtual function

    virtual int firstFit(int size) = 0;
    virtual int nextFit(int size) = 0;

    void printStatistics() const;

    void addOperation( MemoryHandling& operation) {
        memOperations.push_back(operation);
    }

    void executeOperations() {
        for (auto& operation : memOperations) {
            int index;
            if (operation.getAction() == 'A') {
                index = allocate(operation.getSize());

                operation.setIndex(index);
                cout << "operation index " << operation.getIndex() << endl;
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
};

#endif // MEMORYMANAGER_H
