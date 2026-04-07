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

struct Aluno {
    string Nome;
    array<float, 4> Notas;
    float Media;
    string situacao;
};

bool CompareNome(const Aluno &a, const Aluno &b) 
{
  return a.Nome < b.Nome;
}

void color(int corFundo, int corTexto) {
  HANDLE tela;
  int16_t cor;
  tela = GetStdHandle(STD_OUTPUT_HANDLE);
  if (corFundo < 0 || corFundo > 15 || corTexto < 0 ||
    corTexto > 15)
    cor = 15;
  else
    cor = corTexto + corFundo * 16;
  SetConsoleTextAttribute(tela, cor);
}

void clear(void) {
    HANDLE tela;
    CONSOLE_SCREEN_BUFFER_INFO info;
    DWORD escrita = 0;
    tela = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(tela, &info);
    COORD pos = {0, 0};
    DWORD celulas = info.dwSize.X * info.dwSize.Y;
    FillConsoleOutputCharacter(tela, ' ', celulas, pos,
    &escrita);
    SetConsoleCursorPosition(tela, pos);
}

int main(void) {
    vector<Aluno> Alunos(30);
    float min, soma_media, soma_nota, media_geral;
    char opcao = 's';
    uint32_t Sala;

    cout << setprecision(2) << fixed << right;

    // looping principal
    while (opcao != 'n' || 'N') {		
        cout << "Media da Sala" << endl;
        cout << string(80, '-') << endl;

        cout << endl << endl;

        cout << "Quantos alunos possue a classe? ";
        cin >> Sala;
        cin.ignore(80, '\n');

        if (Sala < 1 || Sala > 100) {
            cout << "Valor invalido, sera usado o padrao 30 alunos" << endl;
            Sala = 30;
        }
        Alunos.resize(Sala);
        cout << endl << endl;
		
		cout << "Qual a media? ";
        cin >> min;
        cin.ignore(80, '\n');

        if (min < 0.0 && min > 10.0) {
            cout << "Valor invalido, sera usado o padrao 5" << endl;
            min = 5.00;
        }
        
        cout << endl;
        cout << string(80, '-') << endl;

        // entrada de dados dos alunos
        for (size_t i = 0; i < Alunos.size(); ++i) {
            cout << "Nome do aluno: ";
            getline(cin, Alunos[i].Nome);
            cout << "Entrada das notas do aluno " << Alunos[i].Nome << endl;
            cout << endl;
            for (size_t j = 0; j < Alunos[i].Notas.size(); j++) {
                if (j < 3) {
                    cout << "Prova " << j+1 << " ...: ";
                    string entranota;         // fazer a entrada como uma string e depois uma converção para float
                    getline(cin, entranota);  // isso possibilita a criação de operaçoes matematicas
                    Alunos[i].Notas[j] = atof(entranota.c_str());
                }
                else{
                    cout << "Prova final: ";
                    cin >> Alunos[i].Notas[j];
                    cin.ignore(80, '\n');
                }
            }
            cout << endl << endl;
        }

        soma_media = 0;
        for(size_t i = 0; i <= Alunos.size(); ++i){
            soma_nota = 0;
            for(size_t j = 0; j <= 3; ++j) // 3 == Numero de notas (0 a 3)
                soma_nota += Alunos[i].Notas[j]; // looping de soma das notas
            Alunos[i].Media = soma_nota / 4.0;
            soma_media += Alunos[i].Media;
            if (Alunos[i].Media >= min)
                Alunos[i].situacao = " Aprovado";
            else
                Alunos[i].situacao = "Reprovado";
        }
        media_geral = soma_media / Alunos.size();

        //sort padram da biblioteca algoritmos std
        sort(Alunos.begin(), Alunos.end(), CompareNome);

        // relatorio geral
        cout << endl << endl;
        cout << "Relatorio Geral" << endl;
        cout << endl << endl;

        cout << setw(6)  << "No.";
        cout << setw(8)  << "Nome";
	    cout << setw(10) << "Nota 1";
	    cout << setw(9)  << "Nota 2";
	    cout << setw(9)  << "Nota 3";
	    cout << setw(9)  << "ProvaF";
    	cout << setw(8)  << "Media";
	    cout << setw(12) << "Situacao";
        
	    cout << endl;

	    cout << string(80, '-') << endl;

        for (size_t i = 0; i < Alunos.size(); ++i) {
            cout << setw(4) << i+1;
            cout << setw(9) << Alunos[i].Nome;
            for (size_t j = 0; j < Alunos[i].Notas.size(); ++j)
                cout << setw(9) << fixed << setprecision(1) << Alunos[i].Notas[j];
            
            cout << setw(9)  << Alunos[i].Media;

            if (Alunos[i].Media >= 5.0)
                color(0, 2); // Fundo preto e letra verde
            else
                color(0, 4); // Fundo preto e letra vermelha
            cout << setw(13) << Alunos[i].situacao;
            cout << endl;
            color(0, 7); // Cor padrão
        }
        cout << string(80, '-') << endl;
        cout << endl;
        cout << "Media geral da sala: " << media_geral << endl;

        cout << endl << endl;
        cout << "Deseja calcular outra classe (S/N)? ";
        cin.get(opcao);
        cin.ignore(80, '\n');
        if (opcao == 's' || opcao == 'S')
            clear();
    }

    cout << endl;
    cout << "Aperte <enter> para encerrar: ";
    cin.get();
    return 0;
}