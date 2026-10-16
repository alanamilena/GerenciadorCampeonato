#include "Campeonato.hpp"
#include <cstddef>

// Função auxiliar para cortar espaços das pontas
static std::string trim(const std::string& s) {
    if (s.empty()) return s;
    size_t inicio = 0;
    size_t fim = s.size();
    // Remove espaços do início
    while (inicio < fim && (s[inicio] == ' ' || s[inicio] == '\t' || s[inicio] == '\r' || s[inicio] == '\n')) {
        ++inicio;
    }
    // Remove espaços do fim
    while (fim > inicio && (s[fim - 1] == ' ' || s[fim - 1] == '\t' || s[fim - 1] == '\r' || s[fim - 1] == '\n')) {
        --fim;
    }
    if (inicio >= fim) return std::string();
    return s.substr(inicio, fim - inicio);
}

bool Campeonato::cadastrarTime(const std::string& nome) {
    std::string nomeCortado = trim(nome);
    if (nomeCortado.empty()) {
        return false; // nome inválido (vazio após trim)
    }
    // Verifica duplicado
    std::map<std::string, Time>::iterator it = times.find(nomeCortado);
    if (it != times.end()) {
        return false; // já cadastrado
    }
    // Insere: chave = nome cortado, valor = Time(nome cortado)
    times.insert(std::make_pair(nomeCortado, Time(nomeCortado)));
    return true;
}

std::vector<std::string> Campeonato::listarTimes() const {
    std::vector<std::string> lista;
    lista.clear();
    // map mantém chaves em ordem alfabética
    for (std::map<std::string, Time>::const_iterator it = times.begin(); it != times.end(); ++it) {
        lista.push_back(it->first);
    }
    return lista;
}

int Campeonato::registrarPartida(const std::string& casa, const std::string& visitante,
                                 int golsCasa, int golsVisitante,
                                 int amarelosCasa, int vermelhosCasa,
                                 int amarelosVisitante, int vermelhosVisitante) {
    // 1) Valida os dados numéricos: nada de gols ou cartões negativos.
    if (golsCasa < 0 || golsVisitante < 0 ||
        amarelosCasa < 0 || vermelhosCasa < 0 ||
        amarelosVisitante < 0 || vermelhosVisitante < 0) {
        return DADOS_INVALIDOS;
    }

    // 2) Corta os espaços das pontas dos nomes, como no cadastro.
    std::string casaCortada = trim(casa);
    std::string visitanteCortado = trim(visitante);

    // 3) Confere se os dois times estão cadastrados.
    std::map<std::string, Time>::iterator itCasa = times.find(casaCortada);
    std::map<std::string, Time>::iterator itVisitante = times.find(visitanteCortado);
    if (itCasa == times.end() || itVisitante == times.end()) {
        return TIME_NAO_ENCONTRADO;
    }

    // 4) Um time não pode jogar contra ele mesmo.
    if (casaCortada == visitanteCortado) {
        return MESMO_TIME;
    }

    // Só chega aqui se todas as validações passaram: agora sim altera as estatísticas.
    // O time da casa marca golsCasa e sofre golsVisitante; o visitante é o inverso.
    itCasa->second.atualizar(golsCasa, golsVisitante, amarelosCasa, vermelhosCasa);
    itVisitante->second.atualizar(golsVisitante, golsCasa, amarelosVisitante, vermelhosVisitante);

    // Guarda o confronto no histórico.
    partidas.push_back(Partida(casaCortada, visitanteCortado,
                               golsCasa, golsVisitante,
                               amarelosCasa, vermelhosCasa,
                               amarelosVisitante, vermelhosVisitante));

    return PARTIDA_OK;
}

bool Campeonato::vazio() const {
    return times.empty();
}
