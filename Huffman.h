#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
using namespace std;

struct TNoHuffman {
	int frequencia;
	char letra;
	TNoHuffman* esquerda;
	TNoHuffman* direita;
};

struct TabelaHuffman {
	char letra;
	string codigo;
};

TNoHuffman* criarNoPai(TNoHuffman* no1, TNoHuffman* no2) {
	TNoHuffman* noPai = new TNoHuffman;

	noPai->letra = NULL;
	noPai->frequencia = no1->frequencia + no2->frequencia;
	noPai->esquerda = no1;
	noPai->direita = no2;

	return noPai;
}

void preFixa(TNoHuffman* no, int nivel) {
	if (no) {
		for (int i = 0; i < nivel; i++) {
			cout << "\t";
		}
		cout << "No - freq: " << no->frequencia << " - char: " << no->letra << endl;
		preFixa(no->esquerda, nivel + 1);
		preFixa(no->direita, nivel + 1);
	}
}

#endif //HUFFMAN_H