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
    BitmapMemoryManager(int totalSize, int minBlockSize)
        : MemoryManager(totalSize, minBlockSize), memoryBitmap(totalSize / minBlockSize, 0) {}

    void allocate(int size) override;
    void deallocate(int index) override;
    void printMemory() const override;
};

#endif // BITMAPMEMORYMANAGER_H