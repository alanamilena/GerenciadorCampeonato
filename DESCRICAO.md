# Descrição do sistema

## Nome e ideia

Este sistema é um gerenciador de campeonatos esportivos, desenvolvido para organizar e acompanhar competições de futebol. Ele serve para organizadores de torneios e torcedores registrarem times, cadastrarem partidas e acompanharem a tabela de classificação em tempo real com critérios de desempate.

## O que o sistema guarda

- Time: Cada time possui nome, pontos, gols marcados, gols sofridos, saldo de gols e partidas jogadas, além do total de cartões amarelos e vermelhos recebidos.
- Partida: Cada partida registra o time da casa, o time visitante, os gols de cada time e a quantidade de cartões amarelos e vermelhos recebidos por cada equipe na partida.
- Campeonato: Gerencia o conjunto de times cadastrados, o histórico de partidas realizadas e calcula a tabela de classificação.

## O que dá para fazer

1. Cadastrar time: Pede o nome do time e o adiciona ao campeonato.
2. Listar times: Mostra todos os times cadastrados em ordem alfabética.
3. Registrar partida: Pede os nomes dos dois times, os gols marcados e a quantidade de cartões amarelos e vermelhos de cada equipe. Após validar os dados, registra a partida, atualiza automaticamente as estatísticas dos times e exibe uma mensagem de confirmação.
4. Exibir tabela de classificação: Mostra a tabela ordenada por pontos (decrescente), saldo de gols, gols marcados e disciplina (menos cartões).
5. Buscar time: Pede o nome de um time e exibe suas estatísticas detalhadas (incluindo cartões).
6. Sair: Encerra o programa.

## Regras

- Não é permitido cadastrar dois times com o mesmo nome.
- Uma partida não pode ser cadastrada entre um time e ele mesmo.
- Os times participantes de uma partida precisam já estar cadastrados no campeonato.
- A pontuação segue o padrão: 3 pontos por vitória, 1 ponto por empate e 0 pontos por derrota.
- O saldo de gols é calculado como: (Gols Marcados - Gols Sofridos).
- Os mesmos times podem se enfrentar mais de uma vez no campeonato, permitindo partidas de turno e returno.
- A tabela de classificação é ordenada criticamente por:
  1. Pontos (maior primeiro)
  2. Saldo de gols (maior primeiro)
  3. Gols marcados (maior primeiro)
  4. Menor número de cartões vermelhos (critério de disciplina)
  5. Menor número de cartões amarelos
  6. Nome do time em ordem alfabética.

## Quando algo dá errado

- Time não existe: Se o usuário tentar registrar uma partida com um time não cadastrado ou buscar um time inexistente, o sistema exibe uma mensagem de erro informando que o time não foi encontrado.
- Cadastro duplicado: Se tentar cadastrar um time com um nome que já existe, o sistema avisa que o time já está cadastrado.
- Lista vazia: Se tentar exibir a tabela de classificação ou listar times sem nenhum cadastro, o sistema avisa que não há times cadastrados.
- Entrada inválida: Se o usuário digitar texto onde o programa espera um número (como nos gols, cartões ou opções do menu), o sistema exibe uma mensagem de erro e limpa a entrada.
- Valores negativos: se o usuário informar uma quantidade negativa de gols ou cartões, o sistema rejeitará a entrada e não registrará a partida nem alterará as estatísticas dos times.

## Classes que eu imagino

- Time: Guarda os dados estatísticos do clube e define o operador de comparação (`operator<`) para ordenação.
- Partida: Guarda os dados de um confronto específico entre dois times, placares e penalidades disciplinares.
- Campeonato: Concentra a lógica de negócio, armazenando os dados em estruturas STL e gerindo as regras do torneio.

## Exemplo de uso

=== MENU CAMPEONATO ===
1. Cadastrar time
2. Listar times
3. Registrar partida
4. Ver classificação
5. Buscar time
6. Sair
Escolha uma opção: 3
Time da casa: Flamengo
Time visitante: Vasco
Gols do Flamengo: 2 | Cartões Amarelos: 1 | Cartões Vermelhos: 0
Gols do Vasco: 1 | Cartões Amarelos: 2 | Cartões Vermelhos: 1
OK: Partida registrada com sucesso!