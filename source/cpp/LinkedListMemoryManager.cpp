//
// Created by gabri on 04/06/2024.
//

// LinkedListMemoryManager.cpp
#include "../headers/LinkedListMemoryManager.h"
#include <iostream>

LinkedListMemoryManager::LinkedListMemoryManager(int totalSize, int minBlockSize, int allocType)
    : MemoryManager(totalSize, minBlockSize, allocType) {
        MemoryBlock* memBlock = new MemoryBlock;
        memBlock->size = totalSize;
        memBlock->start = 0;
        memBlock->isFree = true;
        memBlock->nextBlock = nullptr;
        memBlock->previousBlock = nullptr;

        head = memBlock;
}

int LinkedListMemoryManager::allocate(int size) {
    // Implement the allocate method using a linked list
    // prints the size for now

    std::cout << "Allocating " << size << " bytes" << std::endl;
    int startAddress = 0;
    if (allocationType == 1) {
        startAddress = firstFit(size);
    } else {
        startAddress = nextFit(size);
    }

    if (startAddress != -1) {
        int blocksNeeded = size / minimumBlockSize + (size % minimumBlockSize != 0);
        allocatedBytes += blocksNeeded * minimumBlockSize;
        numAllocations++;
        std::cout << "Block allocated at address " << startAddress << std::endl;
    } else {
        std::cout << "Block could not be allocated" << std::endl;
    }
    return startAddress;
}

void LinkedListMemoryManager::deallocate(int id) {
    // Implement the deallocate method
        // prints the index for now
    cout<<"Finding dealocate"<<endl;
     for (auto& operation : memOperations) {
        if(operation.getId() == id){
            int blocks = operation.getSize() / minimumBlockSize + (operation.getSize() % minimumBlockSize != 0);
            deallocatedBytes += blocks * minimumBlockSize;
            numDeallocations++;
            
             MemoryBlock* current = head;

            // Encontra o bloco com o endereço inicial especificado
            while (current != nullptr) {
                if (current->start == operation.getIndex()) {
                    // Marca o bloco como livre
                    current->isFree = true;

                    // Tenta combinar com o bloco anterior, se estiver livre
                    if (current->previousBlock && current->previousBlock->isFree) {
                        MemoryBlock* prevBlock = current->previousBlock;
                        prevBlock->size += current->size;
                        prevBlock->nextBlock = current->nextBlock;

                        if (current->nextBlock) {
                            current->nextBlock->previousBlock = prevBlock;
                        }

                        delete current;
                        current = prevBlock;
                    }

                    // Tenta combinar com o próximo bloco, se estiver livre
                    if (current->nextBlock && current->nextBlock->isFree) {
                        MemoryBlock* nextBlock = current->nextBlock;
                        current->size += nextBlock->size;
                        current->nextBlock = nextBlock->nextBlock;

                        if (nextBlock->nextBlock) {
                            nextBlock->nextBlock->previousBlock = current;
                        }

                        delete nextBlock;
                    }

                    return;
                }

                current = current->nextBlock;
            }
            break;
        }
            
     }

    cout << "Deallocating block of id " << id << endl;
}

void LinkedListMemoryManager::printMemory() const {
    // Implement the printMemory method
    std::cout << "Printing memory" << std::endl;
    MemoryBlock* current = head;
    while (current != nullptr) {
        std::cout <<  current->size << ", "
                  << (current->isFree ? "0" : "1") << std::endl;
        current = current->nextBlock;
    }
}

int LinkedListMemoryManager::firstFit(int size) {
    // Ponteiro para percorrer a lista de blocos de memória
    MemoryBlock* current = head;

    // Percorre a lista de blocos para encontrar o primeiro bloco livre que seja grande o suficiente
    while (current != nullptr) {
        if (current->isFree && current->size >= size) {
            // Se o bloco é grande o suficiente, aloca a memória
            int startAddress = current->start;

            // Se o bloco é exatamente do tamanho requerido, marca-o como ocupado
            if (current->size == size) {
                current->isFree = false;
            } else {
                // Caso contrário, divide o bloco em dois
                MemoryBlock* newBlock = new MemoryBlock;
                newBlock->start = current->start + size;
                newBlock->size = current->size - size;
                newBlock->isFree = true;
                newBlock->nextBlock = current->nextBlock;
                newBlock->previousBlock = current;

                if (current->nextBlock) {
                    current->nextBlock->previousBlock = newBlock;
                }

                current->nextBlock = newBlock;
                current->size = size;
                current->isFree = false;
            }

            return startAddress; // Retorna o endereço inicial do bloco alocado
        }

        // Avança para o próximo bloco
        current = current->nextBlock;
    }

    std::cout << "First fit" << std::endl;
    cout << size << endl;
    return -1; // Se não encontrou um bloco grande o suficiente, retorna -1
}

int LinkedListMemoryManager::nextFit(int size) {
    // finds the next sequence of blocks that are empty and have enough space to allocate the size
    // and then fills the blocks with 1 and returns the index of the first block

    // Ponteiro para percorrer a lista de blocos de memória, começando do último bloco utilizado
    MemoryBlock* current = lastAllocated ? lastAllocated : head;
    MemoryBlock* startPoint = current;

    do {
        if (current->isFree && current->size >= size) {
            // Se o bloco é grande o suficiente, aloca a memória
            int startAddress = current->start;

            // Se o bloco é exatamente do tamanho requerido, marca-o como ocupado
            if (current->size == size) {
                current->isFree = false;
            } else {
                // Caso contrário, divide o bloco em dois
                MemoryBlock* newBlock = new MemoryBlock;
                newBlock->start = current->start + size;
                newBlock->size = current->size - size;
                newBlock->isFree = true;
                newBlock->nextBlock = current->nextBlock;
                newBlock->previousBlock = current;

                if (current->nextBlock) {
                    current->nextBlock->previousBlock = newBlock;
                }

                current->nextBlock = newBlock;
                current->size = size;
                current->isFree = false;
            }

            // Atualiza o ponteiro do último bloco utilizado
            lastAllocated = current;

            return startAddress; // Retorna o endereço inicial do bloco alocado
        }

        // Avança para o próximo bloco
        current = current->nextBlock ? current->nextBlock : head;
    } while (current != startPoint);
    
    std::cout << "Next fit" << std::endl;
    cout << size << endl;
    return -1; // Se não encontrou um bloco grande o suficiente, retorna -1
}