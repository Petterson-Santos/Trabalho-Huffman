#include <iostream>
#include "Huffman.h"
#include "ListaEncadeada.h"
using namespace std;

/*
	CODIFICAR :: 
		Fazer a lista de frequencia de caracteres :: DONE
			Inserir item na lista ou incrementar frequencia :: DONE
			Ordenar lista por frequencia (crescente) :: DONE
		Montar a arvore de Huffman (lista com só um nó) :: DONE
		Gerar a tabela de código Huffman :: DONE
		Varrer o texto original e escrever a frase em codigo :: 
	DECODIFICAR ::
*/

int main() {
	string mensagem = "maria e linda";
	TListaEncadeada<TNoHuffman*> lista = criaNovaLista(mensagem);

	imprimeListaEncadeadaHuffman(lista);
	ordenarListaEncadeada(lista);
	cout << endl;
	imprimeListaEncadeadaHuffman(lista);

	criarArvoreHuffman(lista);
	cout << endl;
	imprimeListaEncadeadaHuffman(lista);
	cout << endl;
	preFixa(lista.inicio->dado, 0);

	TListaEncadeada<TabelaHuffman*> tabela;
	inicializarListaEncadeada(tabela);
	criaNovaTabela(lista.inicio->dado, "", tabela);
	imprimirTabelaHuffman(tabela);

	return 0;
}
