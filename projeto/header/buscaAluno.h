#ifndef BUSCAALUNO_H
#define BUSCAALUNO_H

#include <vector>
#include <algorithm>
#include <windows.h>
#include <cstdlib>
#include "Aluno.h"


// para fazer a busca binaria, os alunos precisam estar ordenados por id
// irei usar o QuickSort para ordenar os alunos que usa um pivot para dividir o vetor
// em partes menores e ordenar cada parte recursivamente

int partition(vector<Aluno>& alunos, int low, int high){
    // a escolha de um pivot aleatorio veio de um conselho de um professor
    // ele serve para evitar que no pior caso ele tenha tempo de O(n²) e passe a ter
    // um tempo constante de O(n log n)
    int randomIndex = low + rand() % (high - low + 1);
    swap(alunos[randomIndex], alunos[high]);
    int pivot = alunos[high].matricula;
    int i = low - 1;

    for(int j = low; j <= high - 1; j++){
        if (alunos[j].matricula <= pivot){
            i++;
            swap(alunos[i], alunos[j]);
        }
    }
    swap(alunos[i + 1], alunos[high]);
    return (i + 1);
}

void quickSort(vector<Aluno>& alunos, int low, int high){
    if (low < high){
        int pivot = partition(alunos, low, high);

        quickSort(alunos, low, pivot - 1);
        quickSort(alunos, pivot + 1, high);
    }
}

// para a busca por matricula, foi pedido o uso de busca binaria

int buscarAluno(vector<Aluno>& alunos, int id,  Aluno &aluno){
    int low = 0;
    int high = alunos.size() - 1;

    quickSort(alunos, low, high); // chamada do quicksort para ordenar

    do{
        int mid = low + (high - low) / 2;

        if(alunos[mid].matricula == id){
            aluno = alunos[mid];
            return mid;
        }
        else if (alunos[mid].matricula < id)
            low = mid + 1;
        else
            high = mid - 1;
    } while (low <= high);
    return -1; // se não for encontrado returna -1, PRECISA SER TRATADO NA MAIN
}

#endif // BUSCAALUNO_H
