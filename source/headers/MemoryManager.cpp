//
// Created by gabri on 04/06/2024.
//

#include "MemoryManager.h"
#include <iostream>

void MemoryManager::printStatistics() const {
    std::cout << "Bytes in use: " << getBytesInUse() << std::endl;
    std::cout << "Allocated bytes: " << getAllocatedBytes() << std::endl;
    std::cout << "Deallocated bytes: " << getDeallocatedBytes() << std::endl;
    std::cout << "Number of allocations: " << getNumAllocations() << std::endl;
    std::cout << "Number of deallocations: " << getNumDeallocations() << std::endl;
}