# Sistema de Autocomplete de Jogos com Trie

## Descrição

Sistema de autocomplete de jogos. A partir de um banco de dados previamente fornecido,
o sistema armazena os jogos em uma Trie, e utiliza esta estrutura para buscar jogos a
partir de um perefixo do título.

**Funcionalidades:**
- Inserir jogos na Trie;
- Ordenar a lista de jogos;
- Buscar um jogo pelo título exato;
- Buscar jogos por prefixo, retornando até $k$ sugestões de jogos mais populares;
- Exibir os resultados encontrados;
- Converter títulos e prefixos para a chave de busca utilizada internamente.

## Compilação e Execução

No Windows:

`g++ main.cpp Game.cpp Trie.cpp GamesDatabase.cpp -o app`

`.\app.exe k prefixo`

No Linux / Mac-OS:

`g++ main.cpp Game.cpp Trie.cpp GamesDatabase.cpp -o app`

`./app k prefixo`

**Importante:** Os comandos são obrigatórios para o funcionamento do programa.
O parâmetro $k$, que indica quantos resultados devem ser retornados, deve ser 
maior do que zero, e o $prefixo$ deve ser escrito com aspas se houver algum
espaço (caso contrário, as aspas são dispensáveis).

## Organização dos Arquivos

O sistema conta com uma base de dados, que corresponde a todos os jogos
que podem ser retornados. Para o funcionamento do sistema, existem três
classes: a classe `Game`, que possui todas as informações de um jogo;
a classe `TrieNode`, que corresponde aos nós da Trie; e a classe `Trie`,
que implementa o funcionamento do sistema.

**Principais funções da classe `Trie`:**
- `toSearchKey`: Converte uma string na chave de busca usada pela Trie;
- `getIndex`: Função auxiliar que calcula o índice do array de filhos a que um caractere
deve pertencer, seguindo a chave de busca;
- `insert`: Insere um jogo na Trie;
- `contains`: Verifica se existe um jogo com o título informado na Trie;
- `sortResults`: Ordena os jogos recebidos usando insertion sort por popularidade
e, em caso de empate, pela chave de busca;
- `search`: Função auxiliar que percorre uma subárvore a partir de um prefixo;
- `autocomplete`: Retorna até $k$ jogos mais populares a partir de um prefixo.

## Exemplos de Uso pela Linha de Comando

**Exemplo 1:** Execução bem-sucedida usando um prefixo sem espaços:

```console
./app 3 hea
[ Hearts of Iron IV | Victory is at your fingertips Your ability to lead your nation is your supreme weapon the strategy game Hearts of Iron IV lets you take command of any nation in World War II the most engaging conflict in world history | 174138 ]

[ Heavy Rain | Experience a gripping psychological thriller filled with innumerable twists and turns The hunt is on for a murderer known only as the Origami Killer Four characters each following their own leads must take part in a desperate attempt to prevent the killer from claiming a new victim | 8418 ]

[ Heat Signature | Heat Signature is a game from the developers of Gunpoint where you break into spaceships make terrible mistakes and think of clever ways out of them You take a mission fly to the target ship sneak inside and make clever use of your gadgets to distract ambush and take out the crew | 6186 ]
```

**Exemplo 2:** Execução bem-sucedida usando um prefixo com espaços:

```console
./app 2 "Hearts o"
[ Hearts of Iron IV | Victory is at your fingertips Your ability to lead your nation is your supreme weapon the strategy game Hearts of Iron IV lets you take command of any nation in World War II the most engaging conflict in world history | 174138 ]

[ Hearts of Iron III | Hearts of Iron III lets you play the most engaging conflict in world history World War 2 on all fronts as any country and through multiple different scenarios Guide your nation to glory between 1936 and 1948 and wage war conduct diplomacy and build your industry in the most detailed World War 2 game ever made | 4566 ]
```

**Exemplo 3:** Execução bem sucedida cujo prefixo não corresponde a nenhum jogo:
```console
./app 3 dojckjbi
No results found
```

**Exemplo 4:** Execução mal sucedida por número errado de argumentos:
```console
./app
Usage: ./app k prefix
```


