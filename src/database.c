#include "../main.h"

// Função para lidar com erros do SQLite
void tratar_erro(int resultado, sqlite3 *bd) {
    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Erro do SQLite: %s\n", sqlite3_errmsg(bd));
        sqlite3_close(bd);
        exit(1);
    }
}

// Função para conectar ao banco de dados
sqlite3* conectar_bd() {
    sqlite3 *bd;
    int resultado = sqlite3_open("banktrade.db", &bd);

    if (resultado != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(bd));
        return NULL;
    }

    return bd;
}

// Função para criar as tabelas
void criar_tabelas(sqlite3 *bd) {
    const char *sql = 
        "CREATE TABLE IF NOT EXISTS usuarios ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "nome TEXT NOT NULL, "
        "numero_de_telefone INTEGER(9) UNIQUE NOT NULL, "
        "pin INTEGER(4) NOT NULL,"
        "gestor INTEGER(1) DEFAULT 0);"

        "CREATE TABLE IF NOT EXISTS transacoes ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "id_transmissor INTEGER NOT NULL, "
        "id_receptor INTEGER NOT NULL, "
        "valor REAL NOT NULL, "
        "data DATETIME DEFAULT CURRENT_TIMESTAMP);"

        "CREATE TABLE IF NOT EXISTS depositos ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "id_user INTEGER NOT NULL, "
        "id_funcionario INTEGER NOT NULL, "
        "valor REAL NOT NULL, "
        "data DATETIME DEFAULT CURRENT_TIMESTAMP);"

        "CREATE TABLE IF NOT EXISTS levantamentos ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "id_user INTEGER NOT NULL, "
        "valor REAL NOT NULL, "
        "data DATETIME DEFAULT CURRENT_TIMESTAMP);";

    char *mensagem_erro = 0;
    int resultado = sqlite3_exec(bd, sql, 0, 0, &mensagem_erro);
    tratar_erro(resultado, bd);
}

void inserir_transacao(sqlite3 *bd, int id_transmissor, int id_receptor, double valor) {
    char sql_inserir[256];
    snprintf(sql_inserir, sizeof(sql_inserir), 
             "INSERT INTO transacoes (id_transmissor, id_receptor, valor) VALUES (%d, %d, %.2f);",
                id_transmissor, id_receptor, valor);
    
    char *mensagem_erro = 0;
    int resultado = sqlite3_exec(bd, sql_inserir, 0, 0, &mensagem_erro);
    tratar_erro(resultado, bd);
}

int inserir_usuario(sqlite3 *bd, const char *nome, int numero_telefone, int pin, int gerente) {
    char sql_inserir[256];
    snprintf(sql_inserir, sizeof(sql_inserir), 
             "INSERT INTO usuarios (nome, numero_de_telefone, pin, gestor) VALUES ('%s', %d, %d, %d);", 
             nome, numero_telefone, pin, gerente);

    char *mensagem_erro = 0;
    int resultado = sqlite3_exec(bd, sql_inserir, 0, 0, &mensagem_erro);
    tratar_erro(resultado, bd);

    return (int)sqlite3_last_insert_rowid(bd);
}

void inserir_deposito(sqlite3 *bd, int id_user, int id_funcionario, double valor) {
    char sql_inserir[256];
    snprintf(sql_inserir, sizeof(sql_inserir), 
             "INSERT INTO depositos (id_user, id_funcionario, valor) VALUES (%d, %d, %.2f);", 
             id_user, id_funcionario, valor);

    char *mensagem_erro = 0;
    int resultado = sqlite3_exec(bd, sql_inserir, 0, 0, &mensagem_erro);
    tratar_erro(resultado, bd);
}

void inserir_levantamento(sqlite3 *bd, int id_user, double valor) {
    char sql_inserir[256];
    snprintf(sql_inserir, sizeof(sql_inserir), 
             "INSERT INTO levantamentos (id_user, valor) VALUES (%d, %.2f);", 
             id_user, valor);

    char *mensagem_erro = 0;
    int resultado = sqlite3_exec(bd, sql_inserir, 0, 0, &mensagem_erro);
    tratar_erro(resultado, bd);
}

double consultar_valor_depositado(sqlite3 *bd, int id_user) {
    const char *sql = "SELECT SUM(valor) FROM depositos WHERE id_user = ?;";
    sqlite3_stmt *stmt;
    int resultado = sqlite3_prepare_v2(bd, sql, -1, &stmt, 0);
    tratar_erro(resultado, bd);

    sqlite3_bind_int(stmt, 1, id_user);  // uso seguro de binding

    double total_depositado = 0.0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        total_depositado = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return total_depositado;
}	

double consultar_valor_transferido(sqlite3 *bd, int id_user) {
    const char *sql = "SELECT SUM(valor) FROM transacoes WHERE id_transmissor = ?;";
    sqlite3_stmt *stmt;
    int resultado = sqlite3_prepare_v2(bd, sql, -1, &stmt, 0);
    tratar_erro(resultado, bd);

    sqlite3_bind_int(stmt, 1, id_user);  // uso seguro de binding

    double total_transferido = 0.0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        total_transferido = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return total_transferido;
}

double consultar_valor_recebido(sqlite3 *bd, int id_user) {
    const char *sql = "SELECT SUM(valor) FROM transacoes WHERE id_receptor = ?;";
    sqlite3_stmt *stmt;
    int resultado = sqlite3_prepare_v2(bd, sql, -1, &stmt, 0);
    tratar_erro(resultado, bd);

    sqlite3_bind_int(stmt, 1, id_user);  // uso seguro de binding

    double total_transferido = 0.0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        total_transferido = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return total_transferido;
}

double consulta_valor_levantado(sqlite3 *bd, int id_user) {
    const char *sql = "SELECT SUM(valor) FROM levantamentos WHERE id_user = ?;";
    sqlite3_stmt *stmt;
    int resultado = sqlite3_prepare_v2(bd, sql, -1, &stmt, 0);
    tratar_erro(resultado, bd);

    sqlite3_bind_int(stmt, 1, id_user);  // uso seguro de binding

    double total_levantado = 0.0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        total_levantado = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return total_levantado;
}

double consultar_saldo(sqlite3 *bd, int id_user) {
    double total_depositado = consultar_valor_depositado(bd, id_user);
    double total_transferido = consultar_valor_transferido(bd, id_user);
    double total_recebido = consultar_valor_recebido(bd, id_user);
    double total_levantado = consulta_valor_levantado(bd, id_user);

    return (total_depositado + total_recebido - total_transferido - total_levantado);
}

void extrato_bancario(sqlite3 *bd, int id_user) {
    const char *sql = 
        "SELECT 'Deposito' AS tipo, valor, data FROM depositos WHERE id_user = ? "
        "UNION ALL "
        "SELECT 'Levantamento' AS tipo, (valor*-1), data FROM levantamentos WHERE id_user = ? "
        "UNION ALL "
        "SELECT 'Transferencia Enviada' AS tipo, (valor*-1), data FROM transacoes WHERE id_transmissor = ? "
        "UNION ALL "
        "SELECT 'Transferencia Recebida' AS tipo, valor, data FROM transacoes WHERE id_receptor = ? "
        "ORDER BY data ASC;";

    sqlite3_stmt *stmt;
    int resultado = sqlite3_prepare_v2(bd, sql, -1, &stmt, 0);
    tratar_erro(resultado, bd);

    // Bind os mesmos parâmetros 4 vezes (para cada ?)
    sqlite3_bind_int(stmt, 1, id_user);
    sqlite3_bind_int(stmt, 2, id_user);
    sqlite3_bind_int(stmt, 3, id_user);
    sqlite3_bind_int(stmt, 4, id_user);

    printf("Extrato bancario do usuario %d:\n", id_user);
    printf("%-25s %-10s %s\n", "Tipo", "Valor", "Data");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *tipo = sqlite3_column_text(stmt, 0);
        double valor = sqlite3_column_double(stmt, 1);
        const unsigned char *data = sqlite3_column_text(stmt, 2);

        printf("%-25s %-10.2f %s\n", tipo, valor, data);
    }

    sqlite3_finalize(stmt);
}


int consultar_numero_usuarios(sqlite3 *bd) {
    const char *sql = "SELECT COUNT(*) FROM usuarios;";
    sqlite3_stmt *stmt;
    int resultado = sqlite3_prepare_v2(bd, sql, -1, &stmt, 0);
    tratar_erro(resultado, bd);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        numero_usuarios = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return numero_usuarios;
    } else {
        printf("Erro ao contar usuários.\n");
    }
    return 0;
}

int consultar_se_usuario_existe(sqlite3 *bd, int id_user) {
    char sql_consultar[256];
    snprintf(sql_consultar, sizeof(sql_consultar), 
             "SELECT id FROM usuarios WHERE id = %d;", id_user);

    sqlite3_stmt *stmt;
    int resultado = sqlite3_prepare_v2(bd, sql_consultar, -1, &stmt, 0);
    tratar_erro(resultado, bd);

    int existe = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        existe = sqlite3_column_int(stmt, 0);
    } else {
        printf("Usuário não encontrado.\n");
    }

    sqlite3_finalize(stmt);
    return existe;
}

char *consultar_nome_usuario(sqlite3 *bd, int id_user) {
    const char *sql = "SELECT nome FROM usuarios WHERE id = ?;";
    sqlite3_stmt *stmt;
    int resultado = sqlite3_prepare_v2(bd, sql, -1, &stmt, 0);
    tratar_erro(resultado, bd);

    sqlite3_bind_int(stmt, 1, id_user);  // uso seguro de binding

    char *nome_copia = NULL;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const unsigned char *nome = sqlite3_column_text(stmt, 0);
        if (nome) {
            nome_copia = strdup((const char *)nome);
        }
    }

    sqlite3_finalize(stmt);
    return nome_copia;
}

int usuario_e_gerente(sqlite3 *bd, int id_user) {
    char sql_consultar[256];
    snprintf(sql_consultar, sizeof(sql_consultar), 
             "SELECT gestor FROM usuarios WHERE id = %d;", id_user);

    sqlite3_stmt *stmt;
    int resultado = sqlite3_prepare_v2(bd, sql_consultar, -1, &stmt, 0);
    tratar_erro(resultado, bd);

    int gerente = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        gerente = sqlite3_column_int(stmt, 0);
    } else {
        printf("Usuário não encontrado.\n");
    }

    sqlite3_finalize(stmt);
    return gerente;
}

void listar_usuarios(sqlite3 *bd) {
    const char *sql = "SELECT id, nome FROM usuarios;";
    sqlite3_stmt *stmt;
    int resultado = sqlite3_prepare_v2(bd, sql, -1, &stmt, 0);
    tratar_erro(resultado, bd);

    printf("Lista de usuários:\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nome = sqlite3_column_text(stmt, 1);
        printf("ID: %d, Nome: %s\n", id, nome ? (const char *)nome : "N/A");
    }

    sqlite3_finalize(stmt);
}
