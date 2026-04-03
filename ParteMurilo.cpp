// minha parte do codigo: Murilo Juttel
// Sistema de faltas dos alunos:
// - Criação de tabela hordenada por faltas
// - coloração vermelha para alunos com mais de 25% de faltas
// busca de alunos: 
// - busca binaria por matricula do aluno

#include <iostream>
#include <iomanip>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <cstdint>
using namespace std;

#define Black     0 // Preto
#define Green     2 // Verde
#define Red       4 // Vermelho
#define lgray     7 // Cinza Claro

struct CadAluno {
    int id;
    string Nome;
    array<float, 4> Notas;
    float Media;
    string situacao;
};

// para fazer a busca binaria, os alunos precisam estar ordenados por id
// irei usar o QuickSort para ordenar os alunos que usa um pivot para dividir o vetor em partes menores e ordenar cada parte recursivamente

int partition(vector<CadAluno>& alunos, int low, int high){
    int pivot = alunos[high].id;
    int i = low - 1;

    for(int j = low; j <= high - 1; j++){
		if (alunos[j].id <= pivot){
			i++;
            swap(alunos[i], alunos[j]);
		}
	}
    swap(alunos[i + 1], alunos[high]);
    return (i + 1);
}

void quickSort(vector<CadAluno>& alunos, int low, int high){
    if (low < high){
		int pivot = partition(alunos, low, high);

        quickSort(alunos, low, pivot - 1);
        quickSort(alunos, pivot + 1, high);
    }
}

// para a busca por matricula, foi pedido o uso de busca binaria

int buscaAluno(vector<CadAluno>& alunos, int id){
    int low = 0;
    int high = alunos.size() - 1;

    quickSort(alunos, low, high); // chamada do quicksort para ordenar

    do{
        int mid = low + (high - low) / 2;

        if(alunos[mid].id == id)
            return mid;
        else if (alunos[mid].id < id)
            low = mid + 1;
        else
            high = mid - 1;
    } while (low <= high);
    return -1; // se não for encontrado returna -1, PRECISA SER TRATADO NA MAIN
}

