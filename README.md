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
            
1. **Título do Projeto**:  
   Resolvedor de Fórmulas Booleanas em CNF (SAT Solver)

2. **Descrição do Projeto**:  

   Este projeto implementa um algoritmo para resolver fórmulas booleanas no formato **CNF (Conjunctive Normal Form)**, utilizando uma **árvore de decisões** recursiva.

   - Lê arquivos no padrão **DIMACS CNF**, amplamente utilizado em competições de SAT.
   - Verifica se existe uma atribuição de variáveis que satisfaça todas as cláusulas (SAT) ou se isso é impossível (UNSAT).
   - Imprime a solução encontrada, se houver, com os valores de cada variável.
   - Toda a estrutura é modularizada com uso adequado de alocação dinâmica e liberação de memória.

3. **Instruções de Compilação**:  

   Para compilar o projeto:


Isso irá gerar o executável chamado `sat_solver`.

4. **Para executar o resolvedor com um arquivo `.cnf`**:


**Exemplo**:

5. **Formato do Arquivo DIMACS**:

Exemplo de um arquivo `.cnf` com 3 variáveis e 2 cláusulas:


- Linhas iniciadas com `c` são **comentários**.
- A linha `p cnf <num_vars> <num_clauses>` define o número de variáveis e cláusulas.
- Cada linha seguinte representa uma cláusula, terminada por `0`.

6. **Liberação de Memória**:  

O programa **libera corretamente toda a memória** alocada dinamicamente, tanto da estrutura da fórmula quanto da árvore de atribuições.

7. **Erros Comuns**:

- `"Uso: ./sat_solver arquivo.cnf"`: ocorre quando o caminho para o arquivo `.cnf` **não é fornecido** como argumento.
- `"Erro ao abrir arquivo"`: o arquivo passado **não foi encontrado** ou **não pôde ser lido**.

8. **Licença**:

Este código é fornecido como um exemplo **educacional** e está disponível sob a **licença MIT**.
