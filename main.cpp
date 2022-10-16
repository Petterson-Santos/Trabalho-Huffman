#include <iostream>
#include "Huffman.h"
#include "ListaEncadeada.h"
using namespace std;

/*
	CODIFICAR :: 
		Fazer a lista de frequencia de caracteres :: DONE
			Inserir item na lista ou incrementar frequencia :: DONE
			Ordenar lista por frequencia (crescente) :: DONE
		Montar a arvore de Huffman (lista com só um nó) ::
		Gerar a tabela de código Huffman :: 
		Varrer o texto original e escrever a frase em codigo :: 
	DECODIFICAR ::
*/

int main() {
	string mensagem = "maria e linda";
	TListaEncadeada<TNoHuffman> lista;
	inicializarListaEncadeada(lista);

	for (int i = 0; i < mensagem.length(); i++) {
		insereLetraListaEncadeada(lista, mensagem[i]);
	}

	imprimeListaEncadeadaHuffman(lista);
	cout << endl;
	ordenarListaEncadeada(lista);
	imprimeListaEncadeadaHuffman(lista);

	return 0;
}
