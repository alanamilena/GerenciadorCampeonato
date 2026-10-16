#include "interface.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstddef>
#include <sstream>

// Função auxiliar para trim (usada para distinguir nome vazio)
static std::string trim_str(const std::string& s) {
    if (s.empty()) return s;
    size_t inicio = 0;
    size_t fim = s.size();
    while (inicio < fim && (s[inicio] == ' ' || s[inicio] == '\t' || s[inicio] == '\r' || s[inicio] == '\n')) {
        ++inicio;
    }
    while (fim > inicio && (s[fim - 1] == ' ' || s[fim - 1] == '\t' || s[fim - 1] == '\r' || s[fim - 1] == '\n')) {
        --fim;
    }
    if (inicio >= fim) return std::string();
    return s.substr(inicio, fim - inicio);
}

namespace interface {

// Lê todos os dados de uma partida e tenta registrá-la no Campeonato.
// A leitura sempre consome 8 linhas (2 nomes + 6 números), mesmo em caso de
// erro, para que nenhuma entrada restante seja confundida com opção do menu.
static void registrarPartidaMenu(Campeonato& camp) {
    std::string casa;
    std::string visitante;

    std::cout << "Time da casa: ";
    std::cout.flush();
    std::getline(std::cin, casa);

    std::cout << "Time visitante: ";
    std::cout.flush();
    std::getline(std::cin, visitante);

    const char* rotulos[6] = {
        "Gols do time da casa: ",
        "Gols do time visitante: ",
        "Cartoes amarelos do time da casa: ",
        "Cartoes vermelhos do time da casa: ",
        "Cartoes amarelos do time visitante: ",
        "Cartoes vermelhos do time visitante: "
    };
    int valores[6] = {0, 0, 0, 0, 0, 0};
    bool formatoOk = true;

    for (int i = 0; i < 6; ++i) {
        std::cout << rotulos[i];
        std::cout.flush();
        int valor = 0;
        if (!lerInteiro(valor)) {
            formatoOk = false; // texto no lugar de número: marca erro...
        }
        valores[i] = valor;    // ...mas segue lendo os 6 números até o fim.
    }

    if (!formatoOk) {
        std::cout << "ERRO: Entrada invalida. A partida foi cancelada." << std::endl;
        std::cout << std::endl;
        return;
    }

    int resultado = camp.registrarPartida(casa, visitante,
                                          valores[0], valores[1],
                                          valores[2], valores[3],
                                          valores[4], valores[5]);

    if (resultado == Campeonato::PARTIDA_OK) {
        std::cout << "OK: Partida registrada com sucesso!" << std::endl;
    } else if (resultado == Campeonato::TIME_NAO_ENCONTRADO) {
        std::cout << "AVISO: Time nao encontrado. A partida foi cancelada." << std::endl;
    } else if (resultado == Campeonato::MESMO_TIME) {
        std::cout << "AVISO: Uma partida nao pode ser entre o mesmo time." << std::endl;
    } else {
        std::cout << "ERRO: Gols e cartoes nao podem ser negativos. A partida foi cancelada." << std::endl;
    }
    std::cout << std::endl;
}

bool lerInteiro(int& valor) {
    std::string linha;
    std::getline(std::cin, linha);
    if (linha.empty()) {
        return false; // linha vazia
    }
    // Tenta converter inteiro, consumindo toda a string
    std::istringstream iss(linha);
    int v = 0;
    // Verifica se há algo para ler
    if (!(iss >> v)) {
        return false; // não é número
    }
    // Verifica se sobrou algo não-whitespace
    std::string resto;
    std::getline(iss, resto);
    // verifica se resto tem só espaços
    for (size_t i = 0; i < resto.size(); ++i) {
        char c = resto[i];
        if (c != ' ' && c != '\t' && c != '\r' && c != '\n') {
            return false;
        }
    }
    valor = v;
    return true;
}

void executar(Campeonato& camp) {
    int opcao = 0;
    while (true) {
        std::cout << "=== MENU CAMPEONATO ===" << std::endl;
        std::cout << "1. Cadastrar time" << std::endl;
        std::cout << "2. Listar times" << std::endl;
        std::cout << "3. Registrar partida" << std::endl;
        std::cout << "4. Ver classificacao" << std::endl;
        std::cout << "5. Buscar time" << std::endl;
        std::cout << "6. Sair" << std::endl;
        std::cout << "Escolha uma opcao: ";
        std::cout.flush();
        
        if (!lerInteiro(opcao)) {
            std::cout << "ERRO: Entrada invalida. Digite um numero entre 1 e 6." << std::endl;
            std::cout << std::endl;
            continue;
        }
        
        if (opcao == 1) {
            std::string nome;
            std::cout << "Nome do time: ";
            std::cout.flush();
            std::getline(std::cin, nome);
            // Tenta cadastrar
            bool ok = camp.cadastrarTime(nome);
            if (ok) {
                std::cout << "OK: Time cadastrado com sucesso!" << std::endl;
            } else {
                // Diferencia vazio vs duplicado
                std::string nomeTrim = trim_str(nome);
                if (nomeTrim.empty()) {
                    std::cout << "AVISO: Nome do time invalido." << std::endl;
                } else {
                    std::cout << "AVISO: Time ja esta cadastrado." << std::endl;
                }
            }
            std::cout << std::endl;
            
        } else if (opcao == 2) {
            if (camp.vazio()) {
                std::cout << "AVISO: Nao ha times cadastrados." << std::endl;
            } else {
                std::vector<std::string> lista = camp.listarTimes();
                for (size_t i = 0; i < lista.size(); ++i) {
                    std::cout << lista[i] << std::endl;
                }
            }
            std::cout << std::endl;
            
        } else if (opcao == 3) {
            registrarPartidaMenu(camp);
            
        } else if (opcao == 4) {
            std::cout << "Opcao ainda nao disponivel." << std::endl;
            std::cout << std::endl;
            
        } else if (opcao == 5) {
            std::cout << "Opcao ainda nao disponivel." << std::endl;
            std::cout << std::endl;
            
        } else if (opcao == 6) {
            // Sair
            break;
            
        } else {
            // Opcao valida em formato, mas fora do intervalo
            std::cout << "ERRO: Opcao invalida. Digite um numero entre 1 e 6." << std::endl;
            std::cout << std::endl;
        }
    }
}

} // namespace interface
