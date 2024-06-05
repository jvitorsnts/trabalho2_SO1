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
    int managerIndex = 0;  //Ultimo indice da gerencia de memoria(usado para nextFit)

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
    MemoryManager(int totalSize, int minBlockSize, int allocType);

    virtual int allocate(int size) = 0; // Pure virtual function
    virtual void deallocate(int index) = 0; // Pure virtual function
    virtual void printMemory() const = 0; // Pure virtual function

    virtual int firstFit(int size) = 0;
    virtual int nextFit(int size) = 0;

    void printStatistics() const;

    void addOperation( MemoryHandling& operation);
    void executeOperations();

    int getBytesInUse() const;
    int getAllocatedBytes() const;
    int getDeallocatedBytes() const;
    int getNumAllocations() const;
    int getNumDeallocations() const;
};

#endif // MEMORYMANAGER_H
