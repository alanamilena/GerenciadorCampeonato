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

bool Campeonato::vazio() const {
    return times.empty();
}
