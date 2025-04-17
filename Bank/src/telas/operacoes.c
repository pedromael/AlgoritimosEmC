#include "../../main.h"

int transferir(){
    int valor,id;
    
    printf("-----------------------------\n");
    printf("digite o ID do usuario a receber\n");
    scanf("%d", &id);

    printf("digite o valor a transferir\n");
    scanf("%d", &valor);

    if(usuarios[id-1].id > 0 && id == logado){
       printf("ID de usuario nao encontrado\n");
    }

    if(valor > usuarios[logado-1].patrimonio_liquido){
        printf("valor maior que seu patrimonio liquido\n");
        return 0;
    }

    int escolha;

    printf("digite 1 - para - transferir: %d.00 para %s\n", valor ,usuarios[id-1].nome);
    scanf("%d", &escolha);
    
    if(escolha != 1){
        printf("tranferencia cancelada\n");
        return 0;
    }

    printf("transferencia realizada com sucesso👌\n");

    usuarios[logado-1].patrimonio_liquido -= valor;
    usuarios[id-1].patrimonio_liquido += valor;

    return 1;
}

int depositar(){
    int valor;
    printf("------------------------------\n");
    printf("digite o dinheiro a depositar\n");
    scanf("%d", &valor);
    usuarios[logado-1].patrimonio_liquido += valor;
    printf("%d.00 depositado com sucesso\n", valor);
    return 1;
}

int levantamento(){
    int valor;
    printf("------------------------------\n");
    printf("digite o dinheiro a levantar\n");
    scanf("%d", &valor);

    if(valor > usuarios[logado-1].patrimonio_liquido){
        printf("valor superior ao teu saldo\n");
    }else{
        usuarios[logado-1].patrimonio_liquido -= valor;
        printf("------------------------------\n");
        printf("---levantamento---simunlado---\n");
        printf("------------------------------\n");
        printf("levantamento de %d.00, realizado com sucesso\n", valor);
        printf("valor restante: %.2f\n", usuarios[logado-1].patrimonio_liquido);
    }
    return 1;
}

void consultar_saldo(){
    printf("-------------------------------\n");
    printf("senhor %s, o seu saldo e de: %.2f\n", usuarios[logado-1].nome, usuarios[logado-1].patrimonio_liquido);
}