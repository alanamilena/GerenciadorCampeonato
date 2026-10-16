#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Campeonato.hpp"

namespace interface {
    // Lê inteiro de uma linha inteira. Retorna true se inteiro válido (formato correto), false caso contrário.
    bool lerInteiro(int& valor);
    
    // Executa loop do menu principal
    void executar(Campeonato& camp);
}

#endif
