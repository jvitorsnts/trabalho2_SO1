#include <iostream>
#include "../headers/MemoryHandling.h"

using namespace std;

MemoryHandling::MemoryHandling(char a, int s, int i) {
    action = a; //A-alocar D-desalocar
    size = s; //Bytes de alocação
    id = i; //Id do processo
}

char MemoryHandling::getAction() const {
    return action;
}

int MemoryHandling::getSize() const {
    return size;
}

int MemoryHandling::getId() const {
    return id;
}