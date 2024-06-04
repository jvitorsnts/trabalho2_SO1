#ifndef BITMAP_H
#define BITMAP_H

#include <vector>
#include "Memory.h"
#include "MemoryHandling.h"

class Bitmap : public Memory{
public:
    Bitmap(int memory_size, vector<MemoryHandling *> actions);
protected:
};

#endif //BITMAP_H