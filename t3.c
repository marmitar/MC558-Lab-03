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


/* Representação do grafo. */
typedef struct graph {
    // número de vértices
    size_t len;
    // matriz de adjcências
    bool adj[];
} graph_t;

static inline
/* Leitura do grafo. */
graph_t *read_graph(size_t order, size_t size)
attribute(malloc, cold, nothrow);

static inline
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
    if (max == SIZE_MAX) {
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

/**
 *  Cálculo do maior Número de Erdős do grafo dado.
 *
 * Retorna SIZE_MAX se não existir tal número.
 */
size_t max_erdos_number(const graph_t *_graph) {
    return SIZE_MAX;
}
