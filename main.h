#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sqlite3.h>

#define TRANSFERENCIA_MAXIMA 1000000
#define LEVANTAMENTO_MAXIMO_DIA 120000
#define LEVANTAMENTO_MAXIMO_VEZ 60000

// funcoes das telas

void principal_usuario();
void principal_gerente();
void entrada();

// funcao de operacoes

int transferir();
int depositar();
int levantamento();
void consultar_saldo_();
int criar_conta(int conta_gerente);

// funcoes de manipulacao de dados

sqlite3* conectar_bd();
void criar_tabelas(sqlite3 *bd);
void inserir_transacao(sqlite3 *bd, int id_transmissor, int id_receptor, double valor);
int inserir_usuario(sqlite3 *bd, const char *nome, int numero_telefone, int pin, int gerente);
void inserir_deposito(sqlite3 *bd, int id_user, int id_funcionario, double valor);
void inserir_levantamento(sqlite3 *bd, int id_user, double valor);

int consultar_numero_usuarios(sqlite3 *bd);
char *consultar_nome_usuario(sqlite3 *bd, int id_user);
int consultar_se_usuario_existe(sqlite3 *bd, int id_user);
double consultar_saldo(sqlite3 *bd, int id_user);
void extrato_bancario(sqlite3 *bd, int id_user);
void listar_usuarios(sqlite3 *bd);
int usuario_e_gerente(sqlite3 *bd, int id_user);

// estruturas

typedef struct{
    int id;
    double patrimonio_liquido;
    int numero_telefone;
    char nome[50];
    int senha;
}usuario;

// variaveis externas

extern int numero_usuarios;
extern usuario *usuarios;
extern int logado;
extern sqlite3 *bd;

#endif