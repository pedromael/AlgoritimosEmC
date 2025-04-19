#include <stdio.h>
#include <stdarg.h>

// Função que aceita uma quantidade variável de inteiros e calcula a soma
int soma(int quantidade, ...) {
    va_list args;
    int soma = 0;

    // Inicializa a lista de argumentos variáveis
    va_start(args, quantidade);

    // Itera pelos argumentos
    for (int i = 0; i < quantidade; i++) {
        soma += va_arg(args, int); // Obtém o próximo argumento
    }

    // Finaliza a lista de argumentos variáveis
    va_end(args);

    return soma;
}

int main() {
    // Exemplo de uso da função
    printf("Soma de 1, 2, 3: %d\n", soma(3, 1, 2, 3));
    printf("Soma de 10, 20: %d\n", soma(2, 10, 20));
    printf("Soma de 5, 15, 25, 35: %d\n", soma(4, 5, 15, 25, 35));

    return 0;
}