#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRANSFERENCIA_MAXIMA 1000000
#define LEVANTAMENTO_MAXIMO_DIA 120000
#define LEVANTAMENTO_MAXIMO_VEZ 60000

// funcoes das telas

void principal();
void entrada();

// funcao de operacoes

int transferir();
int depositar();
int levantamento();
void consultar_saldo();

// estruturas

typedef struct{
    int id;
    double patrimonio_liquido;
    char nome[50];
    int senha;
}usuario;

// variaveis externas

extern int numero_usuarios;
extern usuario *usuarios;
extern int logado;

#endif