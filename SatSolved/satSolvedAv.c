#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VARS 100
#define MAX_CLAUSES 1000

typedef struct {
    int *literals;
    int size;
} Clause;

typedef struct {
    Clause *clauses;
    int num_vars;
    int num_clauses;
} Formula;

typedef struct AssignNode {
    int var; // variável atribuída neste nó
    int value; // 1 = true, -1 = false
    struct AssignNode *left;   // atribuição false
    struct AssignNode *right;  // atribuição true
    struct AssignNode *parent; // ancestral (para reconstruir o caminho)
} AssignNode;

// Cria novo nó de atribuição
AssignNode* create_node(int var, int value, AssignNode *parent) {
    AssignNode *node = malloc(sizeof(AssignNode));
    node->var = var;
    node->value = value;
    node->left = node->right = NULL;
    node->parent = parent;
    return node;
}

// Retorna valor da variável a partir da árvore de atribuições
int get_assignment(AssignNode *node, int var) {
    while (node) {
        if (node->var == var)
            return node->value;
        node = node->parent;
    }
    return 0; // unset
}

// Avalia literal (positivo ou negativo)
bool eval_literal(AssignNode *node, int lit) {
    int var = abs(lit);
    int val = get_assignment(node, var);
    if (val == 0) return false;
    return (lit > 0 && val == 1) || (lit < 0 && val == -1);
}

// Verifica se cláusula está satisfeita
bool is_clause_satisfied(Formula *F, Clause *clause, AssignNode *node) {
    for (int i = 0; i < clause->size; i++) {
        if (eval_literal(node, clause->literals[i])) return true;
    }
    return false;
}

// Verifica se cláusula é insatisfatível sob a atribuição atual
bool is_clause_unsatisfiable(Formula *F, Clause *clause, AssignNode *node) {
    for (int i = 0; i < clause->size; i++) {
        int var = abs(clause->literals[i]);
        if (get_assignment(node, var) == 0)
            return false;
    }
    return !is_clause_satisfied(F, clause, node);
}

// SAT principal (busca recursiva)
bool sat_tree(Formula *F, AssignNode *node, AssignNode **solution) {
    bool all_satisfied = true;
    for (int i = 0; i < F->num_clauses; i++) {
        if (is_clause_unsatisfiable(F, &F->clauses[i], node))
            return false;
        if (!is_clause_satisfied(F, &F->clauses[i], node))
            all_satisfied = false;
    }

    if (all_satisfied) {
        *solution = node;
        return true;
    }

    for (int i = 1; i <= F->num_vars; i++) {
        if (get_assignment(node, i) == 0) {
            node->right = create_node(i, 1, node);
            if (sat_tree(F, node->right, solution)) return true;
            node->left = create_node(i, -1, node);
            if (sat_tree(F, node->left, solution)) return true;
            return false;
        }
    }

    return false;
}

// Imprime atribuições da solução
void print_solution(AssignNode *node, int num_vars) {
    int result[MAX_VARS + 1] = {0};
    while (node && node->var != 0) {
        result[node->var] = node->value;
        node = node->parent;
    }

    for (int i = 1; i <= num_vars; i++) {
        printf("x%d = %s\n", i,
               result[i] == 1 ? "true" :
               result[i] == -1 ? "false" : "unset");
    }
}

// Leitura do arquivo DIMACS
void read_dimacs(const char *filename, Formula *F) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    F->clauses = malloc(sizeof(Clause) * MAX_CLAUSES);
    char line[256];
    int clause_idx = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == 'c' || line[0] == '\n') continue;

        if (line[0] == 'p') {
            sscanf(line, "p cnf %d %d", &F->num_vars, &F->num_clauses);
        } else {
            F->clauses[clause_idx].literals = malloc(sizeof(int) * MAX_VARS);
            F->clauses[clause_idx].size = 0;

            int lit;
            char *ptr = line;
            while (sscanf(ptr, "%d", &lit) == 1 && lit != 0) {
                F->clauses[clause_idx].literals[F->clauses[clause_idx].size++] = lit;
                while (*ptr && *ptr != ' ') ptr++;
                while (*ptr == ' ') ptr++;
            }

            clause_idx++;
        }
    }

    fclose(fp);
}

// Libera memória dos dados da fórmula
void free_formula(Formula *F) {
    for (int i = 0; i < F->num_clauses; i++) {
        free(F->clauses[i].literals);
    }
    free(F->clauses);
}

// Libera memória da árvore de atribuições
void free_tree(AssignNode *node) {
    if (!node) return;
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s arquivo.cnf\n", argv[0]);
        return 1;
    }

    Formula F;
    read_dimacs(argv[1], &F);

    AssignNode *root = create_node(0, 0, NULL);  // raiz dummy
    AssignNode *solution_node = NULL;

    bool satisfiable = sat_tree(&F, root, &solution_node);

    if (satisfiable && solution_node != NULL) {
        printf("SAT!\n");
        print_solution(solution_node, F.num_vars);
    } else {
        printf("UNSAT!\n");
    }

    free_tree(root);
    free_formula(&F);
    return 0;
}
