#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include <vector>
#include "Memory.h"
#include "MemoryHandling.h"

class DoublyLinkedList : public Memory{
public:
    DoublyLinkedList(int memory_size, vector<MemoryHandling *> actions);
protected:
};

#endif //DOUBLYLINKEDLIST_Hs