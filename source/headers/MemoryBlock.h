#ifndef MEMORYBLOCK_H
#define MEMORYBLOCK_H

#include <iostream>

using namespace std;


class MemoryBlock
{
private:
    int id;
    int start;
    int size;
    bool free;
    MemoryBlock* nextBlock;
    MemoryBlock* previousBlock;

public:
	MemoryBlock(int id, int start, int size, bool isFree, MemoryBlock* nextBlock, MemoryBlock* previousBlock);
	
	void addSize(int toAdd);

   // Getters
    int getId() const;
    int getStart() const;
    int getSize() const;
    bool isFree() const;
    MemoryBlock* getNextBlock() const;
    MemoryBlock* getPreviousBlock() const;

    // Setters
    void setId(int id);
    void setStart(int start);
    void setSize(int size);
    void setFree(bool value);
    void setNextBlock(MemoryBlock* nextBlock);
    void setPreviousBlock(MemoryBlock* previousBlock);
};

#endif // MEMORYBLOCK_H
