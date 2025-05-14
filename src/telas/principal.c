#include "../../main.h"

void principal_usuario()
{
    pause_console();

    int escolha;

    printf("------------------------------\n");
    printf("escolha as opcoes disponiveis \n");
    printf("1-Levantamento \n");
    printf("2-Tranferencia \n");
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
        consultar_saldo_();
    }else{
        logado = 0;
    }
}

void principal_gerente()
{
    pause_console();
    
    int escolha;

    printf("------------------------------\n");
    printf("escolha as opcoes disponiveis \n");
    printf("1-Levantamento \n");
    printf("2-Tranferencia \n");
    printf("3-Deposito \n");
    printf("4-Consulta saldo\n");
    printf("5-Criar conta\n");
    printf("6-Extrato do usuario\n");
    printf("7-Listar usuarios\n");
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
        consultar_saldo_();
    }else if(escolha == 5){
        criar_conta(0);
    }else if(escolha == 6){
        int id;
        printf("digite o id do usuario:\n");
        scanf("%d", &id);
        printf("------------------------------\n");
        if(consultar_se_usuario_existe(bd, id) == 0){
            printf("ID de usuario nao encontrado\n");
        }else{
            extrato_bancario(bd, id);
        }
        printf("------------------------------\n"); 
    }else if(escolha == 7){
        printf("--------------usuarios cadastrados:--------------\n");
        listar_usuarios(bd);
    }
    else{
        logado = 0;
    }
}