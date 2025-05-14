1. Título do Projeto :
  Compressão e Descompressão de Arquivos com Huffman

2. Descrição do Projeto :

  Este projeto implementa um algoritmo de compressão e descompressão de arquivos baseado no **código de Huffman**.

  - É capaz de comprimir **qualquer tipo de arquivo** (texto, imagem, vídeo, áudio, etc.).
  - Também pode descomprimir arquivos gerados no formato `.huff`.
  - O projeto separa a **implementação** (huffmanfinal.c) da **interface** (huffman.h).
  - Todas as estruturas de dados são **encapsuladas utilizando ponteiros `void*`** (TADs).
  - Todas as funções estão **documentadas seguindo o estilo JavaDoc**.

3. Instruções de Compilação :

  Para compilar o projeto :

        gcc huffmanfinal.c -o huffmanfinal
        Isso irá gerar o executável chamado huffmanfinal

  ### Para comprimir um arquivo :

        ./huffmanfinal -c arquivo_original.txt arquivo_comprimido.huff
  Exemplo :
            ./huffmanfinal -c testo.txt fer.huff 

  ### Para descomprimir um arquivo .huff :
  
        ./huffmanfinal -d arquivo_entrada.huff arquivo_saida.txt
  Exemplo :
            ./huffmanfinal -d fer.huff jjj.txt
            
SAT Solver em C
Este projeto implementa um resolvedor de fórmulas booleanas no formato CNF (Conjunctive Normal Form) usando uma árvore de decisões. A entrada deve estar no padrão DIMACS CNF.

1. Visão Geral
O programa lê um arquivo .cnf, constrói a representação da fórmula e tenta encontrar uma atribuição das variáveis que satisfaça todas as cláusulas. Ele imprime a solução encontrada, se existir.

2. Estrutura
Leitura do arquivo DIMACS.

Representação da fórmula e das cláusulas.

Algoritmo de busca em árvore para tentar todas as possíveis atribuições.

Impressão do resultado SAT/UNSAT.

3. Compilação
Para compilar o código, você precisa ter um compilador C instalado, como o gcc.

4. Passos
Salve o código em um arquivo chamado sat_solver.c.

Compile com:

bash
Copiar
Editar
gcc -o sat_solver sat_solver.c
5. Execução
Após compilar, execute o programa passando um arquivo .cnf no formato DIMACS como argumento:

bash
Copiar
Editar
./sat_solver exemplo.cnf
Exemplo de uso:
bash
Copiar
Editar
./sat_solver testes/formula1.cnf
6. Formato do Arquivo DIMACS
Exemplo de um arquivo .cnf com 3 variáveis e 2 cláusulas:

css
Copiar
Editar
c Exemplo de fórmula
p cnf 3 2
1 -3 0
2 3 -1 0
Linhas iniciadas com c são comentários.

A linha p cnf <num_vars> <num_clauses> define o número de variáveis e cláusulas.

Cada linha seguinte representa uma cláusula, terminada por 0.

7. Liberação de Memória
O programa libera corretamente toda a memória alocada dinamicamente ao final da execução.

8. Erros Comuns
"Uso: ./sat_solver arquivo.cnf": ocorre quando o caminho para o arquivo .cnf não é passado como argumento.

"Erro ao abrir arquivo": o arquivo passado não foi encontrado ou não pôde ser aberto.

9. Licença
Este código é um exemplo educacional e está disponível sob licença MIT.
