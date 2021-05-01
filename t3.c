/**
 * MC558 - Teste 03
 * Tiago de Paula - RA 187679
 */
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __GNUC__
// Atributos do GCC
#define attribute(...) __attribute__((__VA_ARGS__))
// Marcador de branch improvável (usado para erros)
#define unlikely(x)    (__builtin_expect((x), 0))

#else
// Fora do GCC, as macros não fazem nada.
#define attribute(...)
#define unlikely(x)      (x)
#endif

// Representação de infinito no cálculo do N. de Erdős
#define INFINITY    (SIZE_MAX - 1)

/* Representação do grafo. */
typedef struct graph {
    // número de vértices
    size_t len;
    // matriz de adjcências
    bool adj[];
} graph_t;

static
/* Leitura do grafo. */
graph_t *read_graph(size_t order, size_t size)
attribute(malloc, cold, nothrow);

static
/* Cálculo do maior Número de Erdős. */
size_t max_erdos_number(const graph_t *graph)
attribute(nonnull, cold, nothrow);


/* Entrada do programa. */
int main(void) {
    size_t N, M;
    // dimensões do grafo
    int rv = scanf("%zu %zu", &N, &M);
    if unlikely(rv < 2) {
        fprintf(stderr, "Erro: Problema de leitura.\n");
        return EXIT_FAILURE;
    }

    // leitura e construção do grafo
    graph_t *graph = read_graph(N, M);
    if unlikely(graph == NULL) {
        fprintf(stderr, "Erro: Problema de leitura do grafo.\n");
        return EXIT_FAILURE;
    }

    // cálculo do resultado
    size_t max = max_erdos_number(graph);
    if unlikely(max == SIZE_MAX) {
        fprintf(stderr, "Erro: Problema no cálculo do resultado.\n");
        free(graph);
        return EXIT_FAILURE;
    }

    // apresentação o resultado
    if (max == INFINITY) {
        printf("infinito\n");
    } else {
        printf("%zu\n", max);
    }

    // fim do programa
    free(graph);
    return EXIT_SUCCESS;
}

/* * * * * *
 * LEITURA *
 * * * * * */

// Acesso do posição (i,j) na matriz de adjacências de 'G'.
#define adjacent(G, i, j) \
    (G)->adj[((i) * (G)->len + (j))]

static inline attribute(malloc, cold, nothrow)
/**
 *  Aloca a matriz de adjacências de um grafo com
 * '|V| = len', inicialmente vazio (sem arestas).
 *
 * Returna NULL em erro de alocação.
 */
graph_t *alloc_graph(size_t len) {
    if unlikely(len >= SIZE_MAX / sizeof(bool) / 2) return NULL;

    size_t fixed = offsetof(graph_t, adj);
    graph_t *new = calloc(fixed + len * len * sizeof(bool), 1);
    if unlikely(new == NULL) return NULL;

    new->len = len;
    return new;
}

/**
 *  Leitura do grafo pela entrada padrão.
 *
 * Retorna NULL em erro de alocação, problema de leitura
 * ou se os valores lidos não fazem sentido.
 */
graph_t *read_graph(size_t order, size_t size) {
    graph_t *g = alloc_graph(order);
    if unlikely(g == NULL) return NULL;

    for (size_t i = 0; i < size; i++) {
        size_t A, B;
        // leitura dos co-autores
        int rv = scanf("%zu %zu", &A, &B);
        // que devem ser menores que n(g)
        if unlikely(rv < 2 || A >= order || B >= order) {
            free(g);
            return NULL;
        }

        // marca os co-autores no grafo
        adjacent(g, A, B) = true;
        adjacent(g, B, A) = true;
    }
    return g;
}

/* * * * * * * *
 * PILHA - BFS *
 * * * * * * * */

// Dado da pilha para BFS.
typedef struct data {
    // vértice atual
    uint16_t node;
    // tamanho do caminho até lá
    uint16_t len;
} data_t;

// Pilha para BFS, implementada por
// um buffer circular.
typedef struct queue {
    // capacidade
    size_t cap;
    // início do buffer
    size_t ini;
    // tamanho do buffer
    size_t len;
    // ponteiro do buffer
    data_t *data;
} queue_t;


static attribute(const, cold, nothrow)
/**
 * Constrói uma nova pilha vazia.
 */
queue_t queue_new(void) {
    return (queue_t) {
        .cap = 0,
        .ini = 0,
        .len = 0,
        .data = NULL
    };
}

static attribute(nonnull, cold, nothrow)
/**
 * Desaloca memória usada na pilha.
 */
void queue_destroy(queue_t *queue) {
    if (queue->data != NULL) {
        free(queue->data);
    }
}

static attribute(nonnull, cold, nothrow)
/**
 * Tenta aumentar a capacidade da pilha.
 *
 * Retorna se houve sucesso na operação.
 */
bool queue_increase_size(queue_t *queue) {
    size_t new_cap;
    data_t *new;
    // primeira alocação
    if unlikely(queue->data == NULL) {
        new_cap = 32;
        new = malloc(new_cap * sizeof(data_t));
    // realocação do buffer
    } else {
        new_cap = 2 * queue->cap;
        new = reallocarray(queue->data, new_cap, sizeof(data_t));
    }
    // erro de alocação
    if unlikely(new == NULL) return false;

    // move os valores do final do buffer para suas novas posições
    memcpy(new + queue->cap, new, queue->ini);
    // ajusta a capacidade e o novo ponteiro
    queue->cap = new_cap;
    queue->data = new;
    return true;
}

static inline attribute(nonnull, hot, nothrow);
/**
 * Insere novo valor na pilha.
 *
 * Retorna 'false' em erro de alocação.
 */
bool queue_push(queue_t *queue, data_t value) {
    // aumenta espeço para novos dados
    if unlikely(queue->len >= queue->cap) {
        bool ok = queue_increase_size(queue);
        if unlikely(!ok) {
            return false;
        }
    }
    // insere no final do buffer
    size_t end = (queue->ini + queue->len) % queue->cap;
    queue->data[end] = value;
    queue->len += 1;
    return true;
}

static inline attribute(nonnull, hot, nothrow);
/**
 * Remove valor do topo da pilha.
 *
 * Retorna 'false' se estiver vazio.
 */
bool queue_pop(queue_t * restrict queue, data_t * restrict data) {
    if unlikely(queue->len == 0) {
        return false;
    }
    // remove da primeira posição
    *data = queue->data[queue->ini];
    queue->ini += 1;
    queue->len -= 1;
    return true;
}

/* * * * * *
 * CÁLCULO *
 * * * * * */

static inline attribute(hot, nothrow)
/**
 *  Busca do maior caminho em 'graph' partindo de 'initial'.
 * O nó inicial não é contado.
 *
 * Usa um buffer externo para marcar nós visitados.
 */
size_t longest_path(const graph_t * restrict _graph, bool * restrict _visited, size_t initial) {
    return 0;
}

/**
 *  Cálculo do maior Número de Erdős do grafo dado.
 *
 * Retorna 'SIZE_MAX' em erro de alocação e 'INFINITY',
 * se não existir tal número, i.e. é infinito.
 */
size_t max_erdos_number(const graph_t *graph) {
    // nós visitados na busca
    bool *visited = calloc(graph->len, sizeof(bool));
    if unlikely(visited == NULL) return SIZE_MAX;

    // maior caminho encontrado
    size_t path_len = longest_path(graph, visited, 0);

    // checa se todos os nós foram visitados
    for (size_t i = 0; i < graph->len; i++) {
        if (!visited[i]) {
            free(visited);
            return INFINITY;
        }
    }
    free(visited);

    // caminho mais longo, visitando todos os nós
    return path_len;
}
