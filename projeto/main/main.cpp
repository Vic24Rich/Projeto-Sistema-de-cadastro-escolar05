#include "cadastroAluno.h"
#include "Aluno.h"
#include "DesfazerCadastro.h"
#include "ListaAluno.h"
#include "buscaAluno.h"
#include "relatorioFaltas.h"
#include "filtrarPorMedia.h"
#include "relatorioGeral.h"


int main(void)
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
    int opcao = 1;

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

            if (buscarAluno(db_alunos, matricula, alEnc) != -1)
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
            filtrarPorMedia(db_alunos, 0, db_alunos.size() - 1);
            break;

        case 5:
            // Chama a função que filtra alunos por quantidade de faltas
            filtrarPorFalta(db_alunos);
            break;

        case 6:
            // Chama a função que gera o relatório geral dos alunos
            relatorioGeral();
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
