//
// Created by gabri on 04/06/2024.
//

// BitmapMemoryManager.h
#ifndef BITMAPMEMORYMANAGER_H
#define BITMAPMEMORYMANAGER_H

#include "MemoryManager.h"
#include <vector>

class BitmapMemoryManager : public MemoryManager {
private:
    std::vector<int> memoryBitmap;

public:
    BitmapMemoryManager(int totalSize, int minBlockSize, int allocType)
        : MemoryManager(totalSize, minBlockSize, allocType), memoryBitmap(totalSize / minBlockSize, 0) {}

    void allocate(int size) override;
    void deallocate(int index) override;
    void printMemory() const override;

    int firstFit(int size) override;
    int nextFit(int size) override;
};

#endif // BITMAPMEMORYMANAGER_H