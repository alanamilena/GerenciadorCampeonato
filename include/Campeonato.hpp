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
    // Códigos de retorno de registrarPartida (documentam o resultado da operação)
    enum ResultadoPartida {
        PARTIDA_OK = 0,           // partida registrada e estatísticas dos times atualizadas
        TIME_NAO_ENCONTRADO = 1,  // um ou os dois times não estão cadastrados
        MESMO_TIME = 2,           // os dois nomes se referem ao mesmo time
        DADOS_INVALIDOS = 3       // algum gol ou cartão é negativo
    };

    Campeonato() {}
    ~Campeonato() {}
    
    // Cadastra time: corta espaços das pontas. Retorna true se cadastrou, false se já existe ou nome vazio.
    bool cadastrarTime(const std::string& nome);
    
    // Retorna lista com nomes dos times em ordem alfabética (vêm do map)
    std::vector<std::string> listarTimes() const;
    
    // Registra uma partida. Valida todos os dados antes de alterar qualquer estatística.
    // Devolve um dos códigos do enum ResultadoPartida.
    int registrarPartida(const std::string& casa, const std::string& visitante,
                         int golsCasa, int golsVisitante,
                         int amarelosCasa, int vermelhosCasa,
                         int amarelosVisitante, int vermelhosVisitante);
    
    // Verifica se não há times cadastrados
    bool vazio() const;
};

#endif
