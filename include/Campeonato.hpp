#ifndef CAMPEONATO_HPP
#define CAMPEONATO_HPP

#include <map>
#include <list>
#include <vector>
#include <string>
#include "Time.hpp"
#include "Partida.hpp"

class Campeonato {
private:
    std::map<std::string, Time> times;
    std::list<Partida> partidas;
    
public:
    Campeonato() {}
    ~Campeonato() {}
    
    // Cadastra time: corta espaços das pontas. Retorna true se cadastrou, false se já existe ou nome vazio.
    bool cadastrarTime(const std::string& nome);
    
    // Retorna lista com nomes dos times em ordem alfabética (vêm do map)
    std::vector<std::string> listarTimes() const;
    
    // Verifica se não há times cadastrados
    bool vazio() const;
};

#endif
