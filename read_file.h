#ifndef READ_FILE_H
#define READ_FILE_H

#endif //READ_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Params {
    int managementType; //1-Bitmap 2-DoublyLinkedList
    int memorySize; //Bytes
    int minBlock; //Bytes
    int alocationType; //1-? 2-?
    vector<MemoryHandling *> manages; //Alocações e desalocações
};

class MemoryHandling
{
private:
    char action;
    int size;
    int id;

public:
	MemoryHandling(char a, int s, int i) {
		action = a;
		size = s;
		id = i;
	}
	
    char getAction() const {
        return action;
    }

    int getSize() const {
        return size;
    }

    int getId() const {
        return id;
    }

	friend ostream &operator<<(ostream& os, const MemoryHandling& h) {
		os <<
			"action = " << h.action <<
				" size = " << h.size <<
					" id = " << h.id << endl;
		return os;
	}
};

class File
{
private:
	ifstream myfile;
	Params *params;

public:
	File() {
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
		int ad, al, i;

		while (myfile >> ad) {
			if (ad == 'A') {
				myfile >> al >> i;
				auto *h = new MemoryHandling(ad, al, i);
			} else {
				myfile >> i;
				auto *h = new MemoryHandling(ad, 0, i);
			}
		}
	}

	void printParams() {
		cout << "Tipo de gerência: " << params->managementType;
		cout << "Tamanho memória: " << params->memorySize;
		cout << "Bloco minimo: " << params->minBlock;
		cout << "Algoritmo: " << params->alocationType;
		
		auto iter = params->manages.begin();
		for(; iter < params->manages.end(); iter++) {
			MemoryHandling *h = *iter;
			cout << *h;
		}
	}	

	Params * getParams() {
		return params;
	}
};