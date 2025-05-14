#include "../../main.h"

void pause_console() {
    printf("\nPressione ENTER para continuar...\n");
    fflush(stdout);
    getchar();

    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}