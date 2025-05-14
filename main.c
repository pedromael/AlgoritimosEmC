#include "main.h"

int numero_usuarios;
int logado;
usuario *usuarios;
sqlite3 *bd;

int main()
{
    bd = conectar_bd();
    criar_tabelas(bd);

    usuarios = malloc(30 * sizeof(usuario));

    while(1){
        if(!logado) entrada();
        
        if(usuario_e_gerente(bd, logado)){
            principal_gerente();
        }else{
            principal_usuario();
        }
        
        continue;
    }

    return 0;
}