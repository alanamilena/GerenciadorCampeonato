#include "Time.hpp"

Time::Time(const std::string& nome)
    : nome_(nome),
      pontos_(0),
      golsMarcados_(0),
      golsSofridos_(0),
      saldo_(0),
      partidasJogadas_(0),
      amarelos_(0),
      vermelhos_(0) {
}

void Time::atualizar(int golsMarcados, int golsSofridos, int amarelos, int vermelhos) {
    golsMarcados_ += golsMarcados;
    golsSofridos_ += golsSofridos;
    saldo_ = golsMarcados_ - golsSofridos_;

    partidasJogadas_ += 1;
    amarelos_ += amarelos;
    vermelhos_ += vermelhos;

    if (golsMarcados > golsSofridos) {
        pontos_ += 3;
    } else if (golsMarcados == golsSofridos) {
        pontos_ += 1;
    }
}

bool Time::operator<(const Time& outro) const {
    if (pontos_ != outro.pontos_) {
        return pontos_ > outro.pontos_;
    }
    if (saldo_ != outro.saldo_) {
        return saldo_ > outro.saldo_;
    }
    if (golsMarcados_ != outro.golsMarcados_) {
        return golsMarcados_ > outro.golsMarcados_;
    }
    if (vermelhos_ != outro.vermelhos_) {
        return vermelhos_ < outro.vermelhos_;
    }
    if (amarelos_ != outro.amarelos_) {
        return amarelos_ < outro.amarelos_;
    }
    return nome_ < outro.nome_;
}

std::string Time::nome() const {
    return nome_;
}

int Time::pontos() const {
    return pontos_;
}

int Time::golsMarcados() const {
    return golsMarcados_;
}

int Time::golsSofridos() const {
    return golsSofridos_;
}

int Time::saldo() const {
    return saldo_;
}

int Time::partidasJogadas() const {
    return partidasJogadas_;
}

int Time::amarelos() const {
    return amarelos_;
}

int Time::vermelhos() const {
    return vermelhos_;
}
