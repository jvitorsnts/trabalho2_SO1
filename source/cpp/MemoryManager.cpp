//
// Created by gabri on 04/06/2024.
//

#include "../headers/MemoryManager.h"
#include <iostream>

MemoryManager::MemoryManager(int totalSize, int minBlockSize, int allocType)
    : totalMemorySize(totalSize), minimumBlockSize(minBlockSize), allocationType(allocType),bytesInUse(0),
        allocatedBytes(0), deallocatedBytes(0), numAllocations(0), numDeallocations(0) {}

void MemoryManager::printStatistics() const {
    std::cout << getBytesInUse() << std::endl; // quantidade de bytes em uso (ocupados)
    std::cout << getAllocatedBytes() << std::endl; // quantidade de bytes alocados
    std::cout << getDeallocatedBytes() << std::endl; // quantidade de bytes desalocados
    std::cout << getNumAllocations() << std::endl; // número de alocações
    std::cout << getNumDeallocations() << std::endl; // número de desalocações
}

void MemoryManager::addOperation( MemoryHandling& operation) {
    memOperations.push_back(operation);
}

void MemoryManager::executeOperations() {
    for (auto& operation : memOperations) {
        int index;
        if (operation.getAction() == 'A') {
            index = allocate(operation.getSize());

            operation.setIndex(index);
            cout << "operation index (LL)" << operation.getIndex() << endl << endl;
        } else if (operation.getAction() == 'D') {
            deallocate(operation.getId());
            cout << endl;
        }
    }
}
int MemoryManager::getBytesInUse() const {
    return bytesInUse;
}

int MemoryManager::getAllocatedBytes() const {
    return allocatedBytes;
}

int MemoryManager::getDeallocatedBytes() const {
    return deallocatedBytes;
}

int MemoryManager::getNumAllocations() const {
    return numAllocations;
}

int MemoryManager::getNumDeallocations() const {
    return numDeallocations;
}