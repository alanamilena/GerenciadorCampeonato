#include <iostream>
#include <string>
#include "Time.hpp"
#include "Partida.hpp"

int falhas = 0;

void verificar(const std::string& descricao, int esperado, int obtido) {
    if (esperado == obtido) {
        std::cout << "[OK]    " << descricao << std::endl;
    } else {
        std::cout << "[FALHA] " << descricao
                  << " (esperado: " << esperado
                  << ", obtido: " << obtido << ")" << std::endl;
        ++falhas;
    }
}

void verificarTexto(const std::string& descricao,
                    const std::string& esperado,
                    const std::string& obtido) {
    if (esperado == obtido) {
        std::cout << "[OK]    " << descricao << std::endl;
    } else {
        std::cout << "[FALHA] " << descricao
                  << " (esperado: \"" << esperado
                  << "\", obtido: \"" << obtido << "\")" << std::endl;
        ++falhas;
    }
}

void testarEstadoInicial() {
    std::cout << "Teste 0: estado inicial (construtor zera tudo)" << std::endl;
    Time t("Time Novo");
    verificarTexto("nome guardado", "Time Novo", t.nome());
    verificar("pontos comecam em 0", 0, t.pontos());
    verificar("gols marcados comecam em 0", 0, t.golsMarcados());
    verificar("gols sofridos comecam em 0", 0, t.golsSofridos());
    verificar("saldo comeca em 0", 0, t.saldo());
    verificar("partidas jogadas comecam em 0", 0, t.partidasJogadas());
    verificar("amarelos comecam em 0", 0, t.amarelos());
    verificar("vermelhos comecam em 0", 0, t.vermelhos());
}

void testarVitoriaEmpateDerrota() {
    std::cout << "Teste 1: vitoria, empate e derrota" << std::endl;

    Time vitoria("Vitoria");
    vitoria.atualizar(3, 1, 0, 0);
    verificar("vitoria soma 3 pontos", 3, vitoria.pontos());
    verificar("vitoria gera saldo +2", 2, vitoria.saldo());

    Time empate("Empate");
    empate.atualizar(1, 1, 0, 0);
    verificar("empate soma 1 ponto", 1, empate.pontos());
    verificar("empate gera saldo 0", 0, empate.saldo());

    Time derrota("Derrota");
    derrota.atualizar(0, 2, 0, 0);
    verificar("derrota soma 0 pontos", 0, derrota.pontos());
    verificar("derrota gera saldo -2", -2, derrota.saldo());
}

void testarAcumulo() {
    std::cout << "Teste 2: acumulo de gols, cartoes e partidas" << std::endl;

    Time t("Acumulo");
    t.atualizar(2, 1, 1, 0);
    t.atualizar(1, 1, 2, 1);
    t.atualizar(0, 3, 0, 2);

    verificar("3 partidas jogadas", 3, t.partidasJogadas());
    verificar("gols marcados 2+1+0", 3, t.golsMarcados());
    verificar("gols sofridos 1+1+3", 5, t.golsSofridos());
    verificar("amarelos 1+2+0", 3, t.amarelos());
    verificar("vermelhos 0+1+2", 3, t.vermelhos());
}

void testarSaldoAcumulado() {
    std::cout << "Teste 3: saldo a partir dos gols acumulados" << std::endl;

    Time t("Saldo");
    t.atualizar(0, 3, 0, 0);
    verificar("apos derrota 0x3, saldo -3", -3, t.saldo());

    t.atualizar(5, 0, 0, 0);
    verificar("apos 0x3 e 5x0, saldo 5-3 = 2", 2, t.saldo());

    t.atualizar(1, 1, 0, 0);
    verificar("apos mais um empate, saldo continua 2", 2, t.saldo());
}

void testarPontosAcumulados() {
    std::cout << "Teste 4: pontuacao acumulada em varias partidas" << std::endl;

    Time t("Pontos");
    t.atualizar(2, 1, 0, 0);
    t.atualizar(1, 1, 0, 0);
    t.atualizar(0, 1, 0, 0);
    t.atualizar(4, 0, 0, 0);

    verificar("pontos 3+1+0+3", 7, t.pontos());
    verificar("4 partidas jogadas", 4, t.partidasJogadas());
}

void testarGetters() {
    std::cout << "Teste 5: getters retornam os valores esperados" << std::endl;

    Time t("Time Teste");
    t.atualizar(3, 2, 4, 1);

    verificarTexto("getter nome", "Time Teste", t.nome());
    verificar("getter pontos", 3, t.pontos());
    verificar("getter gols marcados", 3, t.golsMarcados());
    verificar("getter gols sofridos", 2, t.golsSofridos());
    verificar("getter saldo", 1, t.saldo());
    verificar("getter partidas jogadas", 1, t.partidasJogadas());
    verificar("getter amarelos", 4, t.amarelos());
    verificar("getter vermelhos", 1, t.vermelhos());
}

void testarPartida() {
    std::cout << "Teste 6: construtor da Partida guarda os oito dados" << std::endl;

    Partida p("Flamengo", "Vasco", 2, 1, 1, 0, 2, 1);
    verificarTexto("getter casa", "Flamengo", p.casa());
    verificarTexto("getter visitante", "Vasco", p.visitante());
    verificar("getter gols da casa", 2, p.golsCasa());
    verificar("getter gols do visitante", 1, p.golsVisitante());
    verificar("getter amarelos da casa", 1, p.amarelosCasa());
    verificar("getter vermelhos da casa", 0, p.vermelhosCasa());
    verificar("getter amarelos do visitante", 2, p.amarelosVisitante());
    verificar("getter vermelhos do visitante", 1, p.vermelhosVisitante());

    std::cout << std::endl;
    std::cout << "Teste 7: partida de outro tipo (empate, sem cartoes)" << std::endl;

    Partida outra("Sao Paulo", "Santos", 1, 1, 0, 0, 0, 0);
    verificarTexto("getter casa", "Sao Paulo", outra.casa());
    verificarTexto("getter visitante", "Santos", outra.visitante());
    verificar("getter gols da casa empatados", 1, outra.golsCasa());
    verificar("getter gols do visitante empatados", 1, outra.golsVisitante());
    verificar("getter amarelos da casa zerado", 0, outra.amarelosCasa());
    verificar("getter vermelhos da casa zerado", 0, outra.vermelhosCasa());
    verificar("getter amarelos do visitante zerado", 0, outra.amarelosVisitante());
    verificar("getter vermelhos do visitante zerado", 0, outra.vermelhosVisitante());
}

int main() {
    std::cout << "=== Testes das classes Time e Partida ===" << std::endl << std::endl;

    testarEstadoInicial();
    std::cout << std::endl;
    testarVitoriaEmpateDerrota();
    std::cout << std::endl;
    testarAcumulo();
    std::cout << std::endl;
    testarSaldoAcumulado();
    std::cout << std::endl;
    testarPontosAcumulados();
    std::cout << std::endl;
    testarGetters();
    std::cout << std::endl;
    testarPartida();

    std::cout << std::endl << "Falhas: " << falhas << std::endl;
    return falhas == 0 ? 0 : 1;
}
