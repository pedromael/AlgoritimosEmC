#include "../../main.h"

int autenticar(int id,int  senha){
    for(int i = 0; i < numero_usuarios; i++){
        if(usuarios[i].id == id && usuarios[i].senha == senha){
            return 1;
        }
    }
    return 0;
}

int login(){
    int id, senha, escolha;
    printf("digite o seu id:\n");
    scanf("%d", &id);
    printf("digite o sua senha:\n");
    scanf("%d", &senha);

    if(autenticar(id, senha)){
        logado = id;
        return 1;
    }else {
        printf("id ou senha errada:\n");
        printf("1 - tentar novamente\n");
        printf("Qualquer tecla - cancelar\n");

        scanf("%d", &escolha);
        if(escolha == 1) login();
    }
    return 0;
}

int criar_conta(){
    usuario novo_usuario;
    
    printf("digite o seu nome:\n");
    scanf("%s", novo_usuario.nome);
    printf("digite o sua senha:\n");
    scanf("%d", &novo_usuario.senha);

    printf("------------------------\n");
    numero_usuarios++;
    novo_usuario.id = numero_usuarios;
    novo_usuario.patrimonio_liquido = 0.00;

    usuarios[numero_usuarios - 1] = novo_usuario;

    printf("Bem vindo %s:\n", novo_usuario.nome);
    printf("seu ID unico e %d:\n", novo_usuario.id);
    
    return 1;
}

void entrada(){
    int escolha;
    while(1){
        printf("logar(1) ou registrar(2)\n");
        scanf("%d", &escolha);

        if(escolha == 1){
            if(login()) break;
        }
        else if(escolha == 2){
            if (criar_conta()) login();
        }
        else printf("escolha 1 ou 2\n");
    }
}