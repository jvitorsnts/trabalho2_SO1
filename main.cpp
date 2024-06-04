#include <iostream>
#include <vector>
#include "read_file.h"
#include "source/headers/Bitmap.h"
#include "source/headers/DoublyLinkedList.h"


using namespace std;

int main() {
    // Params *params;

    File f;
    f.read_file();
	f.printParams();
	// params = f.getParams();

    // Memoria de tantos bytes
    // Cada bloco com um quantidade minima de bytes
    // Memoria dividida em unidades de alocação
    // Bitmap: bit por unidade de alocação
    // LinkedList: lista encadeada
    // Requisitos: memoria para inserir os IDS             
}