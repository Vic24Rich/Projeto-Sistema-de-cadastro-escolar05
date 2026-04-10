#ifndef RELATORIOGERAL_H
#define RELATORIOGERAL_H

#include <iostream>
#include <vector>
#include <iomanip>
#include "Aluno.h"

//Função de Relatório Recursivo
void relatorioRecursivo(const vector<Aluno>& alunos, int idx, float& somaMedias, int& somaFaltas)
{
    // Se o índice (idx) for igual ao tamanho da lista, não há mais ninguém para olhar.
    if (idx == (int)alunos.size()) return;

    // Eu pego a média e a falta do aluno que está no (idx)
    // e jogo dentro das variáveis de soma que recebi por referência (&).
    somaMedias += alunos[idx].media;
    somaFaltas += alunos[idx].faltas;

    // Chamo a própria função, mas faço com que ela olhe o próximo idx (idx + 1), repetindo até acabar
    relatorioRecursivo(alunos, idx + 1, somaMedias, somaFaltas);
}

void relatorioGeral()
{
    system("clear");

    //Para descobrir a quantidade de alunos cadastrados
    int n = db_alunos.size();

    //Checa se foi cadastrado algum aluno
    if (n == 0) {
        cout << "\nNenhum aluno cadastrado.\n";
        return;
    }

    // Inicia as variáveis com 0 para garantir que não tenha nada na memória
    float somaMedias = 0.0f;
    int somaFaltas = 0;

    // chama a função principal começando do primeiro aluno (índice 0).
    // Ela vai rodar, preencher as variaveis e voltar quando terminar.
    relatorioRecursivo(db_alunos, 0, somaMedias, somaFaltas);

    cout << "\n========== RELATORIO ==========\n";
    cout << "Alunos: " << n << "\n";
    cout << fixed << setprecision(2);
    cout << "Media Geral: " << somaMedias / n << "\n";
    cout << "Total de Faltas: " << somaFaltas << "\n";
    cout << "===============================\n";
}

#endif // RELATORIOGERAL_H
