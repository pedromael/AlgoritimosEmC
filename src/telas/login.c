#include "../../main.h"

int autenticar(int id, int senha) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id FROM usuarios WHERE id = ? AND pin = ?;";

    int resultado = sqlite3_prepare_v2(bd, sql, -1, &stmt, 0);
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Erro ao preparar a consulta: %s\n", sqlite3_errmsg(bd));
        return 0;
    }

    // Bind dos parâmetros
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_bind_int(stmt, 2, senha);

    // Executar a consulta
    resultado = sqlite3_step(stmt);

    int autenticado = 0;
    if (resultado == SQLITE_ROW) {
        autenticado = 1;
    }

    sqlite3_finalize(stmt);
    return autenticado;
}

int login(){
    int id, senha;
    while (1) {
        printf("digite o seu id:\n");
        scanf("%d", &id);
        printf("digite o sua senha:\n");
        scanf("%d", &senha);

        if (autenticar(id, senha)) {
            logado = id;
            char *nome_usuario = consultar_nome_usuario(bd, logado);
            printf("Bem vindo %d : %s:\n", logado, nome_usuario);
            return 1;
        }

        printf("id ou senha errada:\n");
        printf("1 - tentar novamente\n");
        printf("Qualquer outro número - cancelar\n");

        int escolha;
        scanf("%d", &escolha);
        if (escolha != 1) break;
    }
    return 0;
}


int criar_conta(int conta_gerente){
    int gerente = conta_gerente ? 1 : 0;
    usuario novo_usuario;
    
    printf("digite o seu nome:\n");
    scanf(" %[^\n]", novo_usuario.nome);
    printf("digite o seu numero de telefone:\n");
    while(1){
        scanf("%d", &novo_usuario.numero_telefone);
        if(novo_usuario.numero_telefone < 100000000 || novo_usuario.numero_telefone > 999999999){
            printf("numero de telefone deve ter 9 digitos:\n");
            continue;
        }
        break;
    }

    printf("digite o sua senha:\n");
    while(1){
        scanf("%d", &novo_usuario.senha);
        if(novo_usuario.senha < 1000 || novo_usuario.senha > 9999){
            printf("senha deve ter 4 digitos:\n");
            continue;
        }
        break;
    }

    printf("------------------------\n");

    int id = inserir_usuario(bd, novo_usuario.nome, novo_usuario.numero_telefone, novo_usuario.senha, gerente);

    if(gerente){
        printf("Conta gerente criada com sucesso:\n");
        printf("Bem vindo %s:\n", novo_usuario.nome);
        printf("seu ID unico e %d:\n", id);
    }else{
        printf("Conta usuario criada com sucesso:\n");
        printf("Bem vindo %s:\n", novo_usuario.nome);
        printf("seu ID unico e %d:\n", id);
    }
    
    return 1;
}

void entrada(){
    int primeiro_conta = consultar_numero_usuarios(bd);

    while(1){
        if(primeiro_conta == 0){
            criar_conta(1);
        }
        printf("Entra com a sua conta. \n");
        if(login()) break;
    }
}