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

| Onde             | O quê               | Por quê |
|---|---|---|
| `Campeonato.hpp` | `std::map`          | Busca times pelo nome com `find()` e mantém as chaves ordenadas, ao contrário do `unordered_map`. |
| `Campeonato.hpp` | `std::list`         | Armazena o histórico de partidas adicionadas sequencialmente, embora um `vector` também servisse. |
| `Campeonato.cpp` | `std::vector<std::string>` | Armazena os nomes para listagem; percorrer o `map` diretamente também seria possível.      |
| `Campeonato.cpp` | `std::vector<Time>` | Copia os times para permitir ordená-los pelos critérios do campeonato.                            |
| `Campeonato.cpp` | `std::sort`         | Ordena o `vector` pelos critérios definidos em `operator<`; exige acesso aleatório, disponível no `vector`, mas não na `list` ou no `map`. |


## Como usei a IA

Escreva com as suas palavras:

- Modelo usado: OpenCode - Big Pickle
- Um pedido que deu certo, e por que você acha que deu certo: Um pedido que deu certo foi solicitar à IA que analisasse o funcionamento do sistema e ajudasse a identificar problemas durante os testes. Com isso, consegui verificar o comportamento do programa em diferentes situações e confirmar que o cadastro de times, o registro de partidas e a classificação funcionavam como esperado. Acredito que o pedido deu certo porque utilizei testes concretos para verificar as sugestões e conferir os resultados.
- Um pedido que deu errado, o que veio errado e como você mudou o pedido: Durante os testes finais, identifiquei que, quando a entrada do programa terminava sem que o usuário escolhesse a opção de sair, o menu continuava exibindo mensagens de erro indefinidamente. Para resolver o problema, direcionei a análise para o tratamento do EOF na função responsável pela leitura da opção do menu. A IA ajudou a identificar a causa e sugeriu uma alteração em `src/interface.cpp` para encerrar o programa quando a entrada acabasse. Depois, executamos o teste novamente e verificamos que o programa encerrava normalmente.
- Uma coisa que a IA sugeriu e você recusou, e por quê: A IA sugeriu alterar o arquivo `DESCRICAO.md` para ajustar a explicação sobre o cancelamento de partidas quando ocorre uma entrada inválida. Decidi não fazer essa alteração durante a Etapa 6, pois o foco era testar as funcionalidades do sistema e corrigir o problema de EOF. Preferi manter o escopo da etapa e evitar mudanças adicionais que não eram necessárias para resolver o problema identificado.
