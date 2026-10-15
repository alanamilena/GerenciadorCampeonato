# Plano de implementação — Gerenciador de Campeonato

Este plano segue o `DESCRICAO.md`, as regras do `AGENTS.md` e os requisitos
do `ENUNCIADO.md`. Tudo em C++11, só com a biblioteca padrão: sem lambda,
sem `unordered_map`, sem `new`/`delete`. Cada etapa termina com um programa
que compila e pode ser testado antes de avançar, e merece um commit.

---

## 1. As classes do sistema

São as três classes imaginadas no `DESCRICAO.md`. As classes do sistema não
usam `cin` nem `cout`: recebem dados por parâmetro e devolvem resultados.

### Time (`include/Time.hpp` + `src/Time.cpp`)

**Guarda:** nome e as estatísticas do clube — pontos, gols marcados,
gols sofridos, saldo de gols, partidas jogadas, cartões amarelos e
cartões vermelhos (totais acumulados no campeonato).

**Métodos:**
- `Time(string nome)` — cria o time com tudo zerado, exceto o nome.
- `void atualizar(int golsMarcados, int golsSofridos, int amarelos, int vermelhos)`
  — soma 1 em partidas jogadas; soma gols e cartões; recalcula o saldo;
  soma 3 pontos (vitória), 1 (empate) ou 0 (derrota) conforme o placar.
- `bool operator<(const Time& outro) const` — comparação de desempate,
  usada pelo `std::sort` (ver etapa 5). O operador é definido de modo que
  `a < b` significa "a deve vir antes de b na tabela", ou seja, o time
  que deve aparecer **primeiro** é o **menor**. Assim, um `std::sort` em
  ordem crescente — sem lambda e sem inverter nada depois — produz
  exatamente a classificação correta, aplicando os critérios nesta ordem:
  1. maior pontuação;
  2. maior saldo de gols;
  3. maior número de gols marcados;
  4. menor número de cartões vermelhos;
  5. menor número de cartões amarelos;
  6. ordem alfabética do nome.
- Getters: `nome()`, `pontos()`, `golsMarcados()`, `golsSofridos()`,
  `saldo()`, `partidasJogadas()`, `amarelos()`, `vermelhos()`.

### Partida (`include/Partida.hpp` + `src/Partida.cpp`)

**Guarda:** um confronto específico — nome do time da casa, nome do
visitante, gols de cada equipe e cartões amarelos e vermelhos de cada
equipe na partida. Só guarda dados, sem regras.

**Métodos:**
- Construtor com os oito valores acima.
- Getters de todos os campos.

### Campeonato (`include/Campeonato.hpp` + `src/Campeonato.cpp`)

**Guarda:** o conjunto de times cadastrados, o histórico de partidas e
toda a lógica de negócio.

**Métodos:**
- `bool cadastrarTime(const string& nome)` — corta os espaços das pontas
  do nome; devolve `false` se o nome já estiver cadastrado (regra mora
  aqui, não na interface). Para inserir, usa `map::insert` com um par
  chave-valor: a chave é o nome já cortado e o valor é um `Time`
  construído com esse nome (`Time(nome)`), que nasce com as estatísticas
  zeradas. Assim o cadastro não depende de construtor padrão de `Time`.
- `vector<string> listarTimes()` — nomes em ordem alfabética (vem de
  graça das chaves do `map`).
- `int registrarPartida(const string& casa, const string& visitante,
  int golsCasa, int golsVisitante, int amarelosCasa, int vermelhosCasa,
  int amarelosVisitante, int vermelhosVisitante)` — devolve `0` = OK,
  `1` = algum time não encontrado, `2` = mesmo time duas vezes. No caso
  `0`: chama `atualizar` nos dois times do `map` e acrescenta a `Partida`
  no fim da lista.
- `bool buscarTime(const string& nome, Time& saida)` — copia o time para
  `saida` se existir; `false` caso contrário.
- `vector<Time> classificacao()` — copia os times do `map` para um
  `vector` e ordena com `std::sort` (que usa o `operator<` do `Time`).
- `bool vazio()` — se não há nenhum time cadastrado.

---

## 2. Containers da STL e justificativa

| Onde | Container/algoritmo | O que guarda | Por quê |
| --- | --- | --- | --- |
| `Campeonato` | `map<string, Time>` | os times, com o nome como chave | atende o requisito de pelo menos um `map`; a busca por nome é `map::find`; o `map` mantém as chaves em ordem alfabética, então "Listar times" e o desempate por nome vêm organizados |
| `Campeonato` | `list<Partida>` | o histórico de partidas | atende o requisito de pelo menos um `set` ou uma `list`; partidas só entram no fim e não precisamos de acesso pela posição; um `set` não serviria porque duas partidas iguais entre os mesmos times seriam descartadas, e a regra do `DESCRICAO.md` permite repetição (turno e returno) |
| `Campeonato::classificacao` | `vector<Time>` + `std::sort` | uma cópia dos times, para ordenar | atende o requisito de `sort` aplicado a objetos de classe própria; ordenar uma cópia deixa o `map` intacto; `sort` em `vector` é o algoritmo natural da STL |
| `Time` | `operator<` | a comparação completa de desempate | o `sort` precisa de um `operator<` na própria classe, como no exemplo 11 da aula; `a < b` significa "a deve vir antes de b na tabela" (o melhor time é o menor), então o `std::sort` em ordem crescente aplica, nesta ordem: maior pontuação, maior saldo de gols, maior número de gols marcados, menor número de cartões vermelhos, menor número de cartões amarelos e, por último, ordem alfabética do nome |
| `Campeonato::listarTimes` | `vector<string>` (retorno) | os nomes ordenados | a interface recebe um `vector` simples para imprimir, sem acesso direto ao `map` |

Objetos são guardados **diretamente** nos containers (`map` e `list`
guardam `Time` e `Partida` por valor). Nada de ponteiros com `new`.

---

## 3. Como os requisitos do enunciado serão atendidos

| Requisito do `ENUNCIADO.md` | Onde no sistema |
| --- | --- |
| Pelo menos três classes com responsabilidade clara | `Time` (estatísticas), `Partida` (dados de um confronto), `Campeonato` (regras de negócio) |
| Pelo menos um `map` | `map<string, Time> times` no `Campeonato` |
| Pelo menos um `set` ou uma `list` | `list<Partida> partidas` no `Campeonato` |
| `sort` ou `find` em objetos próprios com `operator<` | `std::sort` em `vector<Time>`, usando o `operator<` do `Time` (etapa 5); o `map::find` também busca objetos próprios |
| Interface em modo texto com menu numerado | `interface.cpp`: menu 1 a 6, igual ao `DESCRICAO.md` |
| Lógica separada da interface | as três classes não tocam em `cin`/`cout`; toda leitura e escrita fica em `interface.hpp`/`interface.cpp` e `main.cpp` |
| C++11 e só biblioteca padrão | comando do `README.md`: `g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema` |
| Casos de erro (prática 5.7) | tratados nas etapas 3, 4 e 5, conforme "Quando algo dá errado" do `DESCRICAO.md` |
| Arquivos de teste em `exemplos/` (prática 5.8) | criados nas etapas 3, 4, 5 e 6 |

---

## 4. Organização dos arquivos

Uma classe por par de arquivos, como manda o `AGENTS.md`; a interface em
arquivos próprios:

```text
include/Time.hpp        dados e estatísticas de um time
include/Partida.hpp     dados de um confronto
include/Campeonato.hpp  regras de negócio e containers
include/interface.hpp   leitura e escrita na tela
src/Time.cpp
src/Partida.cpp
src/Campeonato.cpp
src/interface.cpp
src/main.cpp            só cria o Campeonato e chama a interface
exemplos/               arquivos de entrada para os testes
```

O comando de compilação do `README.md` usa `src/*.cpp`, então arquivos
novos entram nele automaticamente — nenhuma mudança no `README.md` é
necessária.

**Divisão de responsabilidades:**
- **Interface** valida o formato: o valor é um número? é não negativo?
  (função `lerInteiro`, que lê a linha inteira com `getline` e, se não
  for número, descarta a linha e devolve `false` — erro e volta ao menu).
- **`Campeonato`** valida as regras: nome duplicado, time existente,
  mesmo time duas vezes. O corte de espaços das pontas também fica aqui.
- **`interface`** traduz os códigos de retorno em mensagens.

---

## 5. Divisão em etapas

São seis etapas. Cuma etapa: compile com o comando do `README.md`, rode o
programa, confira o resultado esperado e faça um commit.

### Etapa 1 — Classe Time (estatísticas)

**Objetivo:** ter um time com nome e estatísticas que se atualizam a cada
partida, e provar que o comando de compilação do `README.md` funciona.

**Arquivos criados:** `include/Time.hpp`, `src/Time.cpp`, `src/main.cpp`
(com um `main` de teste temporário, substituído na etapa 3).

**Classes e métodos:** `Time` — construtor, `atualizar`, getters.

**Funcionalidades prontas:** criar um time, somar uma partida nele e ler
suas estatísticas.

**Como compilar e testar:**
```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```

**Resultado esperado:** o `main` imprime as estatísticas de um time após
um ou mais chamados de `atualizar`. Conferir na tela: vitória soma 3
pontos (empate soma 1), o saldo bate com gols marcados − gols sofridos e
os cartões acumulam. Sem avisos do `-Wall -Wextra`. Depois, commit.

---

### Etapa 2 — Classe Partida (dados do confronto)

**Objetivo:** guardar um confronto completo (placar e cartões das duas
equipes), sem nenhuma regra.

**Arquivos criados:** `include/Partida.hpp`, `src/Partida.cpp`.
**Arquivos modificados:** `src/main.cpp` (o teste agora cria uma `Partida`).

**Classes e métodos:** `Partida` — construtor com os oito valores e
getters de todos os campos.

**Funcionalidades prontas:** montar uma partida em memória e imprimir
seus dados.

**Como compilar e testar:**
```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema
```

**Resultado esperado:** o `main` imprime os dados da partida no formato do
exemplo do `DESCRICAO.md`, por exemplo:
`Gols do Flamengo: 2 | Cartões Amarelos: 1 | Cartões Vermelhos: 0`.
Commit.

---

### Etapa 3 — Campeonato: cadastro e listagem de times (map + interface de verdade)

**Objetivo:** entrar no menu, cadastrar times (com corte de espaços e
proteção contra duplicado) e listá-los em ordem alfabética. É aqui que a
interface substitui o `main` de teste.

**Arquivos criados:** `include/Campeonato.hpp`, `src/Campeonato.cpp`,
`include/interface.hpp`, `src/interface.cpp`, `exemplos/cenario1.txt`.
**Arquivos modificados:** `src/main.cpp` (agora definitivo: só cria o
`Campeonato` e chama a interface).

**Classes e métodos:**
- `Campeonato` com o `map<string, Time>` e a `list<Partida>` (vazia nesta
  etapa, mas o campo já nasce): `cadastrarTime` (insere no `map` com
  `insert` de um par chave-valor — a chave é o nome cortado e o valor é
  `Time(nome)`, construído com o nome, sem depender de construtor padrão),
  `listarTimes`, `vazio`.
- `interface`: `executar(Campeonato&)` com o laço do menu; opções 1, 2 e 6
  funcionais (as demais mostram "opção ainda não disponível" até a etapa 5);
  `lerInteiro` com descarte da linha inválida.

**Funcionalidades prontas:** cadastrar time, duplicado detectado, nomes
com espaços e com espaços extras das pontas, listagem alfabética, opção
sair, erro de entrada no menu.

**Como compilar e testar:**
```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema < exemplos/cenario1.txt
```
O `cenario1.txt` deve conter: cadastro de uns quatro times (um com espaços
extras nas pontas), uma tentativa de duplicado, uma listagem e a opção 6.

**Resultado esperado na tela:** cadastros confirmados; o duplicado (por
exemplo, cadastrar `"  São Paulo  "` e depois `"São Paulo"`) recebe aviso
de que o time já está cadastrado; "flamengo" e "Flamengo" coexistem, pois
maiúscula e minúscula contam; a listagem sai em ordem alfabética; texto no
lugar da opção do menu mostra erro e reexibe o menu. Commit.

---

### Etapa 4 — Registrar partida no Campeonato

**Objetivo:** registrar partidas com todas as validações, atualizando as
estatísticas dos times e guardando o histórico na `list`.

**Arquivos criados:** `exemplos/cenario2.txt`.
**Arquivos modificados:** `include/Campeonato.hpp`, `src/Campeonato.cpp`,
`include/interface.hpp`, `src/interface.cpp`.

**Classes e métodos:**
- `Campeonato`: `registrarPartida` (códigos 0/1/2) e `buscarTime`
  (nascem juntos, pois `registrarPartida` já precisa achar os times com
  `map::find`).
- `interface`: opção 3 do menu — lê nomes, lê números com `lerInteiro`,
  rejeita negativos, chama `registrarPartida` e traduz o código de retorno
  na mensagem certa; em qualquer erro, cancela a partida e volta ao menu,
  sem alterar nada nos times.

**Funcionalidades prontas:** registrar partida válida; erros de time
inexistente e de mesmo time; entrada inválida e valor negativo cancelam a
operação.

**Como compilar e testar:**
```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema < exemplos/cenario1.txt   # a etapa anterior não quebrou
./sistema < exemplos/cenario2.txt
```
O `cenario2.txt` deve conter: cadastros, partidas válidas (inclusive os
mesmos times de novo, turno e returno), time inexistente, mesmo time,
texto no lugar de número e valor negativo.

**Resultado esperado na tela:** partida válida mostra
`OK: Partida registrada com sucesso!`; time inexistente mostra aviso de
que o time não foi encontrado; mesmo time duas vezes é recusado; texto ou
negativo mostra erro e o menu volta, sem nenhuma estatística alterada.
Commit.

---

### Etapa 5 — Classificação e busca (operator< + sort)

**Objetivo:** a tabela ordenada com todos os critérios de desempate e a
busca de um time com estatísticas detalhadas.

**Arquivos criados:** `exemplos/cenario3.txt`.
**Arquivos modificados:** `include/Time.hpp`, `src/Time.cpp`,
`include/Campeonato.hpp`, `src/Campeonato.cpp`, `include/interface.hpp`,
`src/interface.cpp`.

**Classes e métodos:**
- `Time`: `operator<` com os seis critérios — `a < b` significa "a deve
  vir antes de b na tabela" (o melhor time é o menor); com isso, o
  `std::sort` em ordem crescente monta a tabela correta: maior pontuação,
  maior saldo de gols, maior número de gols marcados, menor número de
  cartões vermelhos, menor número de cartões amarelos e, por último,
  ordem alfabética do nome.
- `Campeonato`: `classificacao` — copia os times do `map` para um
  `vector` e chama `std::sort` (sem lambda: ordena pelo `operator<`).
- `interface`: opções 4 e 5 — a tabela (com aviso de lista vazia) e a
  busca (com aviso de time não encontrado).

**Funcionalidades prontas:** tabela completa ordenada; times sem partidas
aparecem zerados; desempate por saldo, gols, cartões e nome; busca de um
time; erros de lista vazia e busca sem sucesso.

**Como compilar e testar:**
```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema < exemplos/cenario1.txt
./sistema < exemplos/cenario2.txt
./sistema < exemplos/cenario3.txt
```
O `cenario3.txt` deve montar um campeonato pequeno com empates de pontos
que só o desempate resolve, e depois pedir a tabela e algumas buscas.

**Resultado esperado na tela:** a tabela sai ordenada pelos seis
critérios, na mesma ordem das regras do `DESCRICAO.md`; um time que ainda
não jogou aparece com zeros; buscar "Flamengo" mostra os totais dele;
buscar um nome inexistente mostra erro; tabela ou listagem sem times
mostra aviso de que não há times cadastrados. Commit.

---

### Etapa 6 — Rodada completa de erros e conferência final

**Objetivo:** percorrer todos os casos de "Quando algo dá errado" do
`DESCRICAO.md` num só cenário e garantir que nada ficou solto.

**Arquivos criados:** `exemplos/cenario4.txt`.
**Arquivos modificados:** só correções pontuais se algum teste revelar
problema. Nenhuma classe nova.

**Funcionalidades prontas:** o sistema inteiro, cobrindo todos os erros.

**Como compilar e testar:**
```bash
g++ -std=c++11 -Wall -Wextra src/*.cpp -Iinclude -o sistema
./sistema < exemplos/cenario1.txt
./sistema < exemplos/cenario2.txt
./sistema < exemplos/cenario3.txt
./sistema < exemplos/cenario4.txt
```

**Resultado esperado:** os quatro cenários rodando sem travar e sem avisos
de compilação; o `cenario4.txt` cobre — time não existe, cadastro
duplicado, lista vazia, entrada inválida (com a partida em andamento sendo
cancelada) e valor negativo; conferir também o `git status` (nenhum `.o`
nem executável prestes a ser commitado). Commit final.

---

## 6. Depois das etapas (fora deste plano)

- Preencher a seção "Onde uso a STL" do `README.md` com as suas palavras,
  sem IA (etapa 6 do `ENUNCIADO.md`).
- Se algum momento a descrição precisar mudar, atualizar o `DESCRICAO.md`
  num commit próprio, como manda o `ENUNCIADO.md`.
