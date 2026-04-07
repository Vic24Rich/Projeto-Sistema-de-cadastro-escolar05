#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Implementação do Quick Sort para a ordenação das falta dos alunos do menor para o maior.
int divisao2(vector<int> &falta, int menor, int maior) {
    int principal = falta[maior];

    int i = (menor - 1);

    for (int j = menor; j <= maior - 1; j++) {
        if (falta[j] >= principal) { 
            i++;
            swap(falta[i], falta[j]);
        }
    }

    swap(falta[i + 1], falta[maior]);
    return (i + 1);
}

void quickSortM(vector<int> &falta, int menor, int maior) {
    if (menor < maior) {
        int faltaparte = divisao2(falta, menor, maior);

        // Recursão para as duas metades
        quickSortM(falta, menor, faltaparte - 1);
        quickSortM(falta, faltaparte + 1, maior);
    }
}