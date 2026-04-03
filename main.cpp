#include "cadastrarAluno.hpp"

using namespace Aluno;

int main(void)
{

    cadastrarAluno();

    cadastrarAluno();

   for (size_t i = 0; i < Aluno::db_alunos.size(); i++)
   {
        db_alunos[i].dados(); cout << '\n';
   }
       

    return 0;
}
