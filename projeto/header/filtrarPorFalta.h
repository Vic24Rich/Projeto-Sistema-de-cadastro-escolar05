#ifndef FILTRARPORFALTA_H
#define FILTRARPORFALTA_H

#include <vector>
#include <algorithm>

using namespace std;

// Implementação do Quick Sort para a ordenação das falta dos alunos do maior para o menor.
int divisao1(vector<int> &falta, int menor, int maior) {
    int principal = falta[maior];

    int i = (menor - 1);

    for (int j = menor; j <= maior - 1; j++) {
        if (falta[j] <= principal) {
            i++;
            swap(falta[i], falta[j]);
        }
    }

    swap(falta[i + 1], falta[maior]);
    return (i + 1);

}

void quickSortF(vector<int> &falta, int menor, int maior) {

    if (menor < maior) {

        int faltaparte = divisao1(falta, menor, maior);

        quickSortF(falta, menor, faltaparte - 1);
        quickSortF(falta, faltaparte + 1, maior);

    }
}

#endif // FILTRARPORFALTA_H
