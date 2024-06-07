//
// Created by gabri on 04/06/2024.
//

// LinkedListMemoryManager.cpp
#include "../headers/LinkedListMemoryManager.h"
#include <iostream>

LinkedListMemoryManager::LinkedListMemoryManager(int totalSize, int minBlockSize, int allocType)
    : MemoryManager(totalSize, minBlockSize, allocType) {
        MemoryBlock* memBlock = new MemoryBlock(0, totalSize, true, nullptr, nullptr);

        head = memBlock;
}

int LinkedListMemoryManager::allocate(int size) {
    // Implement the allocate method using a linked list
    // prints the size for now

    //std::cout << "Allocating " << size << " bytes" << std::endl;
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
        //std::cout << "Block allocated at address " << startAddress << std::endl;
    } else {
        //std::cout << "Block could not be allocated" << std::endl;
    }
    return startAddress;
}

void LinkedListMemoryManager::deallocate(int id) {
    // Implement the deallocate method
        // prints the index for now
    //cout<<"Finding dealocate"<<endl;
     for (auto& operation : memOperations) {
        if(operation.getId() == id){
            int blocks = operation.getSize() / minimumBlockSize + (operation.getSize() % minimumBlockSize != 0);
            deallocatedBytes += blocks * minimumBlockSize;
            numDeallocations++;
            
             MemoryBlock* current = head;

            // Encontra o bloco com o endereço inicial especificado
            while (current != nullptr) {
                if (current->getStart() == operation.getIndex()) {
                    // Marca o bloco como livre
                    current->setFree(true);

                    // Tenta combinar com o bloco anterior, se estiver livre
                    if (current->getPreviousBlock() && current->getPreviousBlock()->isFree()) {
                        MemoryBlock* prevBlock = current->getPreviousBlock();
                        prevBlock->addSize(current->getSize());
                        prevBlock->setNextBlock(current->getNextBlock());

                        if (current->getNextBlock()) {
                            current->getNextBlock()->setPreviousBlock(prevBlock);
                        }

                        delete current;
                        current = prevBlock;
                    }

                    // Tenta combinar com o próximo bloco, se estiver livre
                    if (current->getNextBlock() && current->getNextBlock()->isFree()) {
                        MemoryBlock* nextBlock = current->getNextBlock();
                        current->addSize(nextBlock->getSize());
                        current->setNextBlock(nextBlock->getNextBlock());

                        if (nextBlock->getNextBlock()) {
                            nextBlock->getNextBlock()->setPreviousBlock(current);
                        }

                        delete nextBlock;
                    }

                    return;
                }

                current = current->getNextBlock();
            }
            break;
        }
            
     }

    //cout << "Deallocating block of id " << id << endl;
}

void LinkedListMemoryManager::printMemory() const {
    // Implement the printMemory method
    //std::cout << "Printing memory" << std::endl;
    MemoryBlock* current = head;
    while (current != nullptr) {
        std::cout <<  current->getSize() << " "
                  << (current->isFree() ? "0" : "1") << std::endl;
        current = current->getNextBlock();
    }
}

int LinkedListMemoryManager::firstFit(int size) {
    // Ponteiro para percorrer a lista de blocos de memória
    MemoryBlock* current = head;

    // Tamanho ocupado pela alocação considerando o bloco minimo
    while (size%minimumBlockSize != 0) {
        size++;
    } 

    // Percorre a lista de blocos para encontrar o primeiro bloco livre que seja grande o suficiente
    while (current != nullptr) {
        if (current->isFree() && current->getSize() >= size) {
            // Se o bloco é grande o suficiente, aloca a memória
            int startAddress = current->getStart();

            allocateMemory(current, size);

            return startAddress; // Retorna o endereço inicial do bloco alocado
        }

        // Avança para o próximo bloco
        current = current->getNextBlock();
    }

    //std::cout << "First fit" << std::endl;
    //cout << size << endl;
    return -1; // Se não encontrou um bloco grande o suficiente, retorna -1
}

void allocateMemory(MemoryBlock* current, int size){
    // Se o bloco é exatamente do tamanho requerido, marca-o como ocupado
    if (current->getSize() == size) {
        current->setFree(false);
    } else {
        // Caso contrário, divide o bloco em dois
        MemoryBlock* newBlock = new MemoryBlock(current->getStart() + size, current->getSize() - size, true, current->getNextBlock(), current);

        if (current->getNextBlock()) {
            current->getNextBlock()->setPreviousBlock(newBlock);
        }

        current->setNextBlock(newBlock);
        current->setSize(size);
        current->setFree(false);
    }
}

int LinkedListMemoryManager::nextFit(int size) {
    // finds the next sequence of blocks that are empty and have enough space to allocate the size
    // and then fills the blocks with 1 and returns the index of the first block

    // Ponteiro para percorrer a lista de blocos de memória, começando do último bloco utilizado
    MemoryBlock* current = lastAllocated ? lastAllocated : head;
    MemoryBlock* startPoint = current;

    // Tamanho ocupado pela alocação considerando o bloco minimo
    while (size%minimumBlockSize != 0) {
        size++;
    } 

    do {
        if (current->isFree() && current->getSize() >= size) {
            // Se o bloco é grande o suficiente, aloca a memória
            int startAddress = current->getStart();

            // Atualiza o ponteiro do último bloco utilizado
            lastAllocated = current;

            return startAddress; // Retorna o endereço inicial do bloco alocado
        }

        // Avança para o próximo bloco
        current = current->getNextBlock() ? current->getNextBlock() : head;
    } while (current != startPoint);
    
    //std::cout << "Next fit" << std::endl;
    //cout << size << endl;
    return -1; // Se não encontrou um bloco grande o suficiente, retorna -1
}