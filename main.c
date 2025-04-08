#include "main.h"

int numero_usuarios;
int logado;
usuario *usuarios;

int main()
{
    usuarios = malloc(30 * sizeof(usuario));

    int escolha;
    while(1){

        if(!logado) entrada();
        printf("-----------------------------");
        principal();
    }
}