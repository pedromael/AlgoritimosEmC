#include "main.h"

int numero_usuarios;
int logado;
usuario *usuarios;

int main()
{
    usuarios = malloc(30 * sizeof(usuario));

    while(1){
        if(!logado) entrada();
        principal();
        continue;
    }

    return 0;
}