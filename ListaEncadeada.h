#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H
#include "Huffman.h"
#include <iostream>
using namespace std;

template <typename T>
struct TElementoListaEncadeada {
	T dado;
	TElementoListaEncadeada* prox;
};

template <typename T>
struct TListaEncadeada {
	TElementoListaEncadeada<T>* inicio;
};

template <typename T>
void inicializarListaEncadeada(TListaEncadeada<T>& lista) {
	lista.inicio = NULL;
}

void insereLetraListaEncadeada(TListaEncadeada<TNoHuffman>& lista, char letra) {
	TElementoListaEncadeada<TNoHuffman>* nav = lista.inicio;

	// lista vazia
	if (nav == NULL) {
		TElementoListaEncadeada <TNoHuffman>* elemento = new TElementoListaEncadeada <TNoHuffman>;
		elemento->dado.letra = letra;
		elemento->dado.frequencia = 1;
		elemento->dado.direita = NULL;
		elemento->dado.esquerda = NULL;
		elemento->prox = NULL;
		lista.inicio = elemento;
		return;
	}

	// percorre toda a lista ate achar a letra ou para no ultimo elemento
	while (nav->prox != NULL) {
		// caso encontra a letra, apenas incrementa a frequencia
		if (nav->dado.letra == letra) {
			nav->dado.frequencia++;
			return;
		}

		nav = nav->prox;
	}

	// caso nao encontre a letra na lista, cria-se um elemento do tipo noHuffman e insere no fim da lista
	TElementoListaEncadeada <TNoHuffman>* elemento = new TElementoListaEncadeada <TNoHuffman>;
	elemento->dado.letra = letra;
	elemento->dado.frequencia = 1;
	elemento->dado.direita = NULL;
	elemento->dado.esquerda = NULL;
	elemento->prox = NULL;
	nav->prox = elemento;
}

void imprimeListaEncadeadaHuffman(TListaEncadeada<TNoHuffman> lista) {
	if (lista.inicio == NULL) {
		cout << "Lista Vazia!" << endl;
		return;
	}
	else {
		for (TElementoListaEncadeada<TNoHuffman>* nav = lista.inicio; nav != NULL; nav = nav->prox) {
			cout << nav->dado.letra << " - " << nav->dado.frequencia << endl;
		}
	}
}

void insereNoPosicaoListaEncadeada(TListaEncadeada<TNoHuffman>& lista, TNoHuffman no, int posicao) {
	if (posicao < 0) { // posicao < 0
		cout << "Erro: Indice < 0";
		return;
	}
	else if (posicao == 0) { // posicao 0
		TElementoListaEncadeada <TNoHuffman>* elemento = new TElementoListaEncadeada<TNoHuffman>;
		elemento->dado = no;
		elemento->prox = lista.inicio;
		lista.inicio = elemento;
		return;
	}
	else {  // posicao 1 em diante
		TElementoListaEncadeada<TNoHuffman>* nav = lista.inicio;
		int contador = 0;

		while (nav != nullptr && contador < posicao - 1) {
			nav = nav->prox;
			contador++;
		}

		if (nav != nullptr) {
			if (nav->prox == NULL) { // posicao == ultima da lista
				TElementoListaEncadeada<TNoHuffman>* elemento = new TElementoListaEncadeada<TNoHuffman>;
				elemento->dado = no;
				elemento->prox = NULL;
				nav->prox = elemento;
				return;
			}
			else {  // posica > 1 && posicao < ultima da lista
				TElementoListaEncadeada<TNoHuffman>* elemento = new TElementoListaEncadeada<TNoHuffman>;
				elemento->dado = no;

				elemento->prox = nav->prox;
				nav->prox = elemento;
			}
		}
	}
}

TNoHuffman removeNoPosicaoListaEncadeada(TListaEncadeada<TNoHuffman>& lista, int posicao) {
	if (posicao < 0) {
		cout << "Erro: indice < 0" << endl;
	}
	else if (posicao == 0) {
		TElementoListaEncadeada<TNoHuffman>* apagar = lista.inicio;
		TNoHuffman removido = apagar->dado;
		lista.inicio = lista.inicio->prox;
		delete apagar;
		return removido;
	}
	else {

		TElementoListaEncadeada<TNoHuffman>* nav = lista.inicio;
		int contador = 0;
		while (nav != nullptr && contador < posicao - 1) {
			nav = nav->prox;
			contador++;
		}

		TElementoListaEncadeada<TNoHuffman>* apagar = nav->prox;
		nav->prox = apagar->prox;
		TNoHuffman removido = apagar->dado;
		delete apagar;
		return removido;
	}
}

int descobreIndiceNo(TListaEncadeada<TNoHuffman> lista, char letra) {
	int posicao = 0;
	for (TElementoListaEncadeada<TNoHuffman>* nav = lista.inicio; nav != NULL; nav = nav->prox) {
		if (nav->dado.letra == letra) {
			return posicao;
		}
		posicao++;
	}

	// quando nao encontra a letra
	return -1;
}

TNoHuffman obtemItemListaEncadeada(TListaEncadeada<TNoHuffman> lista, int posicao) {
	if (posicao < 0) { // posicao < 0
		cout << "Erro: Indice < 0";
	}
	else { // posicao 0 em diante
		TElementoListaEncadeada<TNoHuffman>* nav = lista.inicio;
		int contador = 0;
		while (nav != nullptr && contador < posicao) {
			nav = nav->prox;
			contador++;
		}

		if (nav != nullptr) {
			return nav->dado;
		}
	}
}

void ordenarListaEncadeada(TListaEncadeada<TNoHuffman>& lista) {
	if (lista.inicio == NULL) {
		cout << "Lista Vazia!";
		return;
	}

	int quantidade = 0;
	TElementoListaEncadeada<TNoHuffman>* nav = lista.inicio;

	while (nav != NULL) { // descobrir quantas posicoes tem a lista
		nav = nav->prox;
		quantidade++;
	}

	int rodada, indice;
	TElementoListaEncadeada<TNoHuffman> temp1;
	TElementoListaEncadeada<TNoHuffman> temp2;

	for (rodada = 0; rodada < quantidade - 1; rodada++) {
		for (indice = 0; indice < quantidade - rodada - 1; indice++) {
			temp1.dado = obtemItemListaEncadeada(lista, indice);
			temp2.dado = obtemItemListaEncadeada(lista, indice + 1);

			if (temp1.dado.frequencia > temp2.dado.frequencia) { //ordena a frequencia crescente
				temp1.dado = temp2.dado;
				removeNoPosicaoListaEncadeada(lista, indice + 1);
				insereNoPosicaoListaEncadeada(lista, temp1.dado, indice);
			}

			if (temp1.dado.frequencia == temp2.dado.frequencia) { //ordena em ordem alfabetica as frequencias iguais
				if (temp1.dado.letra > temp2.dado.letra) {
					temp1.dado = temp2.dado;
					removeNoPosicaoListaEncadeada(lista, indice + 1);
					insereNoPosicaoListaEncadeada(lista, temp1.dado, indice);
				}
			}
		}
	}
}

#endif	// LISTAENCADEADA_H

