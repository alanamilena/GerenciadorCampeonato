#ifndef TIME_HPP
#define TIME_HPP

#include <string>

class Time {
public:
    Time(const std::string& nome);

    void atualizar(int golsMarcados, int golsSofridos, int amarelos, int vermelhos);

    bool operator<(const Time& outro) const;

    std::string nome() const;
    int pontos() const;
    int golsMarcados() const;
    int golsSofridos() const;
    int saldo() const;
    int partidasJogadas() const;
    int amarelos() const;
    int vermelhos() const;

private:
    std::string nome_;
    int pontos_;
    int golsMarcados_;
    int golsSofridos_;
    int saldo_;
    int partidasJogadas_;
    int amarelos_;
    int vermelhos_;
};

#endif
