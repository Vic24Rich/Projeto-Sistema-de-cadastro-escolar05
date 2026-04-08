#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct Aluno {
    string matricula;
    string nome;
    float media;
    int faltas;

    static vector<Aluno> db_alunos; 
};

vector<Aluno> Aluno::db_alunos;

void cadastrarAluno()
{
    Aluno aluno; 

    cout << "Digite a matricula do aluno: ";
    cin >> aluno.matricula;
    cin.ignore(80, '\n');

    cout << "Digite o nome de aluno: ";
    cin >> aluno.nome; 

    cout << "Digite a media do aluno: ";
    cin >> aluno.media;
    cin.ignore(80, '\n');

    cout << "Digite a quantidade de falta do aluno: ";
    cin >> aluno.faltas;
    cin.ignore(80, '\n');

    Aluno::db_alunos.push_back(aluno);
    cout << "Aluno cadastrado com sucesso!\n";
}



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

void gerarRelatorioGeral()
{

    //Para descobrir a quantidade de alunos cadastrados
    int n = Aluno::db_alunos.size();

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
    relatorioRecursivo(Aluno::db_alunos, 0, somaMedias, somaFaltas);

    cout << "\n========== RELATORIO ==========\n";
    cout << "Alunos: " << n << "\n";
    cout << fixed << setprecision(2);
    cout << "Media Geral: " << somaMedias / n << "\n";
    cout << "Total de Faltas: " << somaFaltas << "\n";
    cout << "===============================\n";
}


//Feito com IA apenas para testes
int main() {
    int opcao;

    do {
        cout << "\n==============================\n";
        cout << "       SISTEMA ACADEMICO      \n";
        cout << "==============================\n";
        cout << "1. Cadastrar Novo Aluno\n";
        cout << "2. Gerar Relatorio (Recursivo)\n";
        cout << "0. Sair\n";
        cout << "------------------------------\n";
        cout << "Escolha uma opcao: ";
        
        if (!(cin >> opcao)) {
            cout << "Entrada invalida! Use apenas numeros.\n";
            cin.clear();
            cin.ignore(80, '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                cadastrarAluno();
                break;
            case 2:
                gerarRelatorioGeral();
                break;
            case 0:
                cout << "Encerrando o programa...\n";
                break;
            default:
                cout << "Opcao inexistente. Tente novamente.\n";
        }

    } while (opcao != 0);

    return 0;
}