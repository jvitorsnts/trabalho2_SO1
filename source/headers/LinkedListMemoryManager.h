//
// Created by gabri on 04/06/2024.
//

// LinkedListMemoryManager.h
#ifndef LINKEDLISTMEMORYMANAGER_H
#define LINKEDLISTMEMORYMANAGER_H

#include "MemoryManager.h"
#include <list>

struct MemoryBlock {
    int id;
    int start;
    int size;
    bool isFree;
    MemoryBlock* nextBlock;
    MemoryBlock* previousBlock;
};

class LinkedListMemoryManager : public MemoryManager {
private:
    MemoryBlock* head;
    MemoryBlock* lastAllocated;  // Novo atributo para armazenar o último bloco utilizado (next fit)

public:
    LinkedListMemoryManager(int totalSize, int minBlockSize, int allocType);

    int allocate(int size) override;
    void deallocate(int index) override;
    void printMemory() const override;
    void allocateMemory(MemoryBlock* current, int size);

    int firstFit(int size) override;
    int nextFit(int size) override;
};

#endif // LINKEDLISTMEMORYMANAGER_H