#include "Partida.hpp"

Partida::Partida(const std::string& casa, const std::string& visitante,
                 int golsCasa, int golsVisitante,
                 int amarelosCasa, int vermelhosCasa,
                 int amarelosVisitante, int vermelhosVisitante)
    : casa_(casa),
      visitante_(visitante),
      golsCasa_(golsCasa),
      golsVisitante_(golsVisitante),
      amarelosCasa_(amarelosCasa),
      vermelhosCasa_(vermelhosCasa),
      amarelosVisitante_(amarelosVisitante),
      vermelhosVisitante_(vermelhosVisitante) {
}

std::string Partida::casa() const {
    return casa_;
}

std::string Partida::visitante() const {
    return visitante_;
}

int Partida::golsCasa() const {
    return golsCasa_;
}

int Partida::golsVisitante() const {
    return golsVisitante_;
}

int Partida::amarelosCasa() const {
    return amarelosCasa_;
}

int Partida::vermelhosCasa() const {
    return vermelhosCasa_;
}

int Partida::amarelosVisitante() const {
    return amarelosVisitante_;
}

int Partida::vermelhosVisitante() const {
    return vermelhosVisitante_;
}
