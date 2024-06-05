#ifndef READ_FILE_H
#define READ_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "source/headers/MemoryHandling.h"
#include "source/headers/MemoryManager.h"
#include "source/headers/BitmapMemoryManager.h"
#include "source/headers/LinkedListMemoryManager.h"

using namespace std;

struct Params {
    int managementType; //1-Bitmap 2-DoublyLinkedList
    int memorySize; //Bytes
    int minBlock; //Bytes
    int alocationType; //1-? 2-?
	// seguido de uma sequencia de alocações e desalocações, que serao armazenadas em um vetor
    vector <MemoryHandling *> manages;
};

class File
{
private:
	ifstream myfile;
	Params *params;
	MemoryManager *memManager;

public:
	File() : params(new Params),  memManager(nullptr){
		myfile.open("entrada.txt");
		if (!myfile.is_open()) {
			cout << "Erro ao abrir o arquivo!\n";
		}
	}
	
	void read_file() {
		// configuração 
		// g: tipo de gerencia
		// m: tamanho de memoria livre
		// b: bloco
		// a: algoritmo de alocação
		int g, m, b, a;
		
		if (!myfile.is_open()) {
			cout << "Arquivo não está aberto!" << endl;
		}

		myfile >> g >> m >> b >> a;

		params->managementType = g;
		params->memorySize = m;
		params->minBlock = b;
		params->alocationType = a;

		// alocações e desalocações
		// ad: alocação ou desalocação
		// al: quantos bytes aloca
		// i: id
		char ad;
		int al, i;

		while (myfile >> ad)
		{
			MemoryHandling *h;
			if (ad == 'A') {
				myfile >> al >> i;
				h = new MemoryHandling(ad, al, i);
			} else {
				myfile >> i;
				h = new MemoryHandling(ad, 0, i);
			}
			params->manages.push_back(h);
		}

	}

	MemoryManager * createMemoryManager() {
		if (params->managementType == 1) {
			memManager = new BitmapMemoryManager(params->memorySize, params->minBlock, params->alocationType);
		} else {
			memManager = new LinkedListMemoryManager(params->memorySize, params->minBlock, params->alocationType);
		}

		// adds the operations to the memory manager
		auto iter = params->manages.begin();
		for(; iter < params->manages.end(); iter++) {
            MemoryHandling *h = *iter;
            memManager->addOperation(*h);
        }
		return memManager;
	}

	void printParams() {
		cout << "Tipo de gerência: " << params->managementType << endl;
		cout << "Tamanho memória: " << params->memorySize << endl;
		cout << "Bloco minimo: " << params->minBlock << endl;
		cout << "Algoritmo: " << params->alocationType << endl;
		
		auto iter = params->manages.begin();
		for(; iter < params->manages.end(); iter++) {
			MemoryHandling *h = *iter;
			cout << *h << endl;
		}
	}	

	Params * getParams() {
		return params;
	}

	MemoryManager * getMemoryManager() {
		return memManager;
	}
};

#endif //READ_FILE_H