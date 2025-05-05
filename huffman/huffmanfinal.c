/**
 * @file huffmanfinal.c
 * @brief Implementação da compressão e decompressão de Huffman para qualquer tipo de arquivo
 * Todas as estruturas são encapsuladas com ponteiros void (TADs)
 * As funções estão documentadas no estilo JavaDoc
 */

#include "huffman.h" // inclusão do TAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> //para usar acentuacao
 
//--------- ESTRUTURAS INTERNAS ---------
 
typedef struct no {
    unsigned char caractere;
    int freq;
    struct no* left;
    struct no* right;
    struct no* next;
} No;
 

typedef struct {
    No* inicio;
    int tam;
} ListaInterna;

 
//--------- FUNÇÕES DA LISTA ORDENADA ---------
 

/**
 * @brief Cria uma lista encadeada vazia
 * @return Ponteiro genérico para a lista criada
 */
Lista criar_lista() 
{
    ListaInterna* l = malloc(sizeof(ListaInterna));
    l->inicio = NULL;
    l->tam = 0;
    return l;
}
 

/**
 * @brief Insere um nó na lista de forma ordenada por frequência (e ASCII em empate)
 * @param lista Ponteiro genérico para a lista
 * @param no_ Ponteiro para o nó a ser inserido
 */
void inserir_ordenado(Lista lista, void* no_) 
{
    //converte um ponteiro genérico void* lista em um ponteiro específico 
    //ListaInterna* l para acessar os campos da estrutura interna. (inicio e tam)
    ListaInterna* l = (ListaInterna*) lista;

    //converter o ponteiro genérico void* no_ em um ponteiro específico 
    //No* no para acessar os campos da estrutura No (como caractere, freq, etc.)
    No* no = (No*) no_;

    //lista vazia ?
    if(l->inicio == NULL)
    {
        l->inicio = no;
    }
    //lista nao vazia e frequencia menor que o inicio da lista
    else if (no->freq < l->inicio->freq || (no->freq == l->inicio->freq && no->caractere < l->inicio->caractere)) 
    {
        no->next = l->inicio;
        l->inicio = no;
    } 
    else 
    {
        No* temp = l->inicio;

        while (temp->next != NULL && (temp->next->freq < no->freq || (temp->next->freq == no->freq && temp->next->caractere < no->caractere))) 
        {
            temp = temp->next;
        }

        no->next = temp->next;
        temp->next = no;
    }
 
    l->tam++;

}
 

/**
 * @brief Remove o primeiro nó da lista (menor frequência)
 * @param lista Ponteiro genérico para a lista
 * @return Ponteiro para o nó removido
 */
void* remover(Lista lista) 
{
    ListaInterna* l = (ListaInterna*) lista;

    if (l->inicio == NULL)
    {
        return NULL;
    } 

    No* temp = l->inicio;
    l->inicio = temp->next;
    l->tam--;
    return temp;
}
 
 //--------- FUNÇÕES DA ÁRVORE DE HUFFMAN ---------
 

/**
 * @brief Monta a Árvore de Huffman a partir da lista ordenada
 * @param lista Ponteiro genérico para a lista
 * @return Ponteiro genérico para a raiz da árvore
 */
NoArvore montar_arvore(Lista lista) 
{
    while (((ListaInterna*)lista)->tam > 1) 
    {
        No* n1 = remover(lista);
        No* n2 = remover(lista);
 
        No* novo = malloc(sizeof(No));
        novo->caractere = '*';
        novo->freq = n1->freq + n2->freq;
        novo->left = n1;
        novo->right = n2;
        novo->next = NULL;
 
        inserir_ordenado(lista, novo);
    }
 
    return ((ListaInterna*)lista)->inicio;
}
 

/**
 * @brief Calcula a altura de uma árvore binária
 * @param no Ponteiro para o nó raiz
 * @return Altura da árvore (raiz conta como altura 0)
 */
int altura_arvore(No* no) 
{
    if (no == NULL)
    {
        return -1;
    } 
    else
    {
        int esq = altura_arvore(no->left) + 1;
        int dir = altura_arvore(no->right) + 1;

        if(esq > dir)
        {
            return esq;
        }
        else
        {
            return dir;
        }
    }
}
 

/**
 * @brief Gera a tabela de códigos binários baseada na árvore de Huffman
 * @param dicionario Vetor de strings onde será salvo cada código
 * @param no Ponteiro para o nó atual da árvore
 * @param caminho Código binário gerado até o nó atual
 * @param colunas Tamanho máximo de cada código
 */
void gerar_tabela(char** dicionario, No* no, char* caminho, int colunas) 
{
    char esq[colunas], dir[colunas];
 
    //verificar se estou em uma folha e copiar o caminho
    if (no->left == NULL && no->right == NULL) 
    {
        strcpy(dicionario[no->caractere], caminho);
    } 
    else 
    {
        strcpy(esq, caminho);
        strcpy(dir, caminho);
 
        strcat(esq, "0");
        strcat(dir, "1");
 
        gerar_tabela(dicionario, no->left, esq, colunas);
        gerar_tabela(dicionario, no->right, dir, colunas);
     }
 }
 

/**
 * @brief Escreve o cabeçalho no arquivo compactado
 * @param f Arquivo de saída
 * @param trash Número de bits de lixo no último byte
 * @param tamanho_arvore Número de bytes da árvore em pré-ordem
 */
void escrever_header(FILE* f, int trash, int tamanho_arvore) 
{
    int cabecalho = (trash << 13) | tamanho_arvore;
    unsigned char byte1 = (cabecalho >> 8) & 0xFF;
    unsigned char byte2 = cabecalho & 0xFF;
    fputc(byte1, f);
    fputc(byte2, f);
}
 

/**
 * @brief Escreve a árvore de Huffman em pré-ordem no arquivo compactado
 * @param no Ponteiro para o nó raiz
 * @param f Arquivo de saída
 * @param cont Ponteiro para o contador de bytes escritos
 */
void escrever_pre_ordem(No* no, FILE* f, int* cont) 
{
    if (no == NULL) return;
 
    if (no->left == NULL && no->right == NULL) 
    {
        if (no->caractere == '*' || no->caractere == '\\') 
        {
            fputc('\\', f);
            (*cont)++;
        }

        fputc(no->caractere, f);
        (*cont)++;

    } 
    else 
    {
         
        fputc('*', f);
         
        (*cont)++;
         
        escrever_pre_ordem(no->left, f, cont);
        escrever_pre_ordem(no->right, f, cont);
    }
}
 

/**
 * @brief Função principal para gerar o arquivo .huff compactado
 * @param nome_entrada Nome do arquivo original
 * @param nome_saida Nome do arquivo compactado (.huff)
 */
void gerar_arquivo_huff(const char* nome_entrada, const char* nome_saida) 
{
    // abrir o arquivo de entrada
    FILE* in = fopen(nome_entrada, "rb");
    if (!in) 
    {
        printf("Erro ao abrir arquivo de entrada.\n");
        exit(1);
    }

    // calcular tamanho do arquivo
    fseek(in, 0, SEEK_END);  //vai ate o fim do arquivo
    long tamanho = ftell(in);  //altura do arquivo
    rewind(in);  // volta para o inicio do arquivo

    // ler todo o conteúdo
    unsigned char* texto = malloc(tamanho);
    fread(texto, 1, tamanho, in);  //ler tudo o arquivo no texto
    fclose(in);

    //tabela de frequencia de cada caractere
    unsigned int tabela_frequencia[TAM] = {0};

    for (long i = 0; i < tamanho; i++) 
    {
        tabela_frequencia[texto[i]]++;
    }

    // criar lista ordenada
    Lista lista = criar_lista();  //criar uma lista vazia

    for (int i = 0; i < TAM; i++) 
    {
        if (tabela_frequencia[i] > 0) 
        {
            No* novo = malloc(sizeof(No));
            novo->caractere = i;
            novo->freq = tabela_frequencia[i];
            novo->left = NULL;
            novo->right = NULL;
            novo->next = NULL;

            inserir_ordenado(lista, novo);
        }
    }

    // montar a árvore de Huffman
    No* raiz = (No*) montar_arvore(lista);

    //montar a tabela de codificacao
    int colunas = altura_arvore(raiz) + 1;

    char** nova_tabela = malloc(TAM * sizeof(char*));

    for (int i = 0; i < TAM; i++) 
    {
        nova_tabela[i] = calloc(colunas, sizeof(char));
    }

    gerar_tabela(nova_tabela, raiz, "", colunas);

    // abrir o arquivo de saída
    FILE* out = fopen(nome_saida, "wb");
    if (!out) 
    {
        printf("Erro ao abrir arquivo de saída.\n");
        exit(1);
    }

    //reserve 2 bytes para o cabecalho 1 bytes = 8 bits
    fputc(0, out);
    fputc(0, out);

    // escrever árvore em pré-ordem
    int tamanho_arvore = 0;
    escrever_pre_ordem(raiz, out, &tamanho_arvore);

    // compactar diretamente bit a bit
    unsigned char byte = 0;
    int bits_preenchidos = 0;

    for (long i = 0; i < tamanho; i++) 
    {
        char* codigo = nova_tabela[texto[i]];  //para cada caractere, recupere seu código Huffman

        for (int j = 0; codigo[j] != '\0'; j++) 
        {
            //para cada bit do código, construa o byte a ser gravado

            if (codigo[j] == '1') 
            {
                //desloque o bit 1 para a posição apropriada no byte
                byte = byte | (1  << ( 7 - bits_preenchidos));
            }
            bits_preenchidos++;

            //quando um byte estiver completo (8 bits), gravá-lo no
            if (bits_preenchidos == 8) 
            {
                fputc(byte, out);
                byte = 0;
                bits_preenchidos = 0;
            }
        }
    }

    //se sobrou bits não escritos (último byte incompleto)
    int trash = 0;
    if (bits_preenchidos > 0) 
    {
        byte <<= (8 - bits_preenchidos);
        fputc(byte, out);
        trash = 8 - bits_preenchidos;  // bits não usados
    }

    // voltar e escrever o cabeçalho correto
    rewind(out);
    escrever_header(out, trash, tamanho_arvore);

    fclose(out);

    // limpeza
    free(texto);
    for (int i = 0; i < TAM; i++) 
    {
        free(nova_tabela[i]);
    }
    free(nova_tabela);

    printf("Arquivo %s compactado com sucesso em %s!\n", nome_entrada, nome_saida);
}


// --------- DESCOMPACTAÇÃO ---------


/**
 * @brief Cria um novo nó folha para a árvore de Huffman
 * @param c Caractere que será armazenado no nó
 * @return Ponteiro para o novo nó criado
 */
No* criar_no(unsigned char c)
{
    No* novo = malloc(sizeof(No));
    novo->caractere = c;
    novo->left = NULL;
    novo->right = NULL;

    return novo;
}


/**
 * @brief Libera a memória de toda a árvore de Huffman
 * @param no Ponteiro para o nó raiz da árvore
 */
void liberar_arvore(No* no) 
{
    if (no) 
    {
        liberar_arvore(no->left);
        liberar_arvore(no->right);
        free(no);
    }
}


/**
 * @brief Decodifica os bits do arquivo e reescreve o arquivo original
 * @param entrada Arquivo compactado
 * @param saida Arquivo descompactado
 * @param raiz Árvore de Huffman reconstruída
 * @param trash Número de bits de lixo no último byte
 */
void decodificar(FILE* entrada, FILE* saida, No* raiz, int trash)
{
    No* atual = raiz;
    unsigned char* dados; //tabela para conter todo o arquivo compactado
    long tamanho;
    int total_bits, bit;

    //salve a posição atual (início dos bits) após a pré-ordem
    long pos_bits = ftell(entrada);

    //ir até o final para descobrir o tamanho
    fseek(entrada, 0, SEEK_END);
    tamanho = ftell(entrada) - pos_bits; //tamanho em bytes dos dados compactados

    //voltar para o inicio
    fseek(entrada, pos_bits, SEEK_SET);

    //alloca memoire para dados e ler tudo o arquivo compactado em dados
    dados = malloc(tamanho);
    fread(dados, 1, tamanho, entrada);

    //NUmero total de bits Uteis
    total_bits = (tamanho * 8) - trash;

    for(int i = 0; i < total_bits; i++)
    {
        //achar o bit 
        // i / 8 : descubra em qual byte o bit i está
        // i % 8 : descubra qual posicao (0 a 7) do bit dentro deste byte
        // (dados[i / 8] >> (7 - (i%8))) : desloca o byte para trazer o bit desejado para a ultima posicao (posicao 0)
        // & 1 : isola apenas o ultimo bit para saber se é 0 ou 1
        bit = (dados[i / 8] >> (7 - (i % 8))) &1;

        if(bit == 0)
        {
            atual = atual->left;
        }
        else
        {
            atual  = atual->right;
        }

        if(atual->left == NULL && atual->right == NULL)
        {
            fputc(atual->caractere, saida);
            atual = raiz;
        }
    }

    free(dados);
}



/**
* @brief Reconstrói a árvore de Huffman a partir do
* @param f Arquivo de entrada
* @param tamanho Tamanho restante da árvore (atualizado)
* @return Ponteiro para a raiz da árvore
*/
No* reconstruir_arvore(FILE* f, int* tamanho)
{
    if(*tamanho <= 0)
    {
        return NULL;
    }

    unsigned char c;
    fread(&c, 1, 1, f); //ler 1 byte de f em c
    (*tamanho)--;

    if(c == '\\')
    {
        fread(&c, 1, 1, f);
        (*tamanho)--;
        return criar_no(c);
    }
    else if(c != '*')
    {
        return criar_no(c);
    }

    No* no = criar_no('*');
    no->left = reconstruir_arvore(f, tamanho);
    no->right = reconstruir_arvore(f, tamanho);
    return no;
}


/**
 * @brief Função principal para descompactar um arquivo .huff
 * @param nome_entrada Caminho do arquivo .huff
 * @param nome_saida Caminho para salvar o arquivo descompactado
 */
void descompactar(const char* nome_entrada, const char* nome_saida)
{
    //abrir o arquivo .huff no modo de leitura binária
    FILE* entrada = fopen(nome_entrada, "rb");
    if(!entrada)
    {
        printf("Erro ao abrir o arquivo %s.\n", nome_entrada);
        exit(1);
    }

    //ler o cabacalho (trash + tamanho_arvore)
    unsigned char cabeccalho[2];
    fread(cabeccalho, 1, 2, entrada);
    int trash = cabeccalho[0] >> 5;  //eslocamento de 5 bits para a direita
    int tamanho_arvore =((cabeccalho[0] & 0x1F) << 8) | cabeccalho[1];

    //reconstruir a Árvore Huffman
    No* raiz = reconstruir_arvore(entrada, &tamanho_arvore);

    //decodificar o arquivo
    FILE* saida = fopen(nome_saida, "wb"); //write binaire
    if(!saida)
    {
        printf("Erro ao criar o arquivo %s.\n", nome_saida);
        exit(1);
    }

    decodificar(entrada, saida, raiz, trash);

    printf("Arquivo %s descompactado com sucesso em %s!\n", nome_entrada, nome_saida);

    fclose(entrada);
    fclose(saida);
    liberar_arvore(raiz);
}



/**
 * @brief Função principal do programa de compressão e descompressão Huffman
 *
 * Controla o fluxo geral:
 * - Se o argumento for "-c", realiza a compressão do arquivo de entrada
 * - Se o argumento for "-d", realiza a descompressão de um arquivo .huff
 * - Exibe mensagens de erro e instruções em caso de uso incorreto
 *
 * @param argc Número de argumentos da linha de comando
 * @param argv Vetor de strings com os argumentos:
 *             argv[1] - opção "-c" (compactar) ou "-d" (descompactar)
 *             argv[2] - nome do arquivo de entrada
 *             argv[3] - nome do arquivo de saída
 * @return 0 em caso de sucesso, 1 em caso de erro de uso
 */
int main(int argc, char* argv[]) 
{
    setlocale(LC_ALL, "Portuguese");  // para acentuacao
    
    if(argc != 4 || (strcmp(argv[1], "-c") != 0 ) && (strcmp(argv[1], "-d") != 0))
    {
        printf("\n");
        printf("Uso : ./huffman [-c | -d] entrada saida\n");
        printf(" -c : Compactar\n");
        printf(" -d : Descompactar\n");
        printf("\n");
        return 1;
    }
    
    if(strcmp(argv[1], "-c") == 0)
    {
        gerar_arquivo_huff(argv[2], argv[3]);
    }
    else if(strcmp(argv[1], "-d") == 0) 
    {
        if(!strstr(argv[2], ".huff"))
        {
            printf("\n");
            printf("Erro: O arquivo de entrada deve ter a extensão .huff\n");
            printf("\n");
        }
        else
        {
            descompactar(argv[2], argv[3]);
        }
    }
    
    return 0;
}
