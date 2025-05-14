#include "../../main.h"

int transferir(){
    int valor,id;
    
    printf("-----------------------------\n");
    printf("digite o ID do usuario a receber\n");
    scanf("%d", &id);

    printf("digite o valor a transferir\n");
    scanf("%d", &valor);

    if(consultar_se_usuario_existe(bd, id) == 0){
        printf("ID de usuario nao encontrado\n");
        return 0;
    }

    if(valor > consultar_saldo(bd, logado)){
        printf("valor maior que seu patrimonio liquido\n");
        return 0;
    }

    int escolha;

    printf("digite 1 - para - transferir: %d.00 para %s\n", valor ,consultar_nome_usuario(bd, id));
    scanf("%d", &escolha);
    
    if(escolha != 1){
        printf("tranferencia cancelada\n");
        return 0;
    }

    inserir_transacao(bd, logado, id, valor);
    printf("transferencia realizada com sucesso👌\n");
    

    return 1;
}

int depositar(){
    int valor, id_user;
    printf("------------------------------\n");
    printf("digite o dinheiro a depositar\n");
    scanf("%d", &valor);
    printf("digite o ID do usuario a depositar\n");
    scanf("%d", &id_user);

    if(consultar_se_usuario_existe(bd, id_user) == 0){
        printf("ID de usuario nao encontrado\n");
        return 0;
    }else{
        inserir_deposito(bd, id_user, logado, valor);
    }

    printf("%d.00 depositado com sucesso\n", valor);
    return 1;
}

int levantamento(){
    int valor;
    printf("------------------------------\n");
    printf("digite o dinheiro a levantar\n");
    scanf("%d", &valor);

    if(valor > consultar_saldo(bd, logado)){
        printf("valor superior ao seu patrimonio liquido\n");
        return 0;
    }else{
        inserir_levantamento(bd, logado, valor);
        printf("------------------------------\n");
        printf("---levantamento---simunlado---\n");
        printf("------------------------------\n");
        printf("levantamento de %d.00, realizado com sucesso\n", valor);
        printf("valor restante: %.2f\n", consultar_saldo(bd, logado));
    }
    return 1;
}

void consultar_saldo_(){
    printf("-------------------------------\n");
    printf("senhor %s, o seu saldo e de: %.2f\n", consultar_nome_usuario(bd, logado), consultar_saldo(bd, logado));
}