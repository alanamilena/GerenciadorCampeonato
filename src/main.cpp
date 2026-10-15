#include <iostream>
#include "Time.hpp"

int main() {
    Time flamengo("Flamengo");
    Time vasco("Vasco");

    flamengo.atualizar(2, 1, 1, 0);
    vasco.atualizar(1, 2, 2, 1);

    std::cout << flamengo.nome()
              << " | pontos: " << flamengo.pontos()
              << " | gols marcados: " << flamengo.golsMarcados()
              << " | gols sofridos: " << flamengo.golsSofridos()
              << " | saldo: " << flamengo.saldo()
              << " | jogos: " << flamengo.partidasJogadas()
              << " | amarelos: " << flamengo.amarelos()
              << " | vermelhos: " << flamengo.vermelhos()
              << std::endl;

    std::cout << vasco.nome()
              << " | pontos: " << vasco.pontos()
              << " | gols marcados: " << vasco.golsMarcados()
              << " | gols sofridos: " << vasco.golsSofridos()
              << " | saldo: " << vasco.saldo()
              << " | jogos: " << vasco.partidasJogadas()
              << " | amarelos: " << vasco.amarelos()
              << " | vermelhos: " << vasco.vermelhos()
              << std::endl;

    return 0;
}
