#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdio.h>
#include <time.h>

#define COR_VERMELHO_RGBA 0xFF0000FF
#define COR_VERDE_RGBA    0x00FF00FF
#define COR_AZUL_RGBA     0x0000FFFF
#define COR_AMARELO_RGBA  0xFFFF00FF

#define COR_RGBA(r, g, b, a) (((uint32_t)(r) << 24) | \
                              ((uint32_t)(g) << 16) | \
                              ((uint32_t)(b) << 8)  | \
                              ((uint32_t)(a)))
struct peca{
    uint32_t cor_hex;
    char letra;
};

typedef struct elemento *Pilha;

Pilha* criar();
int vazia(Pilha*);
int inserir(Pilha*,struct peca);
int remover(Pilha*);
int acessar(Pilha*, struct peca*);
void destruir(Pilha*);

void printaMatriz(Pilha*,int);
Pilha *criamtrz(int, int);
