cmake_minimum_required(VERSION 3.5)

project(ProjetoEscolar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ProjetoEscolar main.cpp

    filtrarPorMedia.h
    cadastroAluno.h
    buscaAluno.h
    relatorioFaltas.h
    Aluno.h
    relatorioGeral.h
    DesfazerCadastro.h
    ListaAluno.h)

include(GNUInstallDirs)
install(TARGETS ProjetoEscolar
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
