#ifndef MEMORYHANDLING_H
#define MEMORYHANDLING_H

#include <iostream>

using namespace std;

class MemoryHandling
{
private:
    char action;
    int size;
    int id;

public:
	MemoryHandling(char a, int s, int i);
	
    char getAction() const;

    int getSize() const;

    int getId() const;

	friend ostream &operator<<(ostream& os, const MemoryHandling& h) {
		os <<
			"action = " << h.action <<
				" size = " << h.size <<
					" id = " << h.id << endl;
		return os;
	}
};

#endif // MEMORYHANDLING_H
