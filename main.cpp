// Neste código apresento as funções Main
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <iomanip>
#include <limits> // necessário para numeric_limits

using namespace std;

struct Aluno
{
    u_int matricula;
    std::string nome;
    float media;
    u_int faltas;

    void dados()
    {
        cout << "Matricula: " << matricula << "\nNome: " << nome << "\nMedia: " << media << "\nFaltas: " << faltas << '\n';
    }
};

vector<Aluno> db_alunos;

void desfazerCadastro(vector<Aluno> &db_alunos)
{
    int tamanho = db_alunos.size();
    vector<Aluno> aux;
    for (size_t i = tamanho; i > 0; i--)
    {
        aux.push_back(db_alunos[i - 1]);
        cout << i - 1;
    }

    aux.pop_back();
    cout << '\n';

    for (size_t i = 0; i < tamanho; i++)
    {
       db_alunos.pop_back();
       cout << i;
    }

    tamanho = aux.size();

    for (size_t i = tamanho; i > 0; i--)
    {
        db_alunos.push_back(aux[i - 1]);
    }
    
}

void enterPContinuar()
{
    cout << "<ENTER> para continuar... ";
    cin.get();
    system("clear");
}

// Funcao de Cadastro de aluno
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

    db_alunos.push_back(aluno);
    cout << "Aluno cadastrado!" << '\n';
}

// Funcao Lista Alunos
void listarAlunos(vector<Aluno> db_alunos)
{
    system("clear");
    cout << "======== Alunos Cadastrados ========" << '\n' << '\n';
    for (Aluno aluno : db_alunos)
    {
        aluno.dados();
        cout << '\n';
    }
    cout << "====================================" << '\n' << '\n';
    enterPContinuar();
}

namespace busAluno
{

    // para fazer a busca binaria, os alunos precisam estar ordenados por id
    // irei usar o QuickSort para ordenar os alunos que usa um pivot para dividir o vetor
    // em partes menores e ordenar cada parte recursivamente

    int partition(vector<Aluno> &alunos, int low, int high)
    {
        // a escolha de um pivot aleatorio veio de um conselho de um professor
        // ele serve para evitar que no pior caso ele tenha tempo de O(n²) e passe a ter
        // um tempo constante de O(n log n)
        int randomIndex = low + rand() % (high - low + 1);
        swap(alunos[randomIndex], alunos[high]);
        int pivot = alunos[high].matricula;
        int i = low - 1;

        for (int j = low; j <= high - 1; j++)
        {
            if (alunos[j].matricula <= pivot)
            {
                i++;
                swap(alunos[i], alunos[j]);
            }
        }
        swap(alunos[i + 1], alunos[high]);
        return (i + 1);
    }

    void quickSort(vector<Aluno> &alunos, int low, int high)
    {
        if (low < high)
        {
            int pivot = partition(alunos, low, high);

            quickSort(alunos, low, pivot - 1);
            quickSort(alunos, pivot + 1, high);
        }
    }

    // para a busca por matricula, foi pedido o uso de busca binaria

    int buscarAluno(vector<Aluno> alunos, int matricula, Aluno &aluno)
    {
        int low = 0;
        int high = alunos.size() - 1;

        quickSort(alunos, low, high); // chamada do quicksort para ordenar

        do
        {
            int mid = low + (high - low) / 2;

            if (alunos[mid].matricula == matricula)
            {
                aluno = alunos[mid];
                return mid;
            }
            else if (alunos[mid].matricula < matricula)
                low = mid + 1;
            else
                high = mid - 1;
        } while (low <= high);
        return -1; // se não for encontrado returna -1, PRECISA SER TRATADO NA MAIN
    }
} // namespace busAluno

// Funcao para filtrar por media
namespace filMedia
{
    // Implementação do Quick Sort para a ordenação das medias dos alunos do menor para o maior.
    int divisao2(vector<Aluno> &aluno, int menor, int maior)
    {
        int principal = aluno[maior].media;

        int i = (menor - 1);

        for (int j = menor; j <= maior - 1; j++)
        {
            if (aluno[j].media >= principal)
            {
                i++;
                swap(aluno[i], aluno[j]);
            }
        }

        swap(aluno[i + 1], aluno[maior]);
        return (i + 1);
    }

    void filtrarPorMedia(vector<Aluno> &aluno, int menor, int maior)
    {
        if (menor < maior)
        {
            int faltaparte = divisao2(aluno, menor, maior);

            // Recursão para as duas metades
            filtrarPorMedia(aluno, menor, faltaparte - 1);
            filtrarPorMedia(aluno, faltaparte + 1, maior);
        }
    }
}

namespace filFalta
{
    // Implementação do Quick Sort para a ordenação das falta dos alunos do maior para o menor.
    int divisao1(vector<Aluno> &aluno, int menor, int maior)
    {
        int principal = aluno[maior].faltas;

        int i = (menor - 1);

        for (int j = menor; j <= maior - 1; j++)
        {
            if (aluno[j].faltas <= principal)
            {
                i++;
                swap(aluno[i], aluno[j]);
            }
        }

        swap(aluno[i + 1], aluno[maior]);
        return (i + 1);
    }

    void filtrarPorFalta(vector<Aluno> &alunos, int menor, int maior)
    {

        if (menor < maior)
        {

            int faltaparte = divisao1(alunos, menor, maior);

            filtrarPorFalta(alunos, menor, faltaparte - 1);
            filtrarPorFalta(alunos, faltaparte + 1, maior);
        }
    }
}

namespace relaGeral
{
    // Função de Relatório Recursivo
    void relatorioRecursivo(const vector<Aluno> &alunos, int idx, float &somaMedias, int &somaFaltas)
    {
        // Se o índice (idx) for igual ao tamanho da lista, não há mais ninguém para olhar.
        if (idx == (int)alunos.size())
            return;

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

        // Para descobrir a quantidade de alunos cadastrados
        int n = db_alunos.size();

        // Checa se foi cadastrado algum aluno
        if (n == 0)
        {
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
        enterPContinuar();
    }

}

// =============================
// MAIN (MENU COMPLETO)
// =============================
int main()
{
    Aluno a1;
    a1.matricula = 123;
    a1.nome = "Maria";
    a1.media = 8.4;
    a1.faltas = 12;
    db_alunos.push_back(a1);

    Aluno a2;
    a2.matricula = 321;
    a2.nome = "Joao";
    a2.media = 7.4;
    a2.faltas = 10;
    db_alunos.push_back(a2);

    Aluno a3;
    a3.matricula = 789;
    a3.nome = "Clara";
    a3.media = 9.4;
    a3.faltas = 8;
    db_alunos.push_back(a3);

    Aluno a4;
    a4.matricula = 987;
    a4.nome = "Jonas";
    a4.media = 6.4;
    a4.faltas = 6;
    db_alunos.push_back(a4);

    Aluno alEnc;

    // Aqui eu criei o vetor de alunos
    // Ele vai armazenar todos os alunos cadastrados

    // Aqui eu controlo quantos alunos existem
    // Usado para saber onde cadastrar e para percorrer o vetor
    int total = 0;

    // Variável para armazenar a escolha do usuário
    int opcao;

    // Uso do do-while para que o menu seja exibido repetidamente
    // até o usuário decidir sair digitando 0
    do
    {

        // Mostro o menu para o usuário
        cout << "\n===== MENU =====\n";
        cout << "1 - Cadastrar aluno\n";
        cout << "2 - Lista de alunos\n";
        cout << "3 - Buscar aluno\n";
        cout << "4 - Filtrar por media\n";
        cout << "5 - Filtrar por falta\n";
        cout << "6 - Relatorio geral\n";
        cout << "8 - Desfazer ultimo cadastro\n";
        cout << "0 - Sair\n";
        cout << "Escolha: ";

        // Leio a opção do usuário
        cin >> opcao;
        // Limpo o buffer do cin para evitar problemas com getline em outras funções
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // =============================
        // SWITCH-CASE DO MENU
        // =============================
        // Uso switch-case para organizar cada opção do menu
        // Cada case chama a função correspondente de forma clara
        // e o default trata entradas inválidas
        switch (opcao)
        {

        case 1:
            // Chama a função que cadastra um novo aluno
            cadastrarAluno();
            break;

        case 2:
            // Chama a função que lista todos os alunos
            listarAlunos(db_alunos);
            break;

        case 3:
            // Chama a função que busca um aluno específico
            system("clear");

            int matricula;
            cout << "Buscar Aluno: " << '\n';

            cout << "Digite a matricula do aluno: ";
            cin >> matricula;
            cin.ignore(80, '\n');
            cout << '\n';

            if (busAluno::buscarAluno(db_alunos, matricula, alEnc) != -1)
            {
                alEnc.dados();
                cout << '\n';
                enterPContinuar();
            }
            else
            {
                cout << "Aluno nao ancontrado! Verifique o matricula digitada esta correta." << '\n' << '\n';
                enterPContinuar();
            }  
            break;

        case 4:
            // Chama a função que filtra alunos por média
            filMedia::filtrarPorMedia(db_alunos, 0, db_alunos.size() - 1);
            break;

        case 5:
            // Chama a função que filtra alunos por quantidade de faltas
            filFalta::filtrarPorFalta(db_alunos, 0, db_alunos.size() - 1);
            break;

        case 6:
            // Chama a função que gera o relatório geral dos alunos
            relaGeral::relatorioGeral();
            break;

        case 8:
            // Chama a função que desfaz o último cadastro feito
            desfazerCadastro(db_alunos);
            break;

        case 0:
            // Mensagem de saída do sistema
            cout << "Saindo do sistema...\n";
            break;

        default:
            // Caso o usuário digite um número inválido
            cout << "Opcao invalida!\n";
        }

    } while (opcao != 0); // Continua mostrando o menu enquanto não escolher sair

    return 0;
}