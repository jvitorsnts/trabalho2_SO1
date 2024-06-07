#include <iostream>
#include "../headers/MemoryBlock.h"

using namespace std;

MemoryBlock::MemoryBlock(int id, int start, int size, bool isFree, MemoryBlock* nextBlock, MemoryBlock* previousBlock) {
    this->id = id;
    this->start = start;
    this->size = size;
    this->free = isFree;
    this->nextBlock = nextBlock;
    this->previousBlock = previousBlock;
}

void MemoryBlock::addSize(int toAdd){
    this->size += toAdd;
}


int MemoryBlock::getId() const {
    return id;
}

int MemoryBlock::getStart() const {
    return start;
}

int MemoryBlock::getSize() const {
    return size;
}

bool MemoryBlock::isFree() const {
    return free;
}

MemoryBlock* MemoryBlock::getNextBlock() const {
    return nextBlock;
}

MemoryBlock* MemoryBlock::getPreviousBlock() const {
    return previousBlock;
}


void MemoryBlock::setId(int id) {
    this->id = id;
}

void MemoryBlock::setStart(int start) {
    this->start = start;
}

void MemoryBlock::setSize(int size) {
    this->size = size;
}

void MemoryBlock::setFree(bool value) {
    this->free = value;
}

void MemoryBlock::setNextBlock(MemoryBlock* nextBlock) {
    this->nextBlock = nextBlock;
}

void MemoryBlock::setPreviousBlock(MemoryBlock* previousBlock) {
    this->previousBlock = previousBlock;
}