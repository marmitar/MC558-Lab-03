# MC558 - Tarefa 3

## Problema

### Número de Erdős

Paul Erdős (1913-1996) foi um matemático húngaro que gostava de resolver problemas e chegou a ganhar alguns importantes prêmios por resolver problemas matemáticos famosos. Erdős gostava particularmente das soluções mais simples e elegantes, e era brilhante na tarefa de encontrá-las. Diversas histórias curiosas permeiam sua biografia, como o fato de ter sido uma vez preso nos Estados Unidos por suspeita de espionagem ao ter adentrado sem permissão uma área militar restrita, enquanto caminhava distraidamente sem destino certo pensando na solução de um problema. Em parte por conta desse incidente, mas também por outras circunstâncias de sua vida pessoal, Erdős viveu de forma nômade por grande parte da sua vida. Passou temporadas como professor visitante em diversas universidades do mundo, trabalhando, em cada uma delas, com novos parceiros que traziam a ele novos problemas interessantes para resolver. Cada uma dessas parcerias normalmente resultava na publicação de novos teoremas matemáticos, totalizando mais de 1500 publicações em sua vida, com um conjunto de mais de 500 co-autores diferentes. Esse fato nada comum, chamou a atenção para essa “rede social” de coautores de Erdős, e motivou a definição do folclórico “Número de Erdős” (Erdős Number). Erdős é a única pessoa com Número de Erdős zero. Os co-autores de Erdős têm número de Erdős um. Co-autores de co-autores de Erdős têm Número de Erdős dois. Co-autores de co-autores de co-autores de Erdős têm Número de Erdős três, e assim por diante. Quando não é possı́vel estabelecer uma sequência de co-autorias partindo de Erdős até uma pessoa, define-se que o Número de Erdős dessa pessoa é infinito. Por exemplo, dadas as seguintes relações de co-autoria em uma tal rede social

| Autor            | Co-autores                                                                   |
| :--------------- | ---------------------------------------------------------------------------- |
| P. Erdős         | J. A. Bondy, L. Lovasz, E. G. Strauss, W. T. Tutte                           |
| J. A. Bondy      | P. Erdős, L. Lovasz, U. S. R. Murty                                          |
| L. Lovasz        | J. A. Bondy, P. Erdős                                                        |
| E. G. Strauss    | A. Einstein, P. Erdős                                                        |
| W. T. Tutte      | P. Erdős, D. H. Younger                                                      |
| U. S. R. Murty   | J. A. Bondy, M. H. Carvalho, C. L. Lucchesi                                  |
| A. Einstein      | E. G. Strauss                                                                |
| D. H. Younger    | C. L. Lucchesi, W. T. Tutte                                                  |
| C. L. Lucchesi   | M. H. Carvalho, A. A. A. Miranda, U. S. R. Murty, C. N. Silva, D. H. Younger |
| M. H. Carvalho   | C. L. Lucchesi, U. S. R. Murty                                               |
| A. A. A. Miranda | C. L. Lucchesi                                                               |
| C. N. Silva      | C. L. Lucchesi                                                               |

observamos que o número de Erdős de cada autor é

| Autor            | Número de Erdős |
| :--------------: | :-------------: |
| P. Erdős         | 0               |
| J. A. Bondy      | 1               |
| L. Lovasz        | 1               |
| E. G. Strauss    | 1               |
| W. T. Tutte      | 1               |
| U. S. R. Murty   | 2               |
| A. Einstein      | 2               |
| D. H. Younger    | 2               |
| C. L. Lucchesi   | 3               |
| M. H. Carvalho   | 3               |
| A. A. A. Miranda | 4               |
| C. N. Silva      | 4               |

Dr. Sabin Ada gosta muito de programar e coletou dados de diversas redes sociais centradas em Erdős. Ele quer calcular, para cada uma delas, o maior número de Erdős daquela rede. Porém, Dr. Ada, muito atarefado, nunca encontra tempo para fazer um programa para resolver esse problema e precisa da sua ajuda para fazê-lo.

## Entrada e Saída

**Entrada:** A primeira linha de cada caso de teste contém dois inteiros *N* e *M* , separados por um espaço em branco, que representam, respectivamente, quantas pessoas fazem parte (1 ≤ *N* ≤ 600) e quantas relações de co-autoria existem na rede social (1 ≤ *M* ≤ 10.000). Cada pessoa da rede é representada por um inteiro entre 0 e *N*−1, sendo a pessoa representada por 0 o próprio Erdős. Cada uma das *M* linhas subsequentes de cada caso de teste contém dois inteiros *A* e *B* (1 ≤ *A*, *B* ≤ *N*), separados por um espaço em branco, indicando que a pessoa *A* é co-autora de *B* e vice-versa.

**Saı́da:** A saı́da deve ser uma única linha, contendo o maior Número de Erdős da rede, que pode ser infinito. Nesse caso, a resposta deve ser textual **“infinito”**, caso contrário deve ser apenas um inteiro.

### Exemplos

```bash
$ ./t3 << EOF
  5 4
  0 1
  0 2
  1 2
  3 4
EOF
infinito
```

```bash
$ ./t3 << EOF
  11 13
  0 1
  0 2
  0 3
  0 4
  1 2
  1 5
  3 6
  4 7
  5 8
  5 9
  7 8
  8 9
  8 10
EOF
4
```

```bash
$ ./t3 << EOF
  10 15
  0 1
  0 4
  0 5
  1 2
  1 6
  2 3
  2 7
  3 4
  3 8
  4 9
  5 7
  5 8
  6 8
  6 9
  7 9
EOF
2
```

## Implementação e Submissão

-  A solução deverá ser implementada em C, C++, Pascal ou Python 2 / Python 3. Só é permitido o uso de bibliotecas padrão.


- O programa deve ser submetido no SuSy, com o nome principal **t3** (por exemplo, `t3.c`).

- O número máximo de submissões é 20.

- A tarefa contém 10 testes abertos e 10 testes fechados. A nota será proporcional ao número de acertos nos testes fechados.

## Prazo

**A solução pode ser submetida até o dia 17/05/21.**
