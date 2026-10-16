# Gerenciador de Campeonato de Futebol

Atividade da Unidade 2 de Linguagem de Programação I. Leia `ENUNCIADO.md`
antes de começar.

Sistema em C++ para cadastrar times de futebol, registrar partidas e acompanhar
estatísticas e a classificação de um campeonato. A descrição completa está em
`DESCRICAO.md`.

## Arquivos

```text
.
├── AGENTS.md       regras que a IA lê antes de cada pedido
├── DESCRICAO.md    a descrição do sistema, escrita por você
├── ENUNCIADO.md    a atividade
├── PLANO.md        plano de implementação do sistema
├── README.md       este arquivo
├── exemplos/       arquivos de entrada para testar
├── include/        um .hpp por classe
└── src/            um .cpp por classe, mais a interface
```

## Compilar e executar

```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```

Se o comando mudar, atualize esta seção. Na correção eu vou usar o que
estiver escrito aqui.

### Testes das classes Time e Partida

Os testes ficam em `testes/`, fora de `src/`, para não conflitar com o
`main.cpp` do sistema:

```bash
g++ -std=c++11 -Wall -Wextra testes/testes_time_partida.cpp src/Time.cpp src/Partida.cpp -Iinclude -o testes_time_partida
./testes_time_partida
```

O programa imprime `[OK]` em cada teste que passa e encerra com código
de saída 0 quando não há falhas (`Falhas: 0`).

## Onde uso a STL

Escreva esta seção sem IA. Para cada container ou algoritmo da STL que o
sistema usa: em que classe ele está, o que guarda, e por que você escolheu
ele e não outro.

| Onde | O quê | Por quê |
| --- | --- | --- |
| | | |

## Como usei a IA

Escreva com as suas palavras:

- Modelo usado:
- Um pedido que deu certo, e por que você acha que deu certo:
- Um pedido que deu errado, o que veio errado e como você mudou o pedido:
- Uma coisa que a IA sugeriu e você recusou, e por quê:
