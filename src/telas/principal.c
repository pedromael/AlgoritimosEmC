#include "../../main.h"

void principal()
{
    int escolha;

    printf("escolha as opcoes disponiveis \n");
    printf("1-Levantamento \n");
    printf("2-Tranferencia \n");
    printf("3-Deposito \n");
    printf("4-Consulta saldo\n");
    printf("Qualquer tecla : Sair\n");

    scanf("%d", &escolha);

    if(escolha == 1){
        levantamento();
    }
    else if(escolha == 2){
        transferir();
    }
    else if(escolha == 3){
        depositar();
    }
    else if(escolha == 4){
        consultar_saldo();
    }
}