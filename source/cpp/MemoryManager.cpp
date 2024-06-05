//
// Created by gabri on 04/06/2024.
//

#include "../headers/MemoryManager.h"
#include <iostream>

void MemoryManager::printStatistics() const {
    std::cout << getBytesInUse() << std::endl; // quantidade de bytes em uso (ocupados)
    std::cout << getAllocatedBytes() << std::endl; // quantidade de bytes alocados
    std::cout << getDeallocatedBytes() << std::endl; // quantidade de bytes desalocados
    std::cout << getNumAllocations() << std::endl; // número de alocações
    std::cout << getNumDeallocations() << std::endl; // número de desalocações
}