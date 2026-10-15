#ifndef PARTIDA_HPP
#define PARTIDA_HPP

#include <string>

class Partida {
public:
    Partida(const std::string& casa, const std::string& visitante,
            int golsCasa, int golsVisitante,
            int amarelosCasa, int vermelhosCasa,
            int amarelosVisitante, int vermelhosVisitante);

    std::string casa() const;
    std::string visitante() const;
    int golsCasa() const;
    int golsVisitante() const;
    int amarelosCasa() const;
    int vermelhosCasa() const;
    int amarelosVisitante() const;
    int vermelhosVisitante() const;

private:
    std::string casa_;
    std::string visitante_;
    int golsCasa_;
    int golsVisitante_;
    int amarelosCasa_;
    int vermelhosCasa_;
    int amarelosVisitante_;
    int vermelhosVisitante_;
};

#endif
