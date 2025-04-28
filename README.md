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

        ./huffmanfinal -c arquivo_original.ext arquivo_comprimido.huff
  Exemplo :
            ./huffmanfinal -c testo.txt fer.huff 

  ### Para descomprimir um arquivo .huff :
  
        ./huffmanfinal -d arquivo_entrada.huff arquivo_saida.ext
  Exemplo :
            ./huffmanfinal -d fer.huff jjj.txt

