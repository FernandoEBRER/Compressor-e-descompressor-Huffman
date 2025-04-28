/**
* @file huffman.h
* @brief Interface TAD (Tipos Abstratos de Dados) para compressão Huffman genérica.
*/

#ifndef HUFFMAN_H
#define HUFFMAN_H
 
#ifdef __cplusplus
extern "C" {
#endif
 
#define TAM 256
 
/** Tipo opaco para nós da árvore de Huffman */
typedef void* NoArvore;
 
/** Tipo opaco para lista encadeada de nós */
typedef void* Lista;
 
//----------- Lista Encadeada -----------
 
/**
* @brief Cria uma lista encadeada vazia
* @return ponteiro para Lista
*/
Lista criar_lista();
 
/**
* @brief Insere um nó ordenadamente na lista
* @param lista ponteiro para Lista
* @param no ponteiro para o nó Huffman
*/
void inserir_ordenado(Lista lista, void* no);
 
/**
* @brief Remove o primeiro nó da lista
* @param lista ponteiro para Lista
* @return ponteiro para o nó removido
*/
void* remover(Lista lista);
 
//----------- Compressão Huffman -----------
 
/**
* @brief Cria a árvore de Huffman a partir da lista
* @param lista Lista com os nós
* @return raiz da árvore
*/
NoArvore montar_arvore(Lista lista);
 
/**
* @brief Gera o arquivo .huff a partir de um arquivo genérico
* @param nome_entrada nome do arquivo a ser comprimido
* @param nome_saida nome do arquivo .huff gerado
*/
void gerar_arquivo_huff(const char* nome_entrada, const char* nome_saida);
 
#ifdef __cplusplus
}
#endif
 
#endif // HUFFMAN_H
 