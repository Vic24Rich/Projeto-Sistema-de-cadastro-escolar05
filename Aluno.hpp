#include <iostream>
#include <string>
#include <vector>

namespace Aluno
{
    struct Aluno
    {
        u_int matricula;
        std::string nome;
        float media;
        u_int faltas;
    };

    std::vector<Aluno> db_alunos;

} // namespace Aluno
