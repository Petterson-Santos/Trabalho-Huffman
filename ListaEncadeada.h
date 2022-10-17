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

void incrementaFrequencia(char letra, TListaEncadeada<TNoHuffman*> &lista) {
	for (TElementoListaEncadeada<TNoHuffman*>* nav = lista.inicio; nav != NULL; nav = nav->prox) {
		if (letra == nav->dado->letra) {
			nav->dado->frequencia++;
		}
	}
}

bool existeNaLista(char letra, TListaEncadeada<TNoHuffman*> lista) {
	for (TElementoListaEncadeada<TNoHuffman*>* nav = lista.inicio; nav != NULL; nav = nav->prox) {
		if (letra == nav->dado->letra) {
			return true;
		}
	}
	return false;
}

void imprimeListaEncadeadaHuffman(TListaEncadeada<TNoHuffman*> lista) {
	if (lista.inicio == NULL) {
		cout << "Lista Vazia!" << endl;
		return;
	}
	else {
		for (TElementoListaEncadeada<TNoHuffman*>* nav = lista.inicio; nav != NULL; nav = nav->prox) {
			cout << nav->dado->letra << " - " << nav->dado->frequencia << endl;
		}
	}
}

void imprimirTabelaHuffman(TListaEncadeada<TabelaHuffman *> lista) {
	if (lista.inicio == NULL) {
		cout << "Lista Vazia!" << endl;
		return;
	}
	else {
		for (TElementoListaEncadeada<TabelaHuffman*>* nav = lista.inicio; nav != NULL; nav = nav->prox) {
			cout << nav->dado->letra << " - " << nav->dado->codigo << endl;
		}
	}
}

void insereFimTabela(TListaEncadeada<TabelaHuffman *>& lista, TabelaHuffman* novoElemento) {
	TElementoListaEncadeada<TabelaHuffman*>* elemento = new TElementoListaEncadeada<TabelaHuffman*>;
	elemento->dado = novoElemento;
	elemento->prox = NULL;

	if (lista.inicio == NULL) {
		lista.inicio = elemento;
		return;
	}

	TElementoListaEncadeada<TabelaHuffman*>* nav = lista.inicio;

	while (nav->prox != NULL) {
		nav = nav->prox;
	}

	nav->prox = elemento;
}

void insereNoFimLista(TListaEncadeada<TNoHuffman*>& lista, TNoHuffman* no) {
	TElementoListaEncadeada<TNoHuffman*>* elemento = new TElementoListaEncadeada<TNoHuffman*>;
	elemento->dado = no;
	elemento->prox = NULL;
	
	if (lista.inicio == NULL) {
		lista.inicio = elemento;
		return;
	}

	TElementoListaEncadeada<TNoHuffman*>* nav = lista.inicio;

	while (nav->prox != NULL) {
		nav = nav->prox;
	}

	nav->prox = elemento;
}

void insereNoPosicaoListaEncadeada(TListaEncadeada<TNoHuffman*>& lista, TNoHuffman* no, int posicao) {
	if (posicao < 0) { // posicao < 0
		cout << "Erro: Indice < 0";
		return;
	}
	else if (posicao == 0) { // posicao 0
		TElementoListaEncadeada <TNoHuffman*>* elemento = new TElementoListaEncadeada<TNoHuffman*>;
		elemento->dado = no;
		elemento->prox = lista.inicio;
		lista.inicio = elemento;
		return;
	}
	else {  // posicao 1 em diante
		TElementoListaEncadeada<TNoHuffman*>* nav = lista.inicio;
		int contador = 0;

		while (nav != nullptr && contador < posicao - 1) {
			nav = nav->prox;
			contador++;
		}

		if (nav != nullptr) {
			if (nav->prox == NULL) { // posicao == ultima da lista
				TElementoListaEncadeada<TNoHuffman*>* elemento = new TElementoListaEncadeada<TNoHuffman*>;
				elemento->dado = no;
				elemento->prox = NULL;
				nav->prox = elemento;
				return;
			}
			else {  // posica > 1 && posicao < ultima da lista
				TElementoListaEncadeada<TNoHuffman*>* elemento = new TElementoListaEncadeada<TNoHuffman*>;
				elemento->dado = no;

				elemento->prox = nav->prox;
				nav->prox = elemento;
			}
		}
	}
}

TNoHuffman* removeNoPosicaoListaEncadeada(TListaEncadeada<TNoHuffman*>& lista, int posicao) {
	if (posicao == 0) {
		TElementoListaEncadeada<TNoHuffman*>* apagar = lista.inicio;
		TNoHuffman* removido = apagar->dado;
		lista.inicio = lista.inicio->prox;
		delete apagar;
		return removido;
	}
	else {

		TElementoListaEncadeada<TNoHuffman*>* nav = lista.inicio;
		int contador = 0;
		while (nav != nullptr && contador < posicao - 1) {
			nav = nav->prox;
			contador++;
		}

		TElementoListaEncadeada<TNoHuffman*>* apagar = nav->prox;
		nav->prox = apagar->prox;
		TNoHuffman* removido = apagar->dado;
		delete apagar;
		return removido;
	}
}

TNoHuffman* obtemItemListaEncadeada(TListaEncadeada<TNoHuffman*> lista, int posicao) {
	TElementoListaEncadeada<TNoHuffman*>* nav = lista.inicio;
	int contador = 0;
	while (nav != nullptr && contador < posicao) {
		nav = nav->prox;
		contador++;
	}

	if (nav != nullptr) {
		return nav->dado;
	}
}

TListaEncadeada<TNoHuffman*> criaNovaLista(string frase) {
	TListaEncadeada <TNoHuffman*> lista;
	inicializarListaEncadeada(lista);

	for (int i = 0; i < frase.length(); i++) {
		char atual = frase[i];
		if (existeNaLista(atual, lista)) {
			incrementaFrequencia(atual, lista);
		}
		else {
			TNoHuffman* novoNo = new TNoHuffman;
			novoNo->letra = atual;
			novoNo->frequencia = 1;
			novoNo->esquerda = novoNo->direita = nullptr;
			insereNoFimLista(lista, novoNo);
		}
	}

	return lista;
}

void criaNovaTabela(TNoHuffman* no, string codigo, TListaEncadeada<TabelaHuffman*> &tabela) {
	if (no) {
		if (no->letra != '\0') {
			TabelaHuffman* novoElemento = new TabelaHuffman;
			novoElemento->letra = no->letra;
			novoElemento->codigo = codigo;
			insereFimTabela(tabela, novoElemento);
		}
		else {
			criaNovaTabela(no->esquerda, codigo + "0", tabela);
			criaNovaTabela(no->direita, codigo + "1", tabela);
		}
	}
}

void ordenarListaEncadeada(TListaEncadeada<TNoHuffman*>& lista) {
	if (lista.inicio == NULL) {
		cout << "Lista Vazia!";
		return;
	}

	int quantidade = 0;
	TElementoListaEncadeada<TNoHuffman*>* nav = lista.inicio;

	while (nav != NULL) { // descobrir quantas posicoes tem a lista
		nav = nav->prox;
		quantidade++;
	}

	int rodada, indice;
	TElementoListaEncadeada<TNoHuffman*> temp1;
	TElementoListaEncadeada<TNoHuffman*> temp2;

	for (rodada = 0; rodada < quantidade - 1; rodada++) {
		for (indice = 0; indice < quantidade - rodada - 1; indice++) {
			temp1.dado = obtemItemListaEncadeada(lista, indice);
			temp2.dado = obtemItemListaEncadeada(lista, indice + 1);

			if (temp1.dado->frequencia > temp2.dado->frequencia) { //ordena a frequencia crescente
				temp1.dado = temp2.dado;
				removeNoPosicaoListaEncadeada(lista, indice + 1);
				insereNoPosicaoListaEncadeada(lista, temp1.dado, indice);
			}

			if (temp1.dado->frequencia == temp2.dado->frequencia) { //ordena em ordem alfabetica as frequencias iguais
				if (temp1.dado->letra > temp2.dado->letra) {
					temp1.dado = temp2.dado;
					removeNoPosicaoListaEncadeada(lista, indice + 1);
					insereNoPosicaoListaEncadeada(lista, temp1.dado, indice);
				}
			}
		}
	}
}

void criarArvoreHuffman(TListaEncadeada<TNoHuffman*>& lista) {
	while (lista.inicio->prox != nullptr) {
		TNoHuffman* esquerda = removeNoPosicaoListaEncadeada(lista, 0);
		TNoHuffman* direita = removeNoPosicaoListaEncadeada(lista, 0);

		TNoHuffman* pai = new TNoHuffman;
		pai->frequencia = esquerda->frequencia + direita->frequencia;
		pai->letra = '\0';
		pai->esquerda = esquerda;
		pai->direita = direita;

		insereNoFimLista(lista, pai);
		ordenarListaEncadeada(lista);
	}
}

#endif	// LISTAENCADEADA_H